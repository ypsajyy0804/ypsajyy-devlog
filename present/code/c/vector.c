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
  if(v->data == NULL){
    v->data = malloc(sizeof(int));
    if(v->data == NULL){
      printf("malloc failed\n");
      return;
    }else v->capacity = 1;
  }

  if(v->size == v->capacity){
    size_t new_capacity;
    if(v->capacity == 0) new_capacity = 1;
    else new_capacity = v->capacity * 2;

    int* new_data = malloc(sizeof(int) * new_capacity);
    if(new_data == NULL){
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

void vec_reserve(Vec* v, size_t n){
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

void vec_resize(Vec* v, size_t n){
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

void vec_insert(Vec* v, size_t pos, int x) {
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

void vec_erase(Vec* v, size_t pos) {
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
  Vec vec;
  Vec* p = &vec;
  vec_init(p);

  vec_reserve(p, 5);

  vec_push(p, 1);
  vec_push(p, 2);
  vec_push(p, 3);
  vec_push(p, 4);  
  printf("初始数组：\n");
  for(size_t i = 0; i < 4; i++){
    printf("%d\n", p->data[i]);
  }

  vec_insert(p, 2, 9);
  printf("插入 9 :\n");
  for(size_t i = 0; i < 5; i++){
    printf("%d\n", p->data[i]);
  }

  vec_erase(p, 0);
  printf("删除一个元素：\n");
  for(size_t i = 0; i < 4; i++){
    printf("%d\n", p->data[i]);
  }

  Vec v;
  Vec* q = &v;
  vec_init(q);
  vec_reserve(q, 100);
  printf("capacity = %zu, size = %zu\n", q->capacity, q->size);

  vec_free(p);
  vec_free(q);
  
  return 0;
}