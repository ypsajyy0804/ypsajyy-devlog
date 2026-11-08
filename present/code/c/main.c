#include "vec.h"
#include <stdio.h>

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
