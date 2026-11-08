#include <stdio.h>
#include <stdlib.h>

int  asc(int a, int b){
	return a - b;
}

int  desc(int a, int b){
	return b - a;
}

int  by_abs(int a, int b){
	return abs(a) - abs(b);
}

void sort(int *arr, int n, int (*cmp)(int, int)){
	if(n <= 1) return;

	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - 1 - i; j++){
			if(cmp(arr[j], arr[j+1]) > 0){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void print_arr(const char *label, const int *a, int n) {
    printf("%s:", label);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {
    int a[6] = {5, -3, 8, 1, -9, 0};
    sort(a, 6, asc);
    print_arr("asc", a, 6);

    int b[6] = {5, -3, 8, 1, -9, 0};
    sort(b, 6, desc);
    print_arr("desc", b, 6);

    int c[6] = {5, -3, 8, 1, -9, 0};
    sort(c, 6, by_abs);
    print_arr("abs", c, 6);

    return 0;
}
