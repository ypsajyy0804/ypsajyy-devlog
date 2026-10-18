#include <stdio.h>
#include <stdlib.h>

int main(){
  int *a = malloc(100 * sizeof(int));
  a[0] = 12345;
  free(a);
  int *b = malloc(100 * sizeof(int));
  printf("%d\n", b[0]);
}
