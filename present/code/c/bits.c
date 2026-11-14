#include <stdio.h>

void print_bits(unsigned v){
	for(int i = 31; i >= 0; i--){
		printf("%u", (v >> i) & 1);
	}

	putchar('\n');
}

int main(){
	print_bits(5);
	print_bits(6);
	print_bits(7);
	print_bits(~5u);
	print_bits(1u << 31);
//	print_bits(-1);
}
