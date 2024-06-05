#include <stdio.h>
#define MAX 100
int n, a[MAX], res[MAX];
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    ///voi face un greedy optim
    ///modulo este distributiv, deci doar aleg elementul cel mai mare
    ///care este divizibil cu n
    for(int i = 0; i < n - i; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i] < a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    int sum = 0;
    int j = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] % n == 0){
            sum += a[i];
            res[j++] = a[i];
        }
    }
    printf("%d\n", sum);
    for(int i = 0; i < j; i++){
        printf("%d ", res[i]);
    }
    return 0;
}
