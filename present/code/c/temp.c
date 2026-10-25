#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} Vec;

void vec_init(Vec* v){
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}

void vec_free(Vec* v){
  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}

int mian(){
  Vec v;
  Vec* p = &v;

  vec_init(p);
  // vec_free(p);
  free(p);

  return 0;
}