#include <stdio.h>
#include <stdlib.h>

#define STACK_CAP 8

typedef struct {
	int data[STACK_CAP];
        int top;            /* 指向下一个可用的位置 */
} Stack;

void stack_init(Stack *s){	/* 把栈清空 */
	s->top = 0;
}

int  stack_push(Stack *s, int v){	/* 满了返回 0；成功返回 1 */
	if(s->top == STACK_CAP) return 0;
	s->data[s->top] = v;
	s->top++;
	return 1;
}

int  stack_pop(Stack *s, int *out){	/* 空返回 0（不许碰 *out）；成功写 *out 返回 1 */
	if(s->top == 0) return 0;
	*out = s->data[s->top-1];
	s->top--;
	return 1;
}

int  stack_is_empty(const Stack *s){	/* 空返回 1，否则返回 0 */
	if(s->top == 0) return 1;
	return 0;
}

int main(){
	Stack s;
	stack_init(&s);
	printf("init: is_empty=%d\n", stack_is_empty(&s));

	printf("push %d -> %d\n", 3, stack_push(&s, 3));
	printf("push %d -> %d\n", 7, stack_push(&s, 7));
	printf("push %d -> %d\n", 11, stack_push(&s, 11));

	int out;
	stack_pop(&s, &out);
	printf("pop -> %d, is_empty=%d\n", out, stack_is_empty(&s));

	stack_push(&s, 0);
	stack_push(&s, 0);
	stack_push(&s, 0);
	stack_push(&s, 0);
	stack_push(&s, 0);
	stack_push(&s, 0);
	printf("push 满 -> %d\n", stack_push(&s, 99));

	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	stack_pop(&s, &out);
	printf("pop 空 -> %d\n", stack_pop(&s, &out));
}
