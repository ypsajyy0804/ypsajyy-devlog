#include <stdio.h>

int main() {
  int a = 0, b = 0, c = 0;
  printf("请输入三个整数：");
  scanf("%d %d %d", &a, &b, &c);
  if(a < b && a < c) {
    printf("%d ", a);
    if(b < c) {
      printf("%d ", b);
      printf("%d\n", c);
    }else {
      printf("%d ", c);
      printf("%d\n", b);
    }
  }else if(b < a && b < c){
    printf("%d ", b);
    if(a < c){
      printf("%d ", a);
      printf("%d\n", c);
    }else {
      printf("%d ", c);
      printf("%d\n", a);
    }
  }else {
    printf("%d ", c);
    if(a < b) {
      printf("%d ", a);
      printf("%d\n", b);
    }else {
      printf("%d ", b);
      printf("%d\n", a);
    }
  }

  return 0;
}
