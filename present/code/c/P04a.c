// P04a.c —— 野指针：从来没指向过有效内存
#include <stdio.h>
int main(void) {
  int *p;
  *p = 10;
  return 0;
}