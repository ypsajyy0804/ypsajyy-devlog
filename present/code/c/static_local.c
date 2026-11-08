#include <stdio.h>

int next_id(void){
	static int count = 0;
	count++;
	return count;
}

//int peek_id(void){}

int main(void) {
    printf("id1 = %d\n", next_id());
    printf("id2 = %d\n", next_id());
    printf("id3 = %d\n", next_id());
//    printf("peek = %d\n", peek_id());
    return 0;
}
