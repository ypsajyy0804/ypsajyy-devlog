#include <stdio.h>

struct Student {
  int id;
  char name[50];
};

int main() {
  struct Student student1 = {1, "Bob"};
  printf("ID: %d, Name: %s\n", student1.id, student1.name);

  return 0;
}