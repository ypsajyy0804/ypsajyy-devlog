#include <stdio.h>

int main() {
  printf("%ld\n",sizeof(char));       //1
  printf("%ld\n",sizeof(short));      //2
  printf("%ld\n",sizeof(int));        //4
  printf("%ld\n",sizeof(long long));  //8
  printf("%ld\n",sizeof(long));       //4
  printf("%ld\n",sizeof(float));      //4
  printf("%ld\n",sizeof(double));     //8
  printf("%ld\n",sizeof(size_t));     //8
  printf("%ld\n",sizeof(char*));      //8
  printf("%ld\n",sizeof(int*));       //8
  printf("%ld\n",sizeof(double*));    //8
  printf("%ld\n",sizeof(void*));      //8

  struct {
    int a;
    char b;
    float c;
  } s;
  printf("%ld\n",sizeof(s));        //12
}