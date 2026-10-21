#include <stdio.h>
int main(void) {
  int a[3] = {1, 2, 3};
  a[3] = 99;          // 越界：合法下标只有 0..2
  printf("%d\n", a[3]);
  return 0;
}