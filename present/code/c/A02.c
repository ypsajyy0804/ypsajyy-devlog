#include <stdio.h>

int main() {
  printf("%zu\n",sizeof(char));       //1
  printf("%zu\n",sizeof(short));      //2
  printf("%zu\n",sizeof(int));        //4
  printf("%zu\n",sizeof(long long));  //8
  printf("%zu\n",sizeof(long));       //8
  printf("%zu\n",sizeof(float));      //4
  printf("%zu\n",sizeof(double));     //8
  printf("%zu\n",sizeof(size_t));     //8
  printf("%zu\n",sizeof(char*));      //8
  printf("%zu\n",sizeof(int*));       //8
  printf("%zu\n",sizeof(double*));    //8
  printf("%zu\n",sizeof(void*));      //8

  printf("%zu\n", sizeof(int));
  printf("%ld\n", (long)sizeof(int));
  printf("%d\n", sizeof(int));

  struct {
    int a;
    char b;
    float c;
  } s;
  printf("%zu\n",sizeof(s));        //12

  printf("%d\n", (size_t)5000000000);

  return 0;
}
