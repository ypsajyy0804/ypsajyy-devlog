# 同样是越界写，为什么 valgrind 一声不吭、ASan 当场抓住

## 现象

2026-11-01 写的 `S02.c` 里，把 `char buf[32]` 改成 `char buf[5]`，然后 `my_strcpy(buf, "hello")` ——
`"hello"` 连结尾的 `'\0'` 一共 6 个字节，往 5 个字节的数组里拷。

- 普通编译：**跑完了，还打印出 `copy = hello`**，什么都没发生
- `valgrind --leak-check=full`：**全绿**，`0 errors`
- `gcc -fsanitize=address` 编译后再跑：

```
==1889==ERROR: AddressSanitizer: stack-buffer-overflow
WRITE of size 1 at 0x7ffd7bf76665 thread T0
    #0 in my_strcpy S02.c:23
    #1 in main     S02.c:39
  This frame has 1 object(s):
    [32, 37) 'buf' (line 38) <== Memory access at offset 37 overflows this variable
```

它不是没坏，是坏在没人看着的地方。C 里这叫**未定义行为** —— 编译器不欠你一个报错。

## 为什么 valgrind 看不见

valgrind 是**运行期**干活的：它把程序放到一个虚拟机里，逐条指令模拟执行，同时记账。
它记的账是 `malloc` / `free` 管的那些块 —— 也就是**堆**。哪块还没释放、哪块已经释放了又被写、哪块写到了块外面，它都知道。

但 `buf` 是**栈**上的。栈在程序启动时就一次性划好一大片，`buf`、`main` 的返回地址、别的局部变量全挤在里面。
对 valgrind 来说这是**一整块合法的内存**，它不知道 `buf` 的边界在第 5 个字节停住 ——
它只跟踪 `malloc`，栈帧的内存分配它不参与。

所以：**valgrind 的本职是堆，不是栈。**

## ASan 怎么就能看见

`-fsanitize=address` 是**编译期**插东西：gcc 在你的每个栈变量前后各塞一段红色区域（redzone），
再在内存里维护一张"影子表"，记着每一段字节能不能写。
`my_strcpy` 写到 `buf[5]` 的那一刻，影子表说"这里是红区"，程序立刻中止并打出调用栈。

它不等到栈帧被踩坏才报警 —— **写下去的那一条指令就报**。

## 怎么用

| 想看什么 | 用什么 |
|---|---|
| 堆上的泄漏、重复 `free`、堆越界 | `valgrind --leak-check=full` |
| 栈越界、未初始化变量、有符号溢出 | `gcc -fsanitize=address,undefined -g` |

**两个工具管的是两块内存，不是谁能替代谁。** 写 C 的时候两个都开，别只开一个。

## 一句话版本

> valgrind 管堆，ASan 管栈 —— 只开一个，等于只查了一半。

---

> 那天还顺带确认了一件事：`sizeof(buf)` 是在**编译期**算出 5 或 32 的，运行期没有任何东西知道 `buf` 有多长。
> 这也是 `strcpy` 这类函数天生没法保护自己的原因 —— 签名的参数里根本没有长度这一个位子。
