#include <stdio.h>

void set_first(const char *s) {
    s[0] = 'X';
}

char *get(const char *s) {
    return s;
}

int main(void) {
    set_first("hello");
    printf("%s\n", get("hello"));
    return 0;
}
