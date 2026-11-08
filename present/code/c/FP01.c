#include <stdio.h>

int dbl(int x){
	return x * 2;
}

int  neg(int x){
	return -x;
}

int  sq(int x){
	return x * x;
}

void map(int *arr, int n, int (*op)(int)){
	if(n <= 0) return;
	for(int i = 0; i < n; i++) arr[i] = op(arr[i]);
}

void print_arr(const char *label, const int *a, int n) {
    printf("%s:", label);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {
    int a[5] = {1, 2, 3, 4, 5};

    map(a, 5, dbl);
    print_arr("dbl", a, 5);

    map(a, 5, neg);
    print_arr("neg", a, 5);

    map(a, 5, sq);
    print_arr("sq", a, 5);

    map(a, 0, dbl);
    print_arr("n=0", a, 5);

    map(a, -3, dbl);
    print_arr("n=-3", a, 5);

    return 0;
}
