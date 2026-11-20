#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rec {
    int    id;
    char   name[16];
    double score;
};

int main(int argc, char **argv){
		if(argc < 3){
			fprintf(stderr,  "usage: %s <file> <command> [args...]\n", argv[0]);
			return 1;
		}

	// write 的情况
	if(strcmp(argv[2], "write") == 0){
		FILE *fp = fopen(argv[1], "r");
		if(fp != NULL) printf("exists, skip\n");
		else{
			fp = fopen(argv[1], "w");	//文件不存在就创建
			if(fp != NULL){
				struct Rec rec[3] = {
					{1, "alice", 90.50},
					{2, "bob", 85.00},
					{3, "carol", 77.25}
				};
				for(int i = 0; i < 3; i++){
					//利用 fprintf 将格式化文字写入文件
					fprintf(fp, "id=%d name=%s score=%.2f\n",
							rec[i].id,
							rec[i].name,
							rec[i].score);
				}
				fseek(fp, 0, SEEK_END);		// 将光标移动到文本末尾
				size_t size = ftell(fp);	// 获取文本的大小

				printf("wrote 3 records,%zu bytes\n", size);
				fclose(fp);
				return 0;
			}else{
				perror("fopen");
				exit(1);
			}
		}
	}

	// show 的情况
	if(strcmp(argv[2], "show") == 0){
		FILE *fp = fopen(argv[1], "r");
		if(fp != NULL){
			char buf[1000];
			while(fgets(buf, sizeof(buf), fp) != NULL){
				printf("%s", buf);
			}
			fclose(fp);
			return 0;
		}else{
			perror("fopen");
			exit(1);
		}
	}

	// patch 的情况
	if(strcmp(argv[2], "patch") == 0){
		if(argc != 5){
			fprintf(stderr,  "usage: %s <file> <command> [args...]\n", argv[0]);
			return 1;
		}

		int target_id = atoi(argv[3]);	// 获取目标 id
		double new_score = atof(argv[4]);	// 获取新的成绩数据

		FILE *fp = fopen(argv[1], "r+");

		if(fp == NULL){
			perror("fopen");
			exit(1);
		}

		char buf[1000];

		while(1){
			long line_start = ftell(fp);
			if(fgets(buf, sizeof(buf), fp) == NULL) break;

			int id;
			char name[16];
			double old_score;

			//sscanf：从字符数组 buf 中解析指定格式的数据，取入上面定义的三个变量中
			//外加一层判断，若读的个数不对，放弃这一行数据，进入下一层循环
			if(sscanf(buf, "id=%d name=%15s score=%lf", &id, name, &old_score) != 3) continue;

			if(target_id == id){
				char *p = strstr(buf, "score=");	//利用 strstr 快速获取字符“score=”的地址

				if(p == NULL){
					fclose(fp);
					return 1;
				}

				long score_offset = line_start + (p - buf) + strlen("score=");//获取score的偏移

				fseek(fp, score_offset, SEEK_SET);	//移动光标到偏移前

				fprintf(fp, "%.2f", new_score);		//利用 fprintf 替换 score
				printf("patched id=%d\n", target_id);

				fclose(fp);
				return 0;
			}
		}
		printf("id = %d is not found", target_id);

		fclose(fp);
		return 1;
	}
	return 0;
}
