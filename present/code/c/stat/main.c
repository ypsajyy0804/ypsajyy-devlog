#include <stdio.h>
#include "counter.h"

int main(void) {
    counter_inc();
    printf("inc1 = %d\n", counter_get());
    counter_inc();
    printf("inc2 = %d\n", counter_get());
    counter_inc();
    printf("inc3 = %d\n", counter_get());
    printf("get = %d\n", counter_get());

    for (int i = 0; i < 1005; i++) counter_inc();
    printf("cap = %d\n", counter_get());

    return 0;
}
