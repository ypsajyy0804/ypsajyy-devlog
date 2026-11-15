#include <stdio.h>
#include <stdlib.h>

struct Rec {
    int    id;
    char   name[16];
    double score;
};

int main(){
	FILE *fp = fopen("rec.txt", "w");

	if(fp == NULL){
		perror("fopen");
		exit(1);
	}

	struct Rec rec[] = {{1, "alice", 90.50}, {2, "bob", 85.00}, {3, "carol", 77.25}};

	for(int i = 0; i < 3; i++){
		fprintf(fp, "%d %s %.2lf\n", rec[i].id, rec[i].name, rec[i].score);	
	}

	fseek(fp, 0, SEEK_END);
	long txt_size = ftell(fp);

	fp = fopen("rec.bin", "rb");

	fseek(fp, 0, SEEK_END);
	long binary_size = ftell(fp);

	printf("binary = %ld\n", binary_size);
	printf("text = %ld\n", txt_size);

	fclose(fp);
	return 0;
}
