#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""present/daily/*.md  ->  *.docx

只用标准库（zipfile），不依赖 python-docx —— 因为本机 PyPI 装不上东西。

用法:
    python present/daily/_make.py              # 补齐所有缺的 docx
    python present/daily/_make.py 2026-10-13   # 只生成指定日期
    python present/daily/_make.py --force      # 全部重新生成

支持的 markdown 子集（只有这些，别的语法不认）:
    # / ## / ###        标题
    ``` 围栏代码块 ```
    - 列表项
    - [ ] 复选框        - [x] 已勾选
    > 引用 / 提示块
    ---                分隔线
    | a | b |          表格，第二行必须是 |---|---|
    **粗体**  `行内代码`

生成的 docx 时间戳固定为当天 00:00，所以同样的 md 生成出来的字节是一样的 ——
git 里不会出现无意义的二进制抖动。
"""

import os
import re
import sys
import zipfile
import datetime

HERE = os.path.dirname(os.path.abspath(__file__))
NAME_RE = re.compile(r'^(\d{4}-\d{2}-\d{2})\.md$')

# ---------------------------------------------------------------- inline

INLINE_RE = re.compile(r'(\*\*.+?\*\*|`[^`]+`)')


def _split_inline(text):
    out = []
    for part in INLINE_RE.split(text):
        if not part:
            continue
        if len(part) > 4 and part.startswith('**') and part.endswith('**'):
            out.append(('bold', part[2:-2]))
        elif len(part) > 2 and part.startswith('`') and part.endswith('`'):
            out.append(('code', part[1:-1]))
        else:
            out.append(('plain', part))
    return out


def esc(t):
    return (t.replace('&', '&amp;')
             .replace('<', '&lt;')
             .replace('>', '&gt;'))


def esc_attr(t):
    return esc(t).replace('"', '&quot;')


def runs_xml(text, force_bold=False):
    chunks = []
    for kind, val in _split_inline(text):
        props = []
        if force_bold or kind == 'bold':
            props.append('<w:b/>')
        if kind == 'code':
            props.append('<w:rFonts w:ascii="Consolas" w:hAnsi="Consolas"/>')
            props.append('<w:sz w:val="19"/><w:szCs w:val="19"/>')
        rpr = '<w:rPr>%s</w:rPr>' % ''.join(props) if props else ''
        chunks.append('<w:r>%s<w:t xml:space="preserve">%s</w:t></w:r>'
                      % (rpr, esc(val)))
    if not chunks:
        chunks.append('<w:r><w:t xml:space="preserve"></w:t></w:r>')
    return ''.join(chunks)


def para_xml(text='', style=None, prefix='', force_bold=False):
    ppr = '<w:pPr><w:pStyle w:val="%s"/></w:pPr>' % style if style else ''
    return '<w:p>%s%s</w:p>' % (ppr, runs_xml(prefix + text, force_bold))


def code_xml(lines):
    body = []
    for i, ln in enumerate(lines):
        if i:
            body.append('<w:br/>')
        body.append('<w:t xml:space="preserve">%s</w:t>' % esc(ln))
    return ('<w:p><w:pPr><w:pStyle w:val="Code"/></w:pPr>'
            '<w:r>%s</w:r></w:p>' % ''.join(body))


def hr_xml():
    return para_xml('', style='HR')


# ---------------------------------------------------------------- table

def _split_row(raw):
    r = raw.strip()
    if r.startswith('|'):
        r = r[1:]
    if r.endswith('|'):
        r = r[:-1]
    return [c.strip() for c in r.split('|')]


def _is_sep(cells):
    return all(re.fullmatch(r':?-{2,}:?', c or '') for c in cells) and cells


def table_xml(raw_rows):
    rows = [_split_row(r) for r in raw_rows]
    rows = [r for r in rows if not _is_sep(r)]
    if not rows:
        return ''
    ncol = max(len(r) for r in rows)
    for r in rows:
        r += [''] * (ncol - len(r))

    total = 9000
    base = total // ncol
    widths = [base] * ncol
    widths[-1] = total - base * (ncol - 1)

    border = ('<w:%s w:val="single" w:sz="4" w:space="0" w:color="BFBFBF"/>')
    borders = '<w:tblBorders>%s</w:tblBorders>' % ''.join(
        border % k for k in ('top', 'left', 'bottom', 'right', 'insideH', 'insideV'))

    grid = ''.join('<w:gridCol w:w="%d"/>' % w for w in widths)

    trs = []
    for idx, r in enumerate(rows):
        head = (idx == 0)
        tcs = []
        for c, w in zip(r, widths):
            shd = ('<w:shd w:val="clear" w:color="auto" w:fill="EEF1F6"/>'
                   if head else '')
            tcpr = ('<w:tcPr><w:tcW w:w="%d" w:type="dxa"/>%s'
                    '<w:vAlign w:val="center"/></w:tcPr>' % (w, shd))
            p = ('<w:p><w:pPr><w:spacing w:before="30" w:after="30" '
                 'w:line="260" w:lineRule="auto"/></w:pPr>%s</w:p>'
                 % runs_xml(c, force_bold=head))
            tcs.append('<w:tc>%s%s</w:tc>' % (tcpr, p))
        trpr = '<w:trPr><w:tblHeader/></w:trPr>' if head else ''
        trs.append('<w:tr>%s%s</w:tr>' % (trpr, ''.join(tcs)))

    return ('<w:tbl><w:tblPr><w:tblW w:w="%d" w:type="dxa"/>%s'
            '<w:tblCellMar>'
            '<w:top w:w="60" w:type="dxa"/><w:left w:w="90" w:type="dxa"/>'
            '<w:bottom w:w="60" w:type="dxa"/><w:right w:w="90" w:type="dxa"/>'
            '</w:tblCellMar></w:tblPr><w:tblGrid>%s</w:tblGrid>%s</w:tbl>'
            % (total, borders, grid, ''.join(trs)))


# ---------------------------------------------------------------- block parse

def parse_blocks(md):
    lines = md.replace('\r\n', '\n').replace('\r', '\n').split('\n')
    blocks = []
    i = 0
    while i < len(lines):
        s = lines[i].strip()
        if not s:
            i += 1
            continue
        if s.startswith('```'):
            i += 1
            buf = []
            while i < len(lines) and not lines[i].strip().startswith('```'):
                buf.append(lines[i])
                i += 1
            i += 1
            blocks.append(('code', buf))
            continue
        if re.fullmatch(r'-{3,}', s):
            blocks.append(('hr', None))
            i += 1
            continue
        m = re.match(r'^(#{1,3})\s+(.*)$', s)
        if m:
            blocks.append(('h%d' % len(m.group(1)), m.group(2).strip()))
            i += 1
            continue
        if s.startswith('|'):
            buf = []
            while i < len(lines) and lines[i].strip().startswith('|'):
                buf.append(lines[i].strip())
                i += 1
            blocks.append(('table', buf))
            continue
        if s.startswith('>'):
            buf = []
            while i < len(lines) and lines[i].strip().startswith('>'):
                buf.append(lines[i].strip().lstrip('>').strip())
                i += 1
            blocks.append(('quote', buf))
            continue
        m = re.match(r'^-\s+\[([ xX])\]\s*(.*)$', s)
        if m:
            done = m.group(1).lower() == 'x'
            blocks.append(('check', (done, m.group(2))))
            i += 1
            continue
        if re.match(r'^[-*]\s+', s):
            blocks.append(('bullet', re.sub(r'^[-*]\s+', '', s)))
            i += 1
            continue
        blocks.append(('p', s))
        i += 1
    return blocks


def render_body(blocks):
    out = []
    for kind, val in blocks:
        if kind == 'hr':
            out.append(hr_xml())
        elif kind in ('h1', 'h2', 'h3'):
            out.append(para_xml(val, style='Heading' + kind[1]))
        elif kind == 'p':
            out.append(para_xml(val))
        elif kind == 'bullet':
            out.append(para_xml(val, style='Bullet', prefix='•  '))
        elif kind == 'check':
            done, text = val
            out.append(para_xml(text, style='Check',
                                prefix=('☑  ' if done else '☐  ')))
        elif kind == 'quote':
            for ln in val:
                out.append(para_xml(ln, style='Quote'))
        elif kind == 'code':
            out.append(code_xml(val))
        elif kind == 'table':
            xml = table_xml(val)
            # 表格相邻时必须夹一个空段落，否则 Word 会把两张表并成一张
            if out and out[-1].startswith('<w:tbl>'):
                out.append('<w:p/>')
            if out and out[-1].startswith('<w:tbl>') and xml:
                out.append('<w:p/>')
            out.append(xml or '')
    return ''.join(out)


# ---------------------------------------------------------------- docx parts

XML_DECL = '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>\n'

CONTENT_TYPES = XML_DECL + '''<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
<Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
<Default Extension="xml" ContentType="application/xml"/>
<Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/>
<Override PartName="/word/styles.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml"/>
<Override PartName="/docProps/core.xml" ContentType="application/vnd.openxmlformats-package.core-properties+xml"/>
<Override PartName="/docProps/app.xml" ContentType="application/vnd.openxmlformats-officedocument.extended-properties+xml"/>
</Types>'''

ROOT_RELS = XML_DECL + '''<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
<Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/>
<Relationship Id="rId2" Type="http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties" Target="docProps/core.xml"/>
<Relationship Id="rId3" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties" Target="docProps/app.xml"/>
</Relationships>'''

DOC_RELS = XML_DECL + '''<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
<Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" Target="styles.xml"/>
</Relationships>'''

APP_XML = XML_DECL + '''<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties" xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
<Application>ypsajyy-devlog / _make.py</Application>
</Properties>'''

CONTENT_FONT = ('<w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" '
                'w:eastAsia="微软雅黑" w:cs="Calibri"/>')


def styles_xml():
    def heading(lvl, size, color, before, after, extra=''):
        return (
            '<w:style w:type="paragraph" w:styleId="Heading%d">'
            '<w:name w:val="heading %d"/><w:basedOn w:val="Normal"/><w:qFormat/>'
            '<w:pPr><w:keepNext/><w:spacing w:before="%d" w:after="%d"/>%s'
            '<w:outlineLvl w:val="%d"/></w:pPr>'
            '<w:rPr><w:b/><w:color w:val="%s"/><w:sz w:val="%d"/>'
            '<w:szCs w:val="%d"/></w:rPr></w:style>'
            % (lvl, lvl, before, after, extra, lvl - 1, color, size, size))

    return XML_DECL + (
        '<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">'
        '<w:docDefaults><w:rPrDefault><w:rPr>%s'
        '<w:sz w:val="21"/><w:szCs w:val="21"/></w:rPr></w:rPrDefault>'
        '<w:pPrDefault><w:pPr><w:spacing w:before="0" w:after="120" '
        'w:line="300" w:lineRule="auto"/></w:pPr></w:pPrDefault></w:docDefaults>'

        '<w:style w:type="paragraph" w:default="1" w:styleId="Normal">'
        '<w:name w:val="Normal"/><w:qFormat/></w:style>'

        % CONTENT_FONT
    ) + (
        heading(1, 32, '1F3864', 300, 160)
        + heading(2, 26, '2E5496', 280, 130,
                  '<w:pBdr><w:bottom w:val="single" w:sz="6" w:space="3" '
                  'w:color="D0D7E5"/></w:pBdr>')
        + heading(3, 23, '404040', 220, 110)

        + '<w:style w:type="paragraph" w:styleId="Quote">'
          '<w:name w:val="Quote"/><w:basedOn w:val="Normal"/>'
          '<w:pPr><w:pBdr><w:left w:val="single" w:sz="18" w:space="10" '
          'w:color="C9CDD4"/></w:pBdr><w:ind w:left="284" w:right="284"/>'
          '<w:spacing w:before="90" w:after="150"/></w:pPr>'
          '<w:rPr><w:color w:val="595959"/><w:sz w:val="20"/>'
          '<w:szCs w:val="20"/></w:rPr></w:style>'

        + '<w:style w:type="paragraph" w:styleId="Code">'
          '<w:name w:val="Code"/><w:basedOn w:val="Normal"/>'
          '<w:pPr><w:shd w:val="clear" w:color="auto" w:fill="F6F7F9"/>'
          '<w:ind w:left="227" w:right="227"/>'
          '<w:spacing w:before="80" w:after="80" w:line="264" w:lineRule="auto"/>'
          '</w:pPr>'
          '<w:rPr><w:rFonts w:ascii="Consolas" w:hAnsi="Consolas" '
          'w:eastAsia="Consolas"/><w:sz w:val="19"/>'
          '<w:szCs w:val="19"/></w:rPr></w:style>'

        + '<w:style w:type="paragraph" w:styleId="Check">'
          '<w:name w:val="Check"/><w:basedOn w:val="Normal"/>'
          '<w:pPr><w:ind w:left="454" w:hanging="284"/>'
          '<w:spacing w:after="60"/></w:pPr></w:style>'

        + '<w:style w:type="paragraph" w:styleId="Bullet">'
          '<w:name w:val="Bullet"/><w:basedOn w:val="Normal"/>'
          '<w:pPr><w:ind w:left="454" w:hanging="284"/>'
          '<w:spacing w:after="60"/></w:pPr></w:style>'

        + '<w:style w:type="paragraph" w:styleId="HR">'
          '<w:name w:val="HR"/><w:basedOn w:val="Normal"/>'
          '<w:pPr><w:pBdr><w:bottom w:val="single" w:sz="6" w:space="1" '
          'w:color="D9D9D9"/></w:pBdr>'
          '<w:spacing w:before="80" w:after="150"/></w:pPr>'
          '<w:rPr><w:sz w:val="4"/><w:szCs w:val="4"/></w:rPr></w:style>'
        + '</w:styles>')


def document_xml(md, title):
    body = render_body(parse_blocks(md))
    sect = ('<w:sectPr><w:pgSz w:w="11906" w:h="16838"/>'
            '<w:pgMar w:top="1134" w:right="1134" w:bottom="1134" '
            'w:left="1134" w:header="851" w:footer="992" w:gutter="0"/>'
            '</w:sectPr>')
    return XML_DECL + (
        '<w:document xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">'
        '<w:body>%s<w:p/>%s</w:body></w:document>' % (body, sect))


def core_xml(title, stamp):
    return XML_DECL + (
        '<cp:coreProperties '
        'xmlns:cp="http://schemas.openxmlformats.org/package/2006/metadata/core-properties" '
        'xmlns:dc="http://purl.org/dc/elements/1.1/" '
        'xmlns:dcterms="http://purl.org/dc/terms/" '
        'xmlns:dcmitype="http://purl.org/dc/dcmitype/" '
        'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">'
        '<dc:title>%s</dc:title>'
        '<dc:creator>ypsajyy0804</dc:creator>'
        '<cp:lastModifiedBy>ypsajyy0804</cp:lastModifiedBy>'
        '<dcterms:created xsi:type="dcterms:W3CDTF">%s</dcterms:created>'
        '<dcterms:modified xsi:type="dcterms:W3CDTF">%s</dcterms:modified>'
        '</cp:coreProperties>' % (esc_attr(title), stamp, stamp))


# ---------------------------------------------------------------- build

def add(z, name, content, dt):
    zi = zipfile.ZipInfo(name, date_time=(dt.year, dt.month, dt.day, 0, 0, 0))
    zi.compress_type = zipfile.ZIP_DEFLATED
    zi.external_attr = 0o600 << 16
    z.writestr(zi, content.encode('utf-8'))


def build(md_path, dt):
    with open(md_path, encoding='utf-8') as f:
        md = f.read()

    first_line = next((l.strip() for l in md.split('\n') if l.strip()), '')
    title = re.sub(r'^#\s*', '', first_line) or os.path.basename(md_path)
    stamp = '%04d-%02d-%02dT00:00:00Z' % (dt.year, dt.month, dt.day)

    out_path = os.path.splitext(md_path)[0] + '.docx'
    tmp_path = out_path + '.tmp'
    with zipfile.ZipFile(tmp_path, 'w', zipfile.ZIP_DEFLATED) as z:
        add(z, '[Content_Types].xml', CONTENT_TYPES, dt)
        add(z, '_rels/.rels', ROOT_RELS, dt)
        add(z, 'word/document.xml', document_xml(md, title), dt)
        add(z, 'word/styles.xml', styles_xml(), dt)
        add(z, 'word/_rels/document.xml.rels', DOC_RELS, dt)
        add(z, 'docProps/core.xml', core_xml(title, stamp), dt)
        add(z, 'docProps/app.xml', APP_XML, dt)
    os.replace(tmp_path, out_path)
    return out_path


def main(argv):
    force = '--force' in argv
    only = [a for a in argv[1:] if NAME_RE.match(os.path.basename(a) + '.md')]
    only = [a if a.endswith('.md') else a + '.md' for a in only]

    made, skipped = [], []
    for name in sorted(os.listdir(HERE)):
        m = NAME_RE.match(name)
        if not m:
            continue
        if only and name not in only:
            continue
        md_path = os.path.join(HERE, name)
        docx_path = os.path.splitext(md_path)[0] + '.docx'
        if os.path.exists(docx_path) and not force \
                and os.path.getmtime(docx_path) >= os.path.getmtime(md_path):
            skipped.append(name)
            continue
        dt = datetime.date(*map(int, m.group(1).split('-')))
        build(md_path, dt)
        made.append(name)

    for n in made:
        print('  generated  %s' % os.path.splitext(n)[0] + '.docx')
    for n in skipped:
        print('  up-to-date %s' % os.path.splitext(n)[0] + '.docx')
    if not made and not skipped:
        print('  (present/daily/ 下没有 YYYY-MM-DD.md)')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
