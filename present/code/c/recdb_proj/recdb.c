#include "recdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int  rec_write(const char *path) {
	FILE *fp = fopen(path, "rb");

	if(fp == NULL){
		fp = fopen(path, "wb");		// 没有文件就创建

		if(fp == NULL) {
			perror("open");
			exit(1);
		}

		struct Rec rec[] = {{1, "alice", 90.50}, {2, "bob", 85.00}, {3, "carol", 77.25}};

		size_t n = fwrite(rec, sizeof(struct Rec), 3, fp);	// 将数据写入文件 

		if(n != 3) {
			perror("fwrite");
			exit(1);
		}

		fclose(fp);

		return (int)n;
	}

	return 0;
}

int  rec_show (const char *path) {
	FILE *fp = fopen(path, "rb");

	if(fp == NULL) {
		perror("fopen");
		exit(1);
	}

	struct Rec rec;	// 创建一个结构体对象来存放读取的数据
	int count = 0;

	while(fread(&rec, sizeof(struct Rec), 1, fp) == 1) {
		count++;
		printf("id=%d name=%s score=%.2f\n", rec.id, rec.name, rec.score); // 逐条打印数据
	}

	fclose(fp);

	if(count == 0) return 0;

	return count;
}

int  rec_patch(const char *path, int id, double score) {
	FILE *fp = fopen(path, "rb+");

	if(fp == NULL) {
		perror("fopen");
		exit(1);
	}

	struct Rec rec;

	int index = 0;	// 用来记录目标 id 在第‘几’条数据
	int found = 0;	// 用来判断是否存在目标 id

	while(fread(&rec, sizeof(struct Rec), 1, fp) == 1) {
		if(rec.id == id){
			found = 1;
			break;	// 发现目标 id，此时 index 保存了目标 id 在哪一条数据
		}

		index++;
	}

	if(!found) {
		fclose(fp);
		return 0;
	}

	// 计算目标 id 对应 score 的偏移
	long score_offset = index * sizeof(struct Rec) + (long)offsetof(struct Rec, score); //offsetof 用于快速找到结构体中成员变量的偏移
	
	fseek(fp, score_offset, SEEK_SET);

	size_t n = fwrite(&score, sizeof(double), 1, fp);

	if(n != 1){
		perror("fwrite");
		exit(1);
	}

	fclose(fp);

	return 1;
}
