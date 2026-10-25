#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  struct Node* next;
  int val;
} Node;

Node* insert(Node* head, int pos, int val){
  Node* prev = head;
  Node* newnode = malloc(sizeof(Node));
  newnode->val = val;

  if(pos == 0){
    newnode->next = head;
    head = newnode;
  }else{
    for(int i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }
    newnode->next = prev->next;
    prev->next = newnode;
  }
  return head;
}

Node* erase(Node* head, int pos){
  Node* prev = head;
  if(pos == 0){
    Node* temp = head;
    head = head->next;
    free(temp);
  }else {
    for(int i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }
    Node* temp = prev->next;
    prev->next = temp;
    free(temp);
  }
  return head;
}

void node_list(Node* head){
  Node* cur = head;
  while(cur != NULL){
    if(cur->next != NULL) printf("%d->", cur->val);
    else printf("%d",cur->val);
    cur = cur->next;
  }
  printf("\n");
}

void node_free(Node* head) {
  Node* cur = head;
  while(cur != NULL){
    Node* temp = cur->next;
    free(cur);
    cur = temp;
  }
}

Node* reverse_list(Node* head){
  Node* cur = head->next;
  Node* temp = head;
  head->next = NULL;
  while(cur != NULL) {
    Node* prev = cur->next;
    cur->next = temp;
    temp = cur;
    cur = prev;
  }
  head = temp;
  return head;
}

int main() {
  Node* head = NULL;
  head = insert(head, 0, 1);
  head = insert(head, 1, 2);
  head = insert(head, 2, 3);
  head = insert(head, 3, 4);
  head = insert(head, 2, 9);
  node_list(head);

  head = erase(head, 0);
  node_list(head);

  head = reverse_list(head);
  node_list(head);

  node_free(head);
  return 0;
}