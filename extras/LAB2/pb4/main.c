#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SLL_NODE {
    int key;
    struct _SLL_NODE *next;
}SLL_NODE;

typedef struct {
    SLL_NODE * first ;
} CIRC_SL_LIST ;

SLL_NODE *create_sll_node(int value) {
    SLL_NODE* node = NULL;
    node = (SLL_NODE*) malloc(sizeof(SLL_NODE));

    if(node == NULL) {
        return NULL;
    }

    memset(node, 0, sizeof (SLL_NODE ));
    node->key = value;

    return node;
}

void csll_print ( const CIRC_SL_LIST * list ){
    if(list == NULL)
        return;

    SLL_NODE* node = list->first;
    while(node->next != list->first){
        printf("%d ", node->key);
        node = node->next;
    }
    printf("%d\n", node->key);
}

void csll_insert_first ( CIRC_SL_LIST * list , int key ){
    if(list == NULL)
        return;

    SLL_NODE *p = create_sll_node(key);

    if(list->first == NULL){///LIST IS EMPTY
        list->first = p;
        list->first->next = p;
    } else {
        p->next = list->first->next;
        list->first->next = p;
        list->first = p;
    }
}

CIRC_SL_LIST *create_cssl() {
    CIRC_SL_LIST *list = NULL;

    list = malloc(sizeof (CIRC_SL_LIST));
    if(list != NULL) {
        memset(list, 0, sizeof (CIRC_SL_LIST));
    } else {
        return NULL;
    }

    return list;
}


SLL_NODE * csll_search ( const CIRC_SL_LIST * list , int key ) {
    SLL_NODE *node = NULL;
    if(list == NULL)
        return NULL;

    node = list->first;
    while(node->next != list->first) {
        if(node->key == key) {
            break;
        }
        node = node->next;
    }
    if(node->key != key)///crt node doesnt have key
        return NULL;
    return node;
}

void csll_insert_after_key ( CIRC_SL_LIST * list , int afterKey , int key ) {
    SLL_NODE *crt_node = NULL;
    crt_node = csll_search(list, afterKey);
    if(crt_node == NULL)
        return;

    SLL_NODE* new_node = create_sll_node(key);
    if(new_node == NULL)
        return;

    new_node->next = crt_node->next;
    crt_node->next = new_node;

}


void csll_delete_key ( CIRC_SL_LIST * list , int key ) {
    SLL_NODE* crt_node = NULL;
    SLL_NODE* trail = NULL;
    int found = 0;

    crt_node = list->first;
    while(crt_node->next != list->first) {
        if(crt_node->key == key){
            found = 1;
            break;
        }
        trail = crt_node;
        crt_node = crt_node->next;
    }
    if(crt_node->key == key)
        found = 1;

    if(!found)//didnt find node
        return;

    trail->next = crt_node->next;

    free(crt_node);
    crt_node = NULL;
}

int main() {

    CIRC_SL_LIST* csll = create_cssl();
    if(csll == NULL)
        exit(-1);

    csll_insert_first(csll, 1);
    csll_insert_first(csll, 4);
    csll_insert_first(csll, 9);
    csll_insert_first(csll, 2);
    csll_insert_first(csll, 10);

    printf("Initial list:\n");
    csll_print(csll);
    csll_insert_after_key(csll, 4, 170);
    printf("List after inserting w/ afterkey:\n");

    return 0;
}
