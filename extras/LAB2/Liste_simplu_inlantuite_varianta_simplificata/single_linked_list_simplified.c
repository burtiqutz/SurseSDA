#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SLL_NODE {
    int key;
    struct _SLL_NODE *next;
}SLL_NODE;

typedef struct {
    SLL_NODE *first;
    SLL_NODE *last;
}SL_LIST;


SL_LIST *create_single_linked_list() {
    SL_LIST *list = NULL;

    list = malloc(sizeof (SL_LIST));
    if(list != NULL) {
        memset(list, 0, sizeof (SL_LIST));
        //sau
        //fac de mana
    } else {
        return NULL;
    }

    return list;
}

void destroy_single_linked_list(SL_LIST **sl_list) {
    if(*sl_list == NULL)//list doesnt exist
        return;

    SLL_NODE* crt_node = NULL;
    SLL_NODE* trail = NULL;
    crt_node = (*sl_list)->first;
    while(crt_node != NULL) {
        trail = crt_node;
        crt_node = crt_node->next;
        free(trail);
        trail = NULL;
    }

    free(*sl_list);
    *sl_list = NULL;
}

void sll_print_list(const SL_LIST *list) {
    if(list != NULL) {
        SLL_NODE* crt_node = list->first;
        while(crt_node != NULL) {
            printf("%d ", crt_node->key);
            crt_node = crt_node->next;
        }
    }

}

SLL_NODE *create_sll_node(int value) {
    SLL_NODE* node = NULL;
    node = malloc(sizeof(SLL_NODE));

    if(node == NULL) {
        return NULL;
    }

    memset(node, 0, sizeof (SLL_NODE ));
    node->key = value;

    return node;
}

void sll_insert_first(SL_LIST *list, int given_key) {
    SLL_NODE* new_node = create_sll_node(given_key);
    if(list == NULL)
        return;
    if(new_node == NULL)
        return;

    if(list->first == NULL) {//lista e goala
        list->first = new_node;
        list->last = new_node;
    } else {//am elemente in lista
        new_node->next = list->first;
        list->first = new_node;
    }
}

void sll_insert_last(SL_LIST *list, int given_key) {
    SLL_NODE* new_node = create_sll_node(given_key);
    if(list == NULL)
        return;
    if(new_node == NULL)
        return;

    if(list->last == NULL) {//nu am elemente in lista
        list->first = new_node;
        list->last = new_node;
    } else {
        list->last->next = new_node;
        list->last = new_node;
    }
}

SLL_NODE *sll_search(const SL_LIST *list, int search_key) {
    SLL_NODE *node = NULL;
    if(list == NULL)
        return NULL;

    node = list->first;
    while(node != NULL) {
        if(node->key == search_key) {
            break;
        }
        node = node->next;
    }

    return node;
}

void sll_insert_after_key(SL_LIST *list, int search_key, int value) {
    SLL_NODE *crt_node = NULL;
    crt_node = sll_search(list, search_key);
    if(crt_node == NULL)
        return;

    SLL_NODE* new_node = create_sll_node(value);
    if(new_node == NULL)
        return;

    new_node->next = crt_node->next;
    crt_node->next = new_node;

    if(list->last == crt_node) {
        list->last = new_node;
    }
}

void sll_delete_first(SL_LIST *list) {
    if(list == NULL)//list doesnt exist
        return;

    SLL_NODE * node = list->first;
    if(node == NULL)//list empty
        return;

    list->first = list->first->next;
    free(node);
    node = NULL;

    if(list->first == NULL){//after deletion is empty
        list->last = NULL;
    }
}

void sll_delete_last(SL_LIST *list) {
    if(list == NULL)
        return; //list doesnt exist

    SLL_NODE* crt_node = NULL;
    SLL_NODE* trail = NULL;
    crt_node = list->first;
    if(crt_node == NULL)
        return;

    while(crt_node != list->last) {
        trail = crt_node;
        crt_node = crt_node->next;
    }

    if(crt_node == list->first) {//single element in list
        list->first = list->last = NULL;
    }
    else {
        trail->next = NULL;
        list->last = trail;
    }

    free(crt_node);
    crt_node = NULL;
}

void sll_delete_key(SL_LIST *list, int search_key) {
    SLL_NODE* crt_node = NULL;
    SLL_NODE* trail = NULL;

    crt_node = list->first;
    while(crt_node != NULL) {
        if(crt_node->key == search_key)
            break;
        trail = crt_node;
        crt_node = crt_node->next;
    }

    if(crt_node == NULL)//didnt find key
        return;

    if(crt_node == list->first){//if it's the first node
        list->first = list->first->next;
        if(list->first == NULL){//emptied list
            list->last = NULL;
        }
    }
    else {//any other node
        trail->next = crt_node->next;
        if(crt_node == list->last){//if we delete the last
            list->last = trail;
        }
    }

    free(crt_node);
    crt_node = NULL;
}


int main() {
    SL_LIST *list = NULL;
    SLL_NODE *node = NULL;
    int search_key = 0;

    list = create_single_linked_list();

    sll_insert_first(list, 4);
    sll_insert_first(list, 1);

    sll_insert_last(list, 3);

    search_key = 2;
    node = sll_search(list, search_key);
    if (node == NULL) {
        printf("The node with the key %d was NOT found!\n", search_key);
    } else {
        printf("The node with the key %d was found at address %p\n", search_key, node);
    }

    search_key = 3;
    node = sll_search(list, search_key);
    if (node == NULL) {
        printf("The node with the key %d was NOT found!\n", search_key);
    } else {
        printf("The node with the key %d was found at address %p\n", search_key, node);
    }

    sll_insert_after_key(list, 4, 22);
    sll_insert_after_key(list, 3, 25);

    sll_print_list(list);
    printf("\n");

    sll_delete_first(list);
    sll_delete_last(list);

    sll_delete_key(list, 22);
    sll_delete_key(list, 8);

    sll_print_list(list);
    printf("\n");

    while(list != NULL && list->first != NULL) {
        sll_delete_first(list);
    }

    sll_print_list(list);
    printf("\n");

    destroy_single_linked_list(&list);
    list = NULL;

    return 0;
}
