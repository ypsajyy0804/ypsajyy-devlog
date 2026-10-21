#include <stdio.h>

void bad(int* p){
   p = NULL; 
}
void good(int* *pp){
   *pp = NULL;
}

int main(void) {
  int x = 1;
  int *p = &x;
  bad(p);
  printf("bad  之后 p 是 %s\n", p ? "非 NULL" : "NULL");

  int *q = &x;
  good(&q);
  printf("good 之后 q 是 %s\n", q ? "非 NULL" : "NULL");
  return 0;
}