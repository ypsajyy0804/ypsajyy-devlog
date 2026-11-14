#include <stdio.h>

#define SQR(x)  x * x
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

int main(void) {
    printf("%d\n", SQR(1 + 2));
    printf("%d\n", MAX(1, 2));
    printf("%d\n", 100 / SQR(2));
    return 0;
}
