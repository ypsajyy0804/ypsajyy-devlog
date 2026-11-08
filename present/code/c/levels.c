#include <stdio.h>

int main(void) {
    int x = 100;
    int *p = &x;
    int **pp = &p;

    printf("&x   = %p\n", (void *)&x);
    printf("p    = %p\n", (void *)p);
    printf("&p   = %p\n", (void *)&p);
    printf("pp   = %p\n", (void *)pp);
    printf("*p   = %d\n", *p);
    printf("**pp = %d\n", **pp);
    return 0;
}
