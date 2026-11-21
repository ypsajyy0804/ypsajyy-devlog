#include <stdio.h>
#include <stdlib.h>

typedef struct N {
	int v;
	struct N *next;
} N;

void del_head(N *head) {
    if (head == NULL) return;
    head = head->next;
}

int main(void) {
    N *a = malloc(sizeof(N));
    N *b = malloc(sizeof(N));
    a->v = 1; a->next = b;
    b->v = 2; b->next = NULL;

    del_head(a);

    printf("main 里的 a 指向: %d\n", a->v);

    free(a);
    free(b);
    return 0;
}
