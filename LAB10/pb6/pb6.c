#include <stdio.h>
int sol[100];
int nr;
int putere(int a, int b){
    int copie = 1;
    for(int i = 1; i <=b; i++){
        copie *= a;
    }
    return copie;
}
void descompunere(int x){
    while(x > 0){
        int temp = 0;
        int pow = 1;
        while(temp <= x){
            temp = putere(2, pow);
            pow++;
        }
        pow -= 2;
        temp = putere(2, pow);
        x -= temp;
        sol[nr++] = temp;
    }
}
int main() {
    int x = 0;
    scanf("%d", &x);
    descompunere(x);
    printf("numarul %d se descompune in: ", x);
    for(int i = 0; i < nr; i++){
        printf("%d ", sol[i]);
    }

    return 0;
}
