#include <stdio.h>
#include <stdlib.h>
enum {VIZITAT, NEVIZITAT};

typedef struct _NodeT{
    int key;
    struct _NodeT* next;
}NodeT;

typedef struct _queue{
    NodeT *first;
    NodeT *last;
}QUEUE;

/* mai intai operatiile pt coada */

QUEUE* initQueue(){
    QUEUE* q = NULL;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    if(q == NULL)
    {   perror("bruh bruh");
        exit(-1);
    }
    q->first = NULL;
    q->last = NULL;

    return q;
}

NodeT *createNode(int key){
    NodeT *node = NULL;
    node = (NodeT *) malloc(sizeof(NodeT));
    if(node == NULL)
        return NULL;
    node->key = key;
    node->next = NULL;

    return node;
}

void enqueue(QUEUE* queue, int key){
    if (queue == NULL)
        return;

    NodeT* node = createNode(key);
    if (node == NULL){
        perror("alloc fail @insert");
        return;
    }
    if(queue->first == NULL){
        queue->first = queue->last = node;
    } else {
        queue->last->next = node;
        queue->last = node;
    }
}
int dequeue(QUEUE* queue){
    if(queue == NULL)
        return -1;
    if(queue->first == NULL)
        return -1;

    int k = 0;
    k = queue->first->key;
    NodeT *node = queue->first;
    queue->first = queue->first->next;
    free(node);
    if(queue->first == NULL){//if we emptied queue
        queue->last = NULL;
    }
    return k;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
