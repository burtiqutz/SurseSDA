#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int solNb=0; /* solution number */
int bestSolNb = 1000;
int bestSol[1000];
enum { FALSE, TRUE };

typedef struct nod {
    char tara[256];
    struct nod *next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT **t;  // tabloul de liste (va fi alocat dinamic)
    //int *pi; //vectorul de parinti
    //int *d; //timpii de descoperire
    //int *f; //timpii de finalizare
    //int *color; //informatia de culoare
} Graf;

void push(NodeT **stiva, char* tara) { //insert first in a linked list

    NodeT *el = (NodeT *) malloc(sizeof(NodeT));
    strcpy(el->tara, tara);
    el->next = (*stiva);
    *stiva = el;
}

int is_a_solution(int change) {
    return (change == 0); /* is a solution when change is 0 */
}

void backtrack(int a[], int k, int n, int change, int values[]) {


}

int main() {

    int n = 0, m = 0;
    Graf* graf = malloc(sizeof(Graf));

    FILE* f = fopen("input.txt", "r");
    FILE* g = fopen("output.txt", "w");
    if(f == NULL){
        exit(-1);
    }
    fscanf(f,"%d", &n);

    graf->t = (NodeT **)(n, sizeof(NodeT*));
    if(graf->t == NULL){
        perror("mem alloc fail @graf.t");
        exit(-1);
    }

    for(int i = 0; i < n; i++){
        graf->t[i] = NULL;
    }

    for(int i = 0; i < n; i++){
        char temp[256];
        fscanf(f, "%s", temp);
        printf("%s\n", temp);
        //fgets(&temp, 256, f);
        //char* p = strtok(temp, " ");
        //strcpy()

    }
    //fscanf(f, "%d", &m);

    return 0;
}

