#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* next;
  struct Node* prev;
} Node;

int main() {
  Node* p1 = malloc(sizeof(Node));
  Node* p2 = malloc(sizeof(Node));
  Node* p3 = malloc(sizeof(Node));

  if(p1 == NULL || p2 == NULL || p3 == NULL)
  return 1;

  p1->data =100;  //等价于（*p1）.data = 100;
  p2->data = 200;
  p3->data = 300;

  p1->next = p2;
  p2->next = p3;
  p3->next = NULL;

  p1->prev = NULL;
  p2->prev = p1;
  p3->prev = p2;

  printf("%d\n", p1->data);
  printf("%d\n", p2->data);
  printf("%d\n", p3->data);
  printf("%d\n", p2->prev->data);
  printf("%d\n", p3->prev->data);
  printf("%d\n", p3->prev->prev->data);
  printf("%d\n", p3->prev->next->data);

  free(p1);
  free(p2);
  free(p3);

  return 0;
}