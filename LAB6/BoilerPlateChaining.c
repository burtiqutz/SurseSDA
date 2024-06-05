#include <stdio.h>
#include <stdlib.h>
#define M 7 //dimensiunea tabelei de dispersie

typedef struct node{
    int val;
    struct node *next;
}NodeT;

int hFunction(int key){
    return key%M;
}

void insert(NodeT* hTable[M], int key){
    while(key < 0){
        key += M;
    }
    int pos = hFunction(key);
    NodeT *toInsert = (NodeT*) malloc(sizeof(NodeT));
    if(toInsert == NULL){
        perror("alloc error @insert");
        exit(-1);
    }
    toInsert->val = key;
    toInsert->next = NULL;

    if(hTable[pos] == NULL){///empty space
        hTable[pos] = toInsert;
    }
    else{///else we chain
        toInsert->next = hTable[pos];
        hTable[pos] = toInsert;
    }
}


NodeT* search(NodeT* hTable[M], int key){
    NodeT* node = NULL;
    int pos = hFunction(key);

    node = hTable[pos];
    while(node != NULL && node->val != key){
        if(hTable[pos]->val == key){
            node = hTable[pos];
            return node;
        }
        node = node->next;
    }

    return node;
}


void deleteKey(NodeT* hTable[M], int key){
    while(key < 0){
        key += M;
    }
    int pos = hFunction(key);

    NodeT* node = hTable[pos];
    NodeT* prev = hTable[pos];

    if(hTable[pos]->val == key){
        hTable[pos] = node->next;
        free(node);
        return;
    }

    while(node != NULL){
        if(node->val == key){
            prev->next = node->next;
            node->next = NULL;
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }

}

//afisarea tuturor elmentelor din tebela de dispersie
void showAll(NodeT* hTable[M]){
    int i;
    for(i = 0; i < M; i++)
    {
        printf(" %d :",i);
        //verificam daca la slotul i am adaugat ceva
        if(hTable[i] != NULL)
        {

            NodeT *p;
            p = hTable[i];
            while (p != NULL)
            {
                printf(" %d ",p->val);
                p = p->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main(){

    //initializare
    NodeT* hTable[M];
    for(int i = 0; i < M; i++){
        hTable[i] = NULL;
    }

    //test inserare
    int vals[] = {36, 18, 6, 43, 72, 10, 5, 15};
    for(int i=0; i<sizeof(vals)/sizeof(int); i++)
        insert(hTable, vals[i]);
    showAll(hTable);

    // 0:
    // 1: 15 43 36
    // 2: 72
    // 3: 10
    // 4: 18
    // 5: 5
    // 6: 6

    int key = 10;
    NodeT *node1 = search(hTable, key);
    if(node1!= NULL){
        printf("Found node %d at %p\n",node1->val, node1);
    }else{
        puts("didn't find node");
    }
    int key2 = 1;
    NodeT *node2 = search(hTable, key2);
    if(node2!= NULL){
        printf("Found node %d at %p\n", node2->val, node2);
    }else{
        puts("didn't find node");
    }

    //test stergere
    int todel[] = {43, 36, 10, 61, -5};
    for(int i=0; i<sizeof(todel)/sizeof(int); i++)
        deleteKey(hTable, todel[i]);
    showAll(hTable);

    // 0:
    // 1: 15
    // 2: 72
    // 3:
    // 4: 18
    // 5: 5
    // 6: 6

    return 0;
}
