// P04b.c —— 悬垂指针：指向的内存已经被还回去了
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *q = malloc(sizeof(int));
  free(q);
  *q = 10;
  return 0;
}