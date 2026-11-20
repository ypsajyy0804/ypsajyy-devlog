#include <stdio.h>

int main(void) {
	for (int i = 0; i < 12; i++) {
		printf("%d -> %d\n", i, i % 7);
	}
	return 0;
}
