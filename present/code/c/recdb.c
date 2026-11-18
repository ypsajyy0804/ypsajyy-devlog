#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct Rec {
    int    id;
    char   name[16];
    double score;
};

int main(int argc, char **argv){
	//判断命令额外参数是否少于两个
	if(argc < 3){
		fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
		return 1;
	}

	// write 的情况
	if(strcmp(argv[2], "write") == 0){
		FILE *fp = fopen(argv[1], "rb");

		// 没有文件则创建
		if(fp == NULL){
			FILE *fp = fopen(argv[1], "wb");
			
			if(fp == NULL){
				perror("fopen");
				exit(1);
			}

			struct Rec rec[] = {{1, "alice", 90.50}, {2, "bob", 85.00}, {3, "carol", 77.25}};
			int num = fwrite(rec, sizeof(struct Rec), 3, fp);	// 把整个结构体数组写入文件 

			fseek(fp, 0, SEEK_END);		// 光标移动到结尾
			size_t size = ftell(fp);	// 读取文件大小
			printf("wrote %d records, %zu bytes\n", num, size);

			fclose(fp);
			return 0;
		}else {
			printf("exists, skip\n");
			fclose(fp);
		}
	}

	// show 的情况
	if(strcmp(argv[2], "show") == 0){
		FILE *fp = fopen(argv[1], "rb");

		if(fp == NULL){
			perror("fopen");
			exit(1);
		}

		struct Rec rec[3];

		size_t n = fread(rec, sizeof(struct Rec), 3, fp);

		for(int i = 0; i < (int)n; i++){
			printf("id=%d name=%s score=%.2lf\n", rec[i].id, rec[i].name, rec[i].score);
		}
		fclose(fp);
		return 0;
	}

	// patch 的情况
	if(strcmp(argv[2], "patch") == 0){

		// 判断参数是否为五个
		if(argc != 5){
			fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
			return 1;
		}

		FILE *fp = fopen(argv[1], "rb+");	// “rb+” 为以二进制写入形式读写模式

		if(fp == NULL){
			perror("fopen");
			exit(1);
		}

		int target_id = atoi(argv[3]);		// 捕获参数中的目标 id
		double new_score = atof(argv[4]);	// 捕获参数中的新 score
		struct Rec rec;
		long index = 0;		// 用于记录第‘几’条信息
		int found = 0;		// 用于判断目标 id 是否存在

		while(fread(&rec, sizeof(struct Rec), 1, fp) == 1){
			// 如果找到目标 id，立即退出循环，此时 index 记录了目标 id 在第‘几’条记录
			if(rec.id == target_id){
				found = 1;
				break;
			}
			index++;
		}

		if(!found){
			printf("id=%d is not found\n", target_id);
			fclose(fp);
			return 1;
		}

		// 计算目标 id 对应 score 在文件中的偏移
		long score_offset = index * sizeof(struct Rec) + (long)offsetof(struct Rec, score);	//offsetof() 快速计算结构体开头到 score 的字节数
		
		fseek(fp, score_offset, SEEK_SET);	// 光标移动到 score 的偏移
		fwrite(&new_score, sizeof(double), 1, fp);	// 新 score 覆盖原 score

		printf("patched id=%d\n", target_id);

		fclose(fp);
		return 0;
	}
	return 0;
}
