#include <stdio.h>

int main() {
  printf("%zd\n",sizeof(char));       //1
  printf("%zd\n",sizeof(short));      //2
  printf("%zd\n",sizeof(int));        //4
  printf("%zd\n",sizeof(long long));  //8
  printf("%zu\n",sizeof(long));       //8
  printf("%zd\n",sizeof(float));      //4
  printf("%zd\n",sizeof(double));     //8
  printf("%zd\n",sizeof(size_t));     //8
  printf("%zd\n",sizeof(char*));      //8
  printf("%zd\n",sizeof(int*));       //8
  printf("%zd\n",sizeof(double*));    //8
  printf("%zd\n",sizeof(void*));      //8

  struct {
    int a;
    char b;
    float c;
  } s;
  printf("%ld\n",sizeof(s));        //12
}
