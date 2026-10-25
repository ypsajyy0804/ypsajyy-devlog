#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} vec;

void vec_reserve(vec* v, size_t n){
  if(v->capacity >= n){
    return;
  }else{
  int* temp = realloc(v->data, sizeof(int) * n);
  if(temp == NULL) {
    printf("realloc failed\n");
    return;
  }else v->data = temp;
  v->capacity = n;
  }
}

void vec_resize(vec* v, size_t n){
  if(n > v->size) {
    if(n > v->capacity) {
      vec_reserve(v,n);
    }
    for(size_t i = v->size; i < n; i++) {
      v->data[i] = 0;
    }
  }
  v->size = n;
}

int main() {
  vec* v = malloc(sizeof(vec));
  if(v == NULL) {
    printf("malloc failed\n");
    return 1;
  }
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;

  vec_reserve(v, 100);
  printf("第一次 reserve 后的 capacity = %zu\n", v->capacity);

  vec_reserve(v, 0);
  printf("第二次 reserve （n = 0）后的 capacity = %zu\n", v->capacity);

  printf("调用 resize 前的 size = %zu\n", v->size);
  vec_resize(v, 3);
  printf("调用 resize 后的 size = %zu\n", v->size);
  for(size_t i = 0; i < v->size; i++) {
    printf("v->data[%zu] = %d\n", i, v->data[i]);
  }

  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
  free(v);
  v = NULL;
  return 0;
}