#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    int dp[100]; // dp[i] = lmax pentru o secventa in care consideram primele i elemente,
    // ULTIMUL ELEMENT FACE OBLIGATORIU PARTE DIN SECVENTA
    int decizii[100];//strict pentru a reconstrui secventa

    int n = 4;
    int a[100] = {24, 12, 15, 15, 19};

    for(int i=1; i<=n; i++)
        dp[i] = 1;

    for(int i=1; i<=n; i++)
        decizii[i] = -1;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= i-1; j++){///consideram toate secventele pana la i
            if(a[j] < a[i]){///daca elementul este mai mic
                if(dp[j] + 1 >= dp[i]){///daca mai adaug un element la secventa actuala ea este mai mare decat cea stocata pana la i
                    dp[i] = dp[j] + 1;
                    decizii[i] = j;
                }
            }
        }
    }

    int lmax = -1;
    int imax = -1;
    for(int i=1; i<=n; i++){
        if(dp[i] > lmax){
            lmax = dp[i];
            imax = i;
        }
    }
    printf("%d\n", lmax);

    int i = imax;
    while(decizii[i] != -1){
        printf("%d ", a[i]);
        i = decizii[i];
    }
    printf("%d ", a[i]);
    int t = 0;
}