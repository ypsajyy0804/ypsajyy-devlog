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

void vec_push(Vec* v, int x){
  if(v->data ==NULL){
    v->data = malloc(sizeof(int));
    if(v->data ==NULL){
      printf("malloc failed\n");
      return;
    }else v->capacity = 1;
  }

  if(v->size == v->capacity){
    size_t new_capacity = v->capacity * 2;
    int* new_data = malloc(sizeof(int) * new_capacity);
    if(new_data ==NULL){
      printf("malloc failed\n");
      return;
    }else{
      for(size_t i = 0; i < v->size; i++){
        new_data[i] = v->data[i];
      }
    }
    free(v->data);
    v->data = new_data;
    v->capacity = new_capacity;
  }

  v->data[v->size] = x;
  v->size++;
}

void vec_free(Vec* v){
  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}

int main() {
  Vec vec;
  Vec* p = &vec;
  vec_init(p);

  //任务二
  // printf("size = %zu\n", p->size);
  // printf("capacity == %zu\n", p->capacity);
  // printf("data = %p\n", p->data);

  for(int i = 0; i < 16; i++){
    vec_push(p, i);
    printf("size = %zu , capacity = %zu\n", p->size, p->capacity);
  }

  vec_free(p);

  return 0;
}