#include <stdio.h>

struct A { char c; int  i; char d; };
struct B { int  i; char c; char d; };
struct C { char c; char d; int  i; };
struct D { char c; long l; char d; };
struct E { char c; char pad[3]; int i; char d; };

int main(void) {
    printf("A=%zu B=%zu C=%zu D=%zu E=%zu\n",
           sizeof(struct A), sizeof(struct B), sizeof(struct C),
           sizeof(struct D), sizeof(struct E));
    return 0;
}
