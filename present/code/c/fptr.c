#include <stdio.h>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    int (*f)(int, int);

    f = add;
    printf("f(2,3) = %d\n", f(2, 3));

    f = mul;
    printf("f(2,3) = %d\n", f(2, 3));

    printf("sizeof(f) = %zu\n", sizeof(f));
    return 0;
}
