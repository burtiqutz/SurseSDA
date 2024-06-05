#include <stdio.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* a, int low, int high){
    int pivot = a[high];
    int sm = low - 1;
    for(int crt = low; crt < high; crt++){
        if(a[crt] <= pivot){
            sm++;
            swap(&a[crt],&a[sm]);
        }
    }
    swap(&a[sm+1], &a[high]);
    return sm+1;
}

void quicksort(int* a, int low, int high){
    if (low < high){
        int q = partition(a, low, high);
        quicksort(a, low, q-1);
        quicksort(a, q + 1, high);
    }
}

int main() {
    int a[] = {7, 3, 2, 10, 12, 16};
    quicksort(a, 0, 5);
    for(int i = 0; i < sizeof (a) / sizeof(int); i++){
        printf("%d ", a[i]);
    }
    return 0;
}
