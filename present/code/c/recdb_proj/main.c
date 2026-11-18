#include "recdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	if(argc < 3){
		fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
		return 1;
	}

	if(strcmp(argv[2], "write") == 0) {
		int n = rec_write(argv[1]);
		printf("写入 %d 条数据\n", n);
	}

	if(strcmp(argv[2], "show") == 0) {
		int n = rec_show(argv[1]);
		printf("返回 %d 条数据\n", n);
	}

	if(strcmp(argv[2], "patch") == 0) {
		if(argc != 5){
			fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
			return 1;
		}

		int n = rec_patch(argv[1], atoi(argv[3]), atof(argv[4]));
		if(n) printf("成功修改\n");
		else printf("文本内未找到 id\n");
	}

	return 0;
}
