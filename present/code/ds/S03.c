#include <stdio.h>
#include <stdlib.h>

#define STACK_CAP 8

typedef struct {
        int data[STACK_CAP];
        int top;            /* 指向下一个可用的位置 */
} Stack;

void stack_init(Stack *s){      /* 把栈清空 */
        s->top = 0;
}

int  stack_push(Stack *s, int v){       /* 满了返回 0；成功返回 1 */
        if(s->top == STACK_CAP) return 0;
        s->data[s->top] = v;
        s->top++;
        return 1;
}

int  stack_pop(Stack *s, int *out){     /* 空返回 0（不许碰 *out）；成功写 *out 返回 1 */
        if(s->top == 0) return 0;
        *out = s->data[s->top-1];
        s->top--;
        return 1;
}

int  stack_is_empty(const Stack *s){    /* 空返回 1，否则返回 0 */
        return s->top == 0;
}

int is_pair(int left, int right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

int bracket_match(const char *s){	/* 完全匹配返回 1，否则返回 0 */
	Stack stack;
	stack_init(&stack);
	while(*s){
		if(*s == '(' || *s == '[' || *s == '{'){
			if(stack_push(&stack, *s) == 0) return 0;
			s++;
			continue;
		}else if(*s == ')' || *s == ']' || *s == '}'){
			if(stack_is_empty(&stack) == 1) return 0;
			int out;
			if(is_pair(stack.data[stack.top-1], *s) == 1) {
				if(stack_pop(&stack, &out) == 0) return 0;
				s++;
				continue;
			}
			return 0;
		}else s++;
	}
  if(stack_is_empty(&stack) == 1) return 1;
  else return 0;
}

int main() {
	printf("%s -> %d\n", "()",       bracket_match("()"));
	printf("%s -> %d\n", "([{}])",   bracket_match("([{}])"));
	printf("%s -> %d\n", "(]",       bracket_match("(]"));
	printf("%s -> %d\n", "(()",      bracket_match("(()"));
	printf("%s -> %d\n", ")(",       bracket_match(")("));
	printf("%s -> %d\n", "a(b)c[d]", bracket_match("a(b)c[d]"));
}
