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

	if(strcmp(argv[2], "write") == 0){
		FILE *fp = fopen(argv[1], "r");
		if(fp != NULL) printf("exists, skip\n");
		else{
			fp = fopen(argv[1], "w");
			if(fp != NULL){
				struct Rec rec[3] = {
					{1, "alice", 90.50},
					{2, "bob", 85.00},
					{3, "carol", 77.25}
				};
				for(int i = 0; i < 3; i++){
					fprintf(fp, "id=%d name=%s score=%.2f\n",
							rec[i].id,
							rec[i].name,
							rec[i].score);
				}
				fseek(fp, 0, SEEK_END);
				size_t size = ftell(fp);

				printf("wrote 3 records,%zu bytes\n", size);
				fclose(fp);
				return 0;
			}else{
				perror("fopen");
				exit(1);
			}
		}
	}

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

	if(strcmp(argv[2], "patch") == 0){
		if(argc != 5){
			fprintf(stderr,  "usage: %s <file> <command> [args...]\n", argv[0]);
			return 1;
		}
		int target_id = atoi(argv[3]);
		double new_score = atof(argv[4]);

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

			if(sscanf(buf, "id=%d name=%15s score=%lf", &id, name, &old_score) != 3) continue;

			if(target_id == id){
				char *p = strstr(buf, "score=");

				if(p == NULL){
					fclose(fp);
					return 1;
				}

				long score_offset = line_start + (p - buf) + strlen("score=");

				fseek(fp, score_offset, SEEK_SET);

				fprintf(fp, "%.2f", new_score);
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
























































