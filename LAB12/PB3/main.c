#include <stdio.h>
#include <math.h>

int max(int a, int b){
    return a > b ? a : b;
}
int size(int x){
    return (x == 0) ? 1 : ((int)log10(x) + 1);
}
void split(int x, int m, int* x1, int* x0){
    *x1 = x / (int)pow(10, m);
    *x0 = x % (int)pow(10, m);
}

long long karatsuba(int x, int y){
    if( x < 10 || y < 10){
        return x * y;
    }
    int mid = max(size(x), size(y)) / 2;
    int x1 = 0, x0 = 0;
    int y1 = 0, y0 = 0;
    split(x, mid, &x1, &x0);
    split(y, mid, &y1, &y0);

    long long z0 = karatsuba(x0, y0);
    long long z2 = karatsuba(x1, y1);
    long long z1 = karatsuba((x1 + x0), (y1 + y0)) - z2 - z1;

    return (int)(z2 * pow(10, 2*mid) + z1 * pow(10, mid) + z0);
}

int main() {

    int x = 25;
    int y = 25;
    printf("%lld", karatsuba(x, y));
    return 0;
}
