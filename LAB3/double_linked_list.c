#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _DLL_NODE {
    int key;
    struct _DLL_NODE *next;
    struct _DLL_NODE *prev;
} DLL_NODE;

/* define a List structure, consisting of the addresses
 * (pointers) of the first and last elements
 * */
typedef struct {
    DLL_NODE *first;
    DLL_NODE *last;
}DL_LIST;

DL_LIST *create_double_linked_list() {
    DL_LIST *list = NULL;

    list = (DL_LIST*) malloc(sizeof(DL_LIST ));
    if( list == NULL)///couldn't create list
        return NULL;

    memset(list, 0, sizeof(DL_LIST ));
    return list;
}

void destroy_double_linked_list(DL_LIST **list) {
    if(*list == NULL)///list doesn't exist
        return;

    DLL_NODE* node = (*list)->first;
    DLL_NODE* prev = NULL;
    while(node != NULL){
        prev = node;
        node = node->next;
        free(prev);
        prev = NULL;
    }

    free(*list);
    (*list) = NULL;
}

void dll_print_forward(const DL_LIST *list){
    if(list == NULL)///list doesn't exist
        return;
    if(list->first == NULL || list->last == NULL)///no items to print
        return;

    DLL_NODE* node = list->first;
    while(node != list->last){
        printf("%d ", node->key);
        node = node->next;
    }
    printf("%d\n", node->key);
}

void dll_print_backward(const DL_LIST *list){
    if(list == NULL)///list doesn't exist
        return;
    if(list->first == NULL || list->last == NULL)///no items to print
        return;

    DLL_NODE* node = list->last;
    while(node != list->first){
        printf("%d ", node->key);
        node = node->prev;
    }
    printf("%d\n", node->key);}

DLL_NODE *dll_search(const DL_LIST *list, int given_key){
    DLL_NODE *node = NULL;
    if(list == NULL)///list doesn't exist
        return NULL;
    if(list->first == NULL || list->last == NULL)///no items to search
        return NULL;

    for(node = list->first; node != NULL; node = node->next){
        if(node->key == given_key)
            break;
    }

    return node;
}

DLL_NODE *create_dll_node(int given_key) {
    DLL_NODE *node = NULL;

    node = (DLL_NODE*) malloc(sizeof(DLL_NODE));
    if(node == NULL)
        return NULL;

    memset(node, 0, sizeof(DLL_NODE ));
    node->key = given_key;

    return node;
}

void dll_insert_first(DL_LIST *list, int given_key){
    if(list == NULL)
        return;

    DLL_NODE* new_node = NULL;
    new_node = create_dll_node(given_key);
    if(new_node == NULL)
        return;

    if(list->first == NULL){ ///list is empty
        list->first = list->last = new_node;
    } else { ///list isn't empty
        new_node->next = list->first;
        list->first->prev = new_node;
        list->first = new_node;
    }
}

void dll_insert_last(DL_LIST *list, int given_key){
    if(list == NULL)
        return;

    DLL_NODE* new_node = NULL;
    new_node = create_dll_node(given_key);
    if(new_node == NULL)
        return;

    if (list->first == NULL){ ///list is empty
        list->first = list->last = new_node;
    } else {

        list->last->next = new_node;
        new_node->prev = list->last;
        list->last = new_node;
    }
}

void dll_insert_after_key(DL_LIST *list, int after_key, int given_key){
    if(list == NULL)
        return;
    if(list->first == NULL)
        return;

    DLL_NODE* node = NULL;
    DLL_NODE* to_insert = NULL;
    node = dll_search(list,after_key);
    to_insert = create_dll_node(given_key);
    if(node == NULL)///did not find after key
        return;
    if(to_insert == NULL)///could not create new node
        return;

    to_insert->prev = node;
    to_insert->next = node->next;
    if(node->next  != NULL){
        node->next->prev = to_insert;
    }
    node->next = to_insert;
    if(list->last == node){
        list->last = to_insert;
    }

}

void dll_delete_first(DL_LIST *list){
    if (list == NULL)
        return;
    DLL_NODE* node = NULL;
    node = list->first;
    list->first = list->first->next;
    free(node);
    if(list->first == NULL){
        list->last = NULL;
    }
    else {
        list->first->prev = NULL;
    }
}

void dll_delete_last(DL_LIST *list) {
    if(list == NULL)
        return;
    DLL_NODE* node = NULL;

    node = list->last;
    list->last = list->last->prev;
    if(list->last == NULL){
        list->first = NULL;
    } else {
        list->last->next = NULL;
    }
    free(node);
}

void dll_delete_key(DL_LIST *list, int given_key){
    if(list == NULL)
        return;
    DLL_NODE* node = NULL;
    node = dll_search(list, given_key);
    if(node == NULL){
        return;
    }
    if(node->prev != NULL){
        node->prev->next = node->next;
    } else {///im deleting the first node
        list->first = node->next;
    }

    if(node->next != NULL){
        node->next->prev = node->prev;
    }else {///im deleting the last node
        list->last = node->prev;
    }
    free(node);
}

int main() {
    DL_LIST *list = NULL;
    int to_search = 0;
    DLL_NODE *searched_node = NULL;

    list = create_double_linked_list();

    /* test insertion operations */
    /* insert some elements at the beginning */
    dll_insert_first(list, 3);
    dll_insert_first(list, 4);
    dll_insert_first(list, 2);
    dll_insert_first(list, 1);

    /* ... and some at the end */
    dll_insert_last(list, 6);
    dll_insert_last(list, 8);

    /* print list contents */
    dll_print_forward(list);  // 1 2 4 3 6 8
    dll_print_backward(list); // 8 6 3 4 2 1

    /* test search operation */
    //search for two distinct keys...
    to_search = 2;
    searched_node = dll_search(list, to_search);
    if (searched_node == NULL) {
        printf("Node %d NOT found!\n", to_search);
    } else {
        printf("Node %d found!\n", searched_node->key);
    }

    to_search = 9;
    searched_node = dll_search(list, to_search);
    if (searched_node == NULL) {
        printf("Node %d NOT found!\n", to_search);
    } else {
        printf("Node %d found!\n", searched_node->key);
    }

    dll_delete_first(list);
    dll_delete_last(list);
    dll_delete_key(list, 4);
    dll_delete_key(list, 15);

    /* print list contents */
    dll_print_forward(list);  // 2 3 6
    dll_print_backward(list); // 6 3 2

    dll_delete_key(list, 2);
    dll_delete_key(list, 6);

    /* print list contents */
    dll_print_forward(list);  // 3
    dll_print_backward(list); // 3

    destroy_double_linked_list(&list);
    list = NULL;

    return 0;
}
