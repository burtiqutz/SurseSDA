#include <stdio.h>
#include <stdlib.h>
int sol[100];
int vis[100];
void printSol(int k){
    puts("Solution found:");
    for(int i = 0; i <= k; i++){
        if(i == 0)
            printf("%d", sol[i]);
        else{
            if(i % 2 == 0) {
                printf("+%d", sol[i]);
            }
            else
            {
                printf("-%d", sol[i]);
            }
        }
    }
    puts("");
}
///AM PRESUPUS CA PRIMUL ELEMENT MEREU INCEPE CU "+"
int sum1(int k){
    int temp = 0;
    for(int i = 0; i<= k; i++){
        if(i % 2 == 0)
            temp += sol[i];
        else
            temp -= sol[i];
    }
    return temp;
}

int phi(int k, int s){
    for(int i = 0; i <= k; i++) {
        for(int j = i + 1; j <=k; j++){
            if(sol[i] == sol[j])
                return 0;
        }
    }
    return sum1(k) == s;
}

void bt(int k, int* a, int n, int s){
    for(int i = k; i < n; i++){///trebuie sa iau elementele de dupa cel curent
        sol[k] = a[i];
        if (k < n){
            if(!vis[a[i]] && phi(k, s)){//found solution
                printSol(k);
            } else {
                vis[a[i]] = 1;
                bt(k + 1, a, n, s);
                vis[a[i]] = 0;
            }
        }
    }
}

int main() {
    int n = 0, s = 0;
    int a[10] = {};
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &s);

    bt(0, a, n, s);

    return 0;
}
