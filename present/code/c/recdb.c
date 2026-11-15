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
	if(argc < 3){
		fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
		return 1;
	}

	if(strcmp(argv[2], "write") == 0){
		FILE *fp = fopen(argv[1], "rb");

		if(fp == NULL){
			FILE *fp = fopen(argv[1], "wb");
			
			if(fp == NULL){
				perror("fopen");
				exit(1);
			}

			struct Rec rec[] = {{1, "alice", 90.50}, {2, "bob", 85.00}, {3, "carol", 77.25}};
			int num = fwrite(rec, sizeof(struct Rec), 3, fp);

			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			printf("wrote %d records, %zu bytes\n", num, size);

			fclose(fp);
			return 0;
		}else {
			printf("exists, skip\n");
			fclose(fp);
		}
	}

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

	if(strcmp(argv[2], "patch") == 0){
		if(argc != 5){
			fprintf(stderr, "usage: %s <file> patch <id> <score>\n", argv[0]);
			return 1;
		}

		FILE *fp = fopen(argv[1], "rb+");

		if(fp == NULL){
			perror("fopen");
			exit(1);
		}

		int target_id = atoi(argv[3]);
		double new_score = atof(argv[4]);
		struct Rec rec;
		long index = 0;
		int found = 0;

		while(fread(&rec, sizeof(struct Rec), 1, fp) == 1){
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

		long score_offset = index * sizeof(struct Rec) + (long)offsetof(struct Rec, score);
		
		fseek(fp, score_offset, SEEK_SET);
		fwrite(&new_score, sizeof(double), 1, fp);

		printf("patched id=%d\n", target_id);

		fclose(fp);
		return 0;
	}
	return 0;
}












































