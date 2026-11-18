#ifndef RECDB_H
#define RECDB_H

struct Rec {
	int id;
	char name[16];
	double score;
};

int rec_write(const char *path);

int rec_show(const char*path);

int rec_patch(const char *path, int id, double score);

#endif
