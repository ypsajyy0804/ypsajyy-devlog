#include <stddef.h>
#ifndef VEC_H
#define VEC_H

typedef struct {
	int* data;
	size_t size;
	size_t capacity;
} Vec;

void vec_init(Vec* v);

void vec_push(Vec* v, int x);

void vec_free(Vec* v);

void vec_reserve(Vec* v, size_t n);

void vec_resize(Vec* v, size_t n);

void vec_insert(Vec* v, size_t pos, int x);

void vec_erase(Vec* v, size_t pos);

#endif
