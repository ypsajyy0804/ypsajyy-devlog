#include <stdio.h>
#include <string.h>

int main() {
	FILE *fp = fopen("./data.txt", "r");
	if(fp == NULL) {
		printf("打开文件失败");
		return 1;
	}

	char buf[100];
	int count = 0, max_len = 0;
	while(fgets(buf, sizeof(buf), fp) != NULL) {
		count++;
		int len = (int)strlen(buf);
		if(buf[len - 1] == '\n') {
			len--;
		}
		if(len > max_len) max_len = len;
	}

	fclose(fp);

	printf("lines = %d\n", count);
	printf("longest = %d\n", max_len);

	return 0;
}
