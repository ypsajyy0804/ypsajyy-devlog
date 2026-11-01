#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* next;
} Node;

Node* clist_push_back(Node* tail, int v){
	if(tail == NULL){
		tail = malloc(sizeof(Node));
		tail->val = v;
		tail->next = tail;
	}else{
		Node* prev = tail;
		Node* head = tail->next;
		tail = malloc(sizeof(Node));
		tail->val = v;
		prev->next = tail;
		tail->next = head;
	}
	return tail;
}

void clist_print(Node* tail){
	if(tail == NULL) printf("循环列表为空");
	else{
		Node* head = tail->next;
		Node* cur = head->next;
		if(head->next != head) printf("%d->", head->val);
		else printf("%d", head->val);
		while(cur != head){
			if(cur->next != head) printf("%d->", cur->val);
			else printf("%d", cur->val);
			cur = cur->next;
		}
	}
}

void clist_free(Node* tail){
	if(tail == NULL) return;
	Node* head = tail->next;
	Node* cur = head->next;
	while(cur != head){
		Node* temp = cur->next;
		free(cur);
		cur = temp;
	}
	free(head);
}

int main() {
	Node* t = NULL;
	t = clist_push_back(t, 1);
	t = clist_push_back(t, 2);
	t = clist_push_back(t, 3);
	t = clist_push_back(t, 4);
	clist_print(t);
	clist_free(t);
	t = NULL;
}
