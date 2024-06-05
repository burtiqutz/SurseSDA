#include <stdio.h>
#include <stdlib.h>

//contine cifra k
//int has_d (int n, int k) {
//    if (0 == n)
//        return 0;
//    if(n % 10 == k) {
//        return 1;
//    }
//    else
//        return has_d(n/10, k);
//}
//
////format doar din cifre impare
////0 daca contine cifre pare
//int cif_imp(int n) {
//    if( n < 10 || n % 2 == 0) {
//        return n % 2;
//    }
//    else {
//        return cif_imp(n/10);
//    }
//
//}

////elementul minim dintr-un tablou de n int uri
//int minim (int a[], int n) {
//    if (n == 1) {
//        return a[0];
//    }
//
//    int r;
//    r = minim(a + 1, n - 1);
//    if(a[0] < r) {
//        return a[0];
//    } else {
//        return r;
//    }
//}

int poz_minim(int a[], int n) {
    if(n == 1)
        return 0;
    int r = poz_minim(a + 1, n - 1);
    if(a[0] < a[r + 1])
        return 0;
    else
        return r + 1;
}

//inversati ordinea elementelor dintr-un tablou

void inversare(int a[], int n) {
    int aux = 0;
//    if((a + n - 1) - a <= 1) {
//        aux = a[0];
//        a[0] = a[n - 1];
//        a[n-1] = aux;
//        return;
//    }
    if(n == 1)
        return;
    inversare(a + 1, n - 2);
    aux = a[0];
    a[0] = a[n - 1];
    a[n-1] = aux;

}
///det daca tabloul de inturi este sortat crescator

int ecresc(int* a,int n)
{
    if(n==1)
        return 1;
    return ecresc(a,n-1) && (a[n-2]<=a[n-1]);
}

int main() {
    int a[] = {4, 3, 2, 1, 2, 7, 6};
    int n = sizeof (a) / sizeof (int);
//    printf("%d\n", has_d(12345, 0));
//    printf("%d\n", cif_imp(1357));
//    printf("%d\n", minim(a, 5));
    printf("%d\n", poz_minim(a, n));
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    puts("");
    inversare(a, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    //printf(("%d\n", ecresc(a, n)));
    return 0;
}
