#include <stdio.h>

void f(int a[5]) {
  printf("函数里 sizeof(a) = %zu\n", sizeof(a));
}

int main(void) {
  int a[5];
  printf("main 里 sizeof(a) = %zu\n", sizeof(a));
  f(a);
  return 0;
}