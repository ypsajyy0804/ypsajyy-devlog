#include <stdio.h>

int main(void) {
    int a[3] = {1, 2, 3};

    FILE *fp = fopen("num.bin", "wb");
    size_t n = fwrite(a, sizeof(int), 3, fp);
    printf("wrote = %zu\n", n);
    fclose(fp);

    fp = fopen("num.bin", "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    printf("size = %ld\n", size);
    fclose(fp);
    return 0;
}
