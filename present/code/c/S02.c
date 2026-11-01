#include <stdio.h>

size_t my_strlen(const char *s){
	size_t len = 0;

	while(*s != '\0'){
		len++;
		s++;
	}
	return len;
}

int my_strcmp(const char *a, const char *b){
	while(*a == *b && *a != '\0'){
		a++;
		b++;
	}
	return *a - *b;
}

void my_strcpy(char *dst, const char *src){
	while(1){
		*dst = *src;
		if(*src == '\0'){
			break;
		}
		dst++;
		src++;
	}
}

int main(){
	printf("len(hello) = %zu\n",         my_strlen("hello"));
	printf("len(empty) = %zu\n",         my_strlen(""));
	printf("cmp(hello, hello) = %d\n",   my_strcmp("hello", "hello"));
	printf("cmp(hello, world) = %d\n",   my_strcmp("hello", "world"));
	printf("cmp(world, hello) = %d\n",   my_strcmp("world", "hello"));
	char buf[32];
	my_strcpy(buf, "hello");
	printf("copy = %s\n", buf);
}
