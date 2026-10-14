#include <stdio.h>

int main() {
	char s1[] = "hello";
	char* s2 = "hello";

	printf("%ld\n", sizeof(s1));
	printf("%ld\n", sizeof(s2));
	printf("%p\n", s1);
	printf("%p\n", s2);

	s1[0] = 'H';
	//s2[0] = 'H';
	printf("%s\n", s1);
	//printf("%s\n", s2);

	return 0;
}
