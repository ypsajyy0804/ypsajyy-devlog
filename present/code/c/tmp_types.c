#include <stdio.h>
int main(void) {
    int matrix[3][4];
    int* ptr_arr[3];   /* 指针数组：3 个元素，每个都是 int* */
    int (*arr_ptr)[4]; /* 数组指针：1 个指针，指向 int[4] */
    printf("%zu %zu %zu\n", sizeof(matrix), sizeof(ptr_arr), sizeof(arr_ptr));
    return 0;
}