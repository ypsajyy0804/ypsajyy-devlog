#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[20];
    char *key = buf;

    strcpy(buf, "hello");
    printf("before: %s\n", key);

    strcpy(buf, "world");
    printf("after:  %s\n", key);

    return 0;
}
