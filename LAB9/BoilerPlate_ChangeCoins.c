#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int solNb=0; /* solution number */
int bestSolNb = 1000;
int bestSol[1000];
enum { FALSE, TRUE };

int is_a_solution(int change) {
    return (change == 0); /* is a solution when change is 0 */
}

void backtrack(int a[], int k, int n, int change, int values[]) {
    int c[2]; /* candidates for next position */
    int ncandidates; /* next position candidate count */
    int i;

    if(k == n) /* all the coins were explored! */
        return;

        int currentCoins = 0;
    for(int i = 0; i <= k; i++){
        if(a[i] == 1)
            currentCoins++;
    }
    if (is_a_solution(change)) {
        printf("Found solution %d:\n", ++solNb);
        //must process solution
        int usedCoins = 0;

        for(int i=0; i<n; i++){
            printf("%d ", a[i]*values[i]);
            if (a[i] == 1){
                usedCoins++;
            }
        }
        if(usedCoins < bestSolNb ){
            bestSolNb = usedCoins;
            memcpy(bestSol, a, sizeof (int) * n);
        }
        printf("\n");
    }
    else if(change > 0 && currentCoins < bestSolNb - 1) {
        k = k + 1;
        a[k] = 1;
        backtrack(a,k,n,change-values[k], values);
        a[k] = 0;
        backtrack(a,k,n,change, values);
    }
}

int main() {
    int n, change;
    int* values = NULL;
    int* a = NULL;
    printf("Number of coins=");
    scanf( "%d", &n );
    printf("Change to be returned=");
    scanf( "%d", &change );
    printf("Input coin values:\n");
    values = (int*)malloc(n*sizeof(int));
    a=(int*)malloc(n*sizeof(int));
    for(int i=0; i<n; i++)  {
        a[i] = values[i] = 0;
    }
    for(int i=0; i<n; i++)
        scanf("%d", values+i);

    backtrack(a, -1, n, change, values);
    printf("\nBest solution\n");
    for(int i=0; i<n; i++){
        printf("%d ", bestSol[i] * values[i]);
    }
    printf( "\nEnd.\n" );
    return 0;
}

