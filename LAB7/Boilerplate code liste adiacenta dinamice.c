#include <stdio.h>
#include <stdlib.h>

/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin liste de adiacenta dinamice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge BFS si se scriu într-un fisier
  nodurile în ordinea parcurgerii.
******************************************************/

typedef struct nod {
    int v;
    struct nod* next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT* *t;    // tabloul de liste (va fi alocat dinamic)
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

enum { WHITE, GRAY, BLACK};

typedef struct _queue{
       NodeT *first;
       NodeT *last;
}QUEUE;

NodeT *create_node(int key){
    NodeT *node = NULL;
    node = (NodeT *) malloc(sizeof(NodeT));
    if(node == NULL)
        return NULL;
    node->v = key;
    node->next = NULL;

    return node;
}

QUEUE* init_queue(){
    QUEUE* q = NULL;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    if(q == NULL)
        return NULL;
    q->first = NULL;
    q->last = NULL;

    return q;
}

void enqueue(QUEUE* queue, int key){
    if (queue == NULL)
        return;

    NodeT *to_insert = NULL;
    to_insert = create_node(key);

    if(queue->first == NULL)///empty queue
        queue->first = to_insert;
    else{
        to_insert->next = queue->first;
        queue->first = to_insert;
    }
}

int dequeue(QUEUE* queue){
    if (queue == NULL || queue->first == NULL)
        return -1;

    int key = queue->first->v;
    NodeT *node = queue->first;

    if(queue->first == queue->last){///1 element
        free(node);
        queue->first = NULL;
        queue->last = NULL;
        return key;
    }

    while(node->next != queue->last){
        node = node->next;
    }

    free(node);
    return key;
}

int goala(QUEUE* queue){
    if(queue == NULL)
        return 0;
    if(queue->first == NULL)
        return 0;
    return 1;
}

void printErr() {
    printf("Memorie insuficienta!\n");
    exit(1);
}


void citesteGraf(FILE* f, Graf* pG) {
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic tabloul de liste de adiacenta de dimensiune n:
    pG->t = calloc(pG->n, sizeof(NodeT*));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i=0; i<pG->n; i++) {
        // initializam (liste vide)
        pG->t[i] = NULL;
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in listele de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        NodeT* node = create_node(w);
        node->next = pG->t[v];
        pG->t[v] = node;
        NodeT *node2 = create_node(v);
        node2->next = pG->t[w];
        pG->t[w] = node2;
    }
}

void show_adjacent_lists(Graf* G){
    if(G == NULL)
        printErr();

    for(int i = 0; i < G->n; i++){
        printf("%d :", i);
        NodeT *node = NULL;
        node = G->t[i];
        while(node != NULL){
            printf("%d ", node->v);
            node = node->next;
        }
        printf("\n");
    }
}

int main()
{
    FILE* f = fopen("graf.txt", "r");
    if (f == NULL) {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f, &G);
    fclose(f);

    show_adjacent_lists(&G);
    int color[G.n] = {};
    int distance[G.n] = {};
    int parent[G.n] = {};
    int v;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);



    return 0;
}
