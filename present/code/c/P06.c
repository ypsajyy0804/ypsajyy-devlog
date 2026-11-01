#include <stdio.h>

int main(void) {
  int matrix[3][4] = {
    { 0, 1, 2, 3 },
    { 4, 5, 6, 7 },
    { 8, 9, 10, 11 }
  };
  int *p = matrix[0];    /* 指向一个 int */
  int (*row)[4] = matrix;       /* 指向一行 int[4] */
    
  printf("p = %p\n", p);
  printf("p + 1 = %p\n", (p + 1));
  printf("(p + 1) - p = %ld\n", ((char* )(p+1) - (char* )p));
  printf("row = %p\n", row);  
  printf("row + 1 = %p\n", (row + 1));
  printf("(row + 1) - row = %ld\n", ((char* )(row + 1) - (char* )row));
}
