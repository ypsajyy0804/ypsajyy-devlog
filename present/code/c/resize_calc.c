#include <stdio.h>

static unsigned hash(const char *key, unsigned n) {
	int sum = 0;
	for(const char *p = key; *p != '\0'; p++) sum += *p;
	return sum % n;
}

int main() {
	const char *key[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
	for (int i = 0; i < 10; i++) printf("%s：%u -> %u\n", key[i], hash(key[i], 8), hash(key[i], 32));
	return 0;
}
