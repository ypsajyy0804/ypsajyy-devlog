#include <stdio.h>
#include <string.h>

int main(){
	printf("%zu\n", strlen("") - 1);
	const char s[] = "hello";
	s[0] = 'H';
	return 0;
}
