#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node* next;
} Node;

  Node* insert(Node* head, int pos, int val){
    Node* newnode = malloc(sizeof(Node));
    newnode->val = val;
    Node* prev = head;
    if(pos == 0){
      newnode->next = head;
      head = newnode;
    }
    else{
      for(int i = 0; i < pos - 1; i++){
        prev = prev->next;
      }
      newnode->next = prev->next;
      prev->next = newnode;
    }
    return head;
  };

  Node* erase(Node* head, int pos){
    Node* prev = head;
    if(pos == 0){
      head = prev->next;
    }
    else{
      for(int i = 0; i < pos - 1; i++){
        prev = prev->next;
      }
      Node* temp = prev->next;
      prev->next = temp->next;
      free(temp);
    }
    return head;
  };

void print_list(Node* head){
  Node* cur = head;

  while(cur != NULL){
    printf("%d ", cur->val);
    cur = cur->next;
  }
  printf("\n");
}

int main() {
  //测试组1
  // Node* head = NULL;
  // head = insert(head, 0, 9);

  // print_list(head);

  //测试组2 测试组3 测试4 测试5
  // Node* head = malloc(sizeof(Node));
  // Node* a = malloc(sizeof(Node));
  // Node* b = malloc(sizeof(Node));
  // Node* c = malloc(sizeof(Node));

  // head->val = 1;
  // a->val = 2;
  // b->val = 3;
  // c->val = 4;

  // head->next = a;
  // a->next = b;
  // b->next = c;
  // c->next = NULL;

  //测试2
  // head = insert(head, 0, 9);

  //测试3
  // head = insert(head, 2, 9);

  //测试4
  // head = insert(head, 3, 9);

  //测试5
  // head = erase(head, 0);

  //测试6
  // head = erase(head, 3);

  // print_list(head);

  //测试7
  Node* head = malloc(sizeof(Node));
  head->val = 1;
  head->next = NULL;

  head = erase(head, 0);

  head == NULL? printf("NULL\n"):printf("非 NULL\n");

  return 0;
}