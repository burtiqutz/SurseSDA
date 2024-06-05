#include <stdio.h>
int price[5] = {0, 1, 5, 8, 9};
int r[6];

int max(int a, int b){
    return a > b ? a : b;
}

int main() {
    r[0] = 0;
    int n = 5;
    for(int j = 1; j <= n; j++){
        int q = -999999999;
        for(int i = 1; i <= j; i++){
            int aux = price[i] + r[j-i];
            q = max(q, aux);
        }
        r[j] = q;
    }

    printf("%d", r[4]);
    return 0;
}
