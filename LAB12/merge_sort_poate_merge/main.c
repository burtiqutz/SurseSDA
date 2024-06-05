#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG

void merge(int *a, int low, int mid, int high){
    int* aux = (int*) malloc(sizeof(int) * (high - low + 1));
    int i = low;
    int k = low;
    int j = mid + 1;

    while(i <= mid && j <= high){
        if(a[i] <= a[j]){
            aux[k++] = a[i++];
        } else {
            aux[k++] = a[j++];
        }
    }

    while(i <= mid){
        aux[k++] = a[i++];
    }
    while (j <= high){
        aux[k++] = a[j++];
    }
    for(int kk = 0; kk <= k; kk++){
        a[low + kk] = aux[kk];
    }
}

void merge_sort(int *a, int p, int q) {
    if(p < q){
        int mid = (p + q ) / 2;
        merge_sort(a, p, mid);
        merge_sort(a, mid + 1, q);
        merge(a, p, mid, q);
    }
}

int main() {
    int numbers[] = {4, 9, 3, 1, 5, 7, 8, 6, 2};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//    int s1[] = {1, 2, 5, 6, 3, 4, 7, 8};
//    merge(s1, 2, 4, 6);
//    for(int i = 2; i <= 6 ; i++){
//        printf("%d ", s1[i]);
//    }
    int n = (int) (sizeof(numbers) / sizeof(int));
    merge_sort(numbers, 0, n-1);
    for (int i = 0; i < n; i++) {
        assert(numbers[i] == expected[i]);
    }
    return 0;
}