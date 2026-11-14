#include <stdio.h>

int main(void) {
    printf("%d %d %d\n", 5 & 3, 5 | 3, 5 ^ 3);
    printf("%d %d\n", ~5, -8 >> 1);
    printf("%u\n", 1u << 31);
    return 0;
}
