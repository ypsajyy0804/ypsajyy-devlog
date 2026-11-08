#include <stdio.h>
#include <string.h>

void swap_str(char **a, char **b){
	char *temp = *a;
	*a = *b;
	*b = temp;
}
void sort_by_len(char *arr[], int n){
	if(n <= 1){
		return;
	}
	for(int i = 0; i < n-1; i++){
		for(int j = 0; j < n-1; j++){
			if(strlen(arr[j]) > strlen(arr[j + 1])){
			swap_str(&arr[j], &arr[j + 1]);
			}
		}
	}
}

int main(void) {
    char *words[5] = {"banana", "a", "cherry", "fig", "elderberry"};

    printf("排序前：");
    for (int i = 0; i < 5; i++) printf(" %s", words[i]);
    printf("\n");

    sort_by_len(words, 5);

    printf("排序后：");
    for (int i = 0; i < 5; i++) printf(" %s", words[i]);
    printf("\n");

    return 0;
}
