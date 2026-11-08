#include <stdio.h>
#include <string.h>

const char *longest(const char *arr[], int n){
	if(n <= 0) return NULL;

	const char *x = arr[0];
	size_t max = strlen(arr[0]);

	for(int i = 0; i < n; i++){
		if(strlen(arr[i]) > max) {
			max = strlen(arr[i]);
			x = arr[i];
		}
	}

	return x;
}

int main(void) {
    const char *words[5] = {"banana", "a", "cherry", "fig", "elderberry"};

    const char *p = longest(words, 5);
    printf("longest = %s\n", p);

    const char *q = longest(words, 0);
    printf("empty   = %s\n", q == NULL ? "(null)" : q);

    return 0;
}
