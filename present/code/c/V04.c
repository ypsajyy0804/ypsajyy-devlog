#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} vec;

void vec_insert(vec* v, size_t pos, int x) {
  if(pos > v->size) {
    printf("pos out of range\n");
    return;
  }

  if(v->capacity <= v->size){
    size_t newcapacity;
    if(v->capacity == 0){
      newcapacity = 1;
    }else{
      newcapacity = v->capacity * 2;
    }
    int* temp = realloc(v->data, sizeof(int) * newcapacity);
    if(temp == NULL) {
      printf("realloc failed\n");
      return;
    }else {
      v->data = temp;
      v->capacity = newcapacity;
    }
  }
    
  for(size_t i = 0; i < v->size - pos; i++) {
    v->data[v->size - i] = v->data[v->size - (i + 1)];
  }

  v->size++;
  v->data[pos] = x;
}

void vec_erase(vec* v, size_t pos) {
  if(pos >= v->size) {
    printf("pos out of range\n");
    return;
  }
  for(size_t i = pos; i < v->size - 1; i++) {
    v->data[i] = v->data[i + 1];
  } 
  v->size--;
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

  for(size_t i = 0; i < 4; i++){
    vec_insert(v, i, i + 1);
  }
  printf("原容器内的元素：\n");
  for(size_t i = 0; i < v->size; i++){
    printf("v->data[%zu] S= %d\n", i, v->data[i]);
  }

  printf("在第2个元素后插入 9：\n");
  vec_insert(v, 2, 9);
    for(size_t i = 0; i < v->size; i++){
      printf("v->data[%zu] S= %d\n", i, v->data[i]);
    }

  printf("删除第1个元素：\n");
  vec_erase(v, 0);
  for(size_t i = 0; i < v->size; i++){
    printf("v->data[%zu] S= %d\n", i, v->data[i]);
  }
  
  free(v->data);
  free(v);
  return 0;
}