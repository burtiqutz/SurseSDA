#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG

typedef enum {
    false, true
} bool;

bool binary_search(int *a, int p, int q, int k) {
    if (p > q)
        return false;
    int mid = (p + q) / 2;
    if(k == a[mid])
        return true;
    if (k < a[mid])
        binary_search(a, p, mid, k);
    else
        binary_search(a, mid + 1, q, k);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int to_be_found[] = {20, 5, 7, 13};
    bool expected[] = {false, true, true, false};

    int n = (int) (sizeof(numbers) / sizeof(int));
    int test_count = (int) (sizeof(to_be_found) / sizeof(int));
    for (int i = 0; i < test_count; i++) {
        assert(binary_search(numbers, 0, n-1, to_be_found[i]) == expected[i]);
    }
    return 0;
}