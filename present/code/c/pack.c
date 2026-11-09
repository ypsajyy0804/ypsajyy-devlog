#include <stdio.h>

struct M_before {
    char   a;
    double b;
    int    c;
    char   d;
};

struct M_after {
    char a;
    char d;
    int c;
    double b;
};

int main(){
	struct M_before a;
	struct M_after b;

	printf("before = %zu\n", sizeof(a));
	printf("after = %zu\n", sizeof(b));

	return 0;
}
