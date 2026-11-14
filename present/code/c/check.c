#include <stdio.h>

#define CHECK(cond) \
do{ \
	if(cond) printf("ok\n"); \
	else { \
		printf("FAIL at %d\n", __LINE__); \
		return 1; \
	} \
}while(0)

int main() {
//	CHECK(1 + 1 == 2);
	if (1) CHECK(1 + 1 == 2); else printf("else\n");
	printf("after first\n");
	CHECK(2 > 3);
	printf("never\n");
}
