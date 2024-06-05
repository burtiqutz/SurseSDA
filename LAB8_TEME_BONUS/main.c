#include <stdlib.h>
#include <stdio.h>

typedef struct nod {
    int val;
    struct nod *next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT **t;  // tabloul de liste (va fi alocat dinamic)
    int *pi; //vectorul de parinti
    int *d; //timpii de descoperire
    int *f; //timpii de finalizare
    int *color; //informatia de culoare
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice; tine si informatia de parcurgere

enum {
    WHITE, GRAY, BLACK
};

void push(NodeT **stiva, int val) { //insert first in a linked list

    NodeT *el = (NodeT *) malloc(sizeof(NodeT));
    el->val = val;
    el->next = (*stiva);
    *stiva = el;
}

/* sterge elementul din varful stivei si returneaza valoarea lui */
int pop(NodeT **stiva)
{
    int n=-1;
    if(*stiva != NULL) {
        NodeT *firstElement = (*stiva);
        *stiva = (*stiva)->next;
        n=firstElement->val;
        free(firstElement);
    }
    return n;
}

/* returneaza 1 daca stiva este goala */
int empty(NodeT *stiva)
{
    return stiva == NULL;
}

void init(NodeT** stiva){
    *stiva = NULL;
}

void printErr() {
    printf("Memorie insuficienta!\n");
    exit(1);
}

void dfs_visit(int v, Graf *G, int *time) {
    (*time)++;
    G->d[v] = *time;
    G->color[v] = GRAY;
    //printf("%d ", v);
    NodeT* nextNode = G->t[v];

    while(nextNode != NULL){
        int w = nextNode->val;
        //NodeT* invSt = NULL;
        if (G->color[w] == WHITE){
            G->pi[w] = v;
            dfs_visit(w, G, time);
        }
        nextNode = nextNode->next;
    }

    G->color[v] = BLACK;
    (*time)++;
    G->f[v] = *time;
}

void dfs_recursiv(Graf *G) {

    int time = 0, i;

    for (i = 0; i < G->n; i++) {
        if (G->color[i] == WHITE) {
            dfs_visit(i, G, &time);
        }
    }
}

int dfs_master(Graf* G, int* f){
    int time = 0;
    int scc = 0;
    ///trebuie sa parcurg in ordine descrescatoare vectorul de finalizare
    for(int i = 0; i < G->n; i++){
        if(G->color[i] == WHITE){
            scc++;
            dfs_visit(f[i], G, &time);
        }


    }
    return scc;
}

void citesteGraf(FILE *f, Graf *pG, Graf *GT) {
    //GT = GRAFUL TRANSPUS
    fscanf(f, "%d", &pG->n);  // citeste nr. de varfuri
    GT->n = pG->n;

    pG->t = (NodeT **) calloc(pG->n, sizeof(NodeT *));
    GT->t = (NodeT **) calloc(pG->n, sizeof(NodeT *));
    if (pG->t == NULL) printErr();  // alocare esuata

    pG->pi = (int *) calloc(pG->n, sizeof(int));
    pG->d = (int *) calloc(pG->n, sizeof(int));
    pG->f = (int *) calloc(pG->n, sizeof(int));
    pG->color = (int *) calloc(pG->n, sizeof(int));
    GT->pi = (int *) calloc(pG->n, sizeof(int));
    GT->d = (int *) calloc(pG->n, sizeof(int));
    GT->f = (int *) calloc(pG->n, sizeof(int));
    GT->color = (int *) calloc(pG->n, sizeof(int));

    int i;
    for (i = 0; i < pG->n; i++) {
        pG->t[i] = NULL;
        GT->t[i] = NULL;
        pG->pi[i] = -1;
        GT->pi[i] = -1;
    }

    int v, w;
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        ///grafurile sunt orientate
        push(&pG->t[v], w);
        //transpusul
        push(&GT->t[w], v);
    }
}

void print(int* arr, int n)
{
    for(int i = 0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void reInitTraversalData(Graf *G)
{
    for(int i=0; i<G->n; i++)
    {
        G->d[i]     = -1;
        G->pi[i]    = -1;
        G->f[i]     = -1;
        G->color[i] = WHITE;
    }

}


int main() {
    FILE *f = fopen("graf.txt", "r");
    if (f == NULL) {
        perror("graf.txt");
        exit(1);
    }
    Graf G, Gt;
    citesteGraf(f, &G, &Gt);
    fclose(f);

    //varianta recursiva
    //printf("DFS varianta recursiva: ");
    dfs_recursiv(&G);
//    printf("\nVectorul de parinti:");
//    print(G.pi, G.n);
//    printf("Timpii de descoperire:");
//    print(G.d, G.n);
//    printf("Timpii de finalizare:");
//    print(G.f, G.n);
//    puts("");

    int* fin = calloc(G.n, sizeof (int));
    for(int i = 0; i < G.n; i++){
        fin[i] = i;
    }

    //sortez descrescator timpii de finalizare de la parcurgerea lui G, salvez nodurile in fin
    for(int i = 0; i < G.n; i++){
        for(int j = i + 1; j< G.n; j++){
            if (G.f[i] < G.f[j]){
                int t = fin[i];
                fin[i] = fin[j];
                fin[j] = t;

                t = G.f[i];
                G.f[i] = G.f[j];
                G.f[j] = t;
            }
        }
    }
    //print(fin, G.n);
    // trebuie sa parcurg G transpus in ordine inversa de finalizare de la G
    reInitTraversalData(&Gt);
    reInitTraversalData(&G);
    int componente = dfs_master(&Gt, fin);
//    printf("\nVectorul de parinti:");
//    print(Gt.pi, Gt.n);
//    printf("Timpii de descoperire:");
//    print(Gt.d, Gt.n);
//    printf("Timpii de finalizare:");
//    print(Gt.f, Gt.n);
    printf("\nNr de componente tare conexe este: %d", componente);

    //eliberam memoria
    free(G.color);
    free(G.d);
    free(G.f);

    int i;
    for (i = 0; i < G.n; i++) {
        /// TODO: eliberati nodurile din lista de adiacenta a lui i, daca e nevida
		//printf("Nu ati eliberat lista indice %d\n", i);
        NodeT* nextNode = NULL;
        NodeT *trail = NULL;
        if(G.t[i] != NULL)
            if(G.t[i]->next != NULL)
                nextNode = G.t[i]->next;
        trail = G.t[i];
        while(nextNode != NULL){
            free(trail);
            trail = nextNode;
            nextNode = nextNode->next;
        }
        free(trail);
    }

    free(G.t);

    return 0;
}
