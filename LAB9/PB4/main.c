#include <stdio.h>
#include <stdlib.h>
int sol[100];
int vis[100];
void printSol(int k){
    puts("Solution found:");
    for(int i = 0; i <= k; i++){
        printf("%d ", sol[i]);
    }
    puts("");
}

int sum(const int* a, int k){
    int temp = 0;
    for(int i = 0; i<= k; i++){
        temp += a[i];
    }
    return temp;
}

int phi(int k, int s){
    int temp = 0;
    for(int i = 0; i <= k; i++){
        temp += sol[i];
        if(temp > s){
            return 0;
        }
    }
    return 1;
}

void bt(int k, int* a, int n, int* sol, int s){
    if(k == n){
        //am epuizat toate numerele
        return;
    }
    ///am o problema cu cazul in care primul element este egal cu s
    for(int i = k + 1; i < n; i++){///trebuie sa iau elementele de dupa cel curent
        sol[k] = a[i];
        if (phi(k, s)){//if partial solution is ok and we haven't used that number yet
            if(sum(sol, k) == s){//found solution
                printSol(k);
            } else {
                bt(k + 1, a, n, sol, s);
            }
        }
    }
}
///AM PRESUPUS CA ELEMENTELE TREBUIE SA APARA O SINGURA DATA
///DACA POT APAREA DE MAI MULTE ORI MODIFICAM FOR-UL DIN BT SA INCEAPA DE LA 0
int main() {
    int n = 0, s = 0;
    int a[10] = {};
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &s);

    bt(0, a, n, sol, s);

    return 0;
}
