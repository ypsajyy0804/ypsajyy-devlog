#include <stdio.h>

void tick(void);
void report(void);
int counter;

int main(void) {
    tick();
    tick();
    tick();
    report();
    printf("from main: %d\n", counter);
    return 0;
}
