#include <stdio.h>

int counter = 0;

static void bump(void) { counter++; }

void tick(void) { bump(); }
void report(void) { printf("counter = %d\n", counter); }
