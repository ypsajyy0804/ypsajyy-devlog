#include <stdio.h>

void flags_set(unsigned *flags, int idx, int on){
	if(idx < 0 || idx > 7) return;
	if(on) *flags |= (1u << idx);
	else *flags &= ~(1u << idx);	
}

int flags_get(unsigned flags, int idx){
	if(idx > 7 || idx < 0) return 0;
	return flags >> idx & 1;
}

int flags_count(unsigned flags){
	int count = 0;
	for(int i = 7; i >= 0; i--){
		if((flags >> i & 1) == 1) count++;
	}
	return count;
}

int main(){
	unsigned f = 0;
	flags_set(&f, 0, 1);
	flags_set(&f, 3, 1);
	flags_set(&f, 7, 1);
	flags_set(&f, 9, 1);
	flags_set(&f, 3, 0);

	printf("f = %d\n", f);
	printf("bit0 = %d\n", flags_get(f, 0));
	printf("bit3 = %d\n", flags_get(f, 3));
	printf("count = %d\n", flags_count(f));
}
