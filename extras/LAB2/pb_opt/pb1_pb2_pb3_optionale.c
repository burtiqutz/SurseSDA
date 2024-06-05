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

void reverse_list(SL_LIST* list) {
    SLL_NODE* next;
    SLL_NODE* current = list->first;
    SLL_NODE* prev = NULL;
    list->last = list->first;

    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->first = prev;
}

void insert_in_ordered_list(SL_LIST* list, int given_key) {

    if(list == NULL)///list doesnt exist
        return;
    SLL_NODE* to_insert = create_sll_node(given_key);
    if(to_insert == NULL)///couldnt create node
        return;

    SLL_NODE* current = list->first;

    ///empty list
    if(list->first == NULL){
        list->first = to_insert;
        list->last = to_insert;
        return;
    }

    ///just one node
    if(list->first == list->last){
        if(to_insert->key < current->key){
            list->first = to_insert;
            to_insert->next = current;
            list->last = current;
        } else {
            list->last = to_insert;
            current->next = to_insert;
        }
        return;
    }

    ///all other cases
    while(current != NULL){
        if(current->next == NULL){///reached end with search
            if(current->key <= to_insert->key){
                current->next = to_insert;
                list->last = to_insert;
                return;
            } else {
                to_insert->next = list->first;
                list->first = to_insert;
                return;
            }

        }
        if(current->key <= to_insert->key && to_insert->key <= current->next->key){
            to_insert->next = current->next;
            current->next = to_insert;
            return;
        }

        current = current->next;
    }
}

SLL_NODE* find_length_sub_k(SL_LIST* list, int k){
    SLL_NODE *current = NULL;
    SLL_NODE *offset = list->first;
    int i = 0;

    if(k == 0){
        return list->first;
    }

    while(offset != NULL && i <= k){
        offset = offset->next;
        i++;
    }

    current = list->first;
    while(current != NULL && offset != NULL){
        current = current->next;
        offset = offset->next;
    }

    return current;

}

int main() {
    ///problema 1
    SL_LIST* list = create_single_linked_list();
    sll_insert_first(list,7);
    sll_insert_last(list, 2);
    sll_insert_last(list, 8);
    sll_insert_last(list, 4);
    sll_insert_last(list, 1);
    sll_insert_last(list, 11);

    printf("Initial list:\n");
    sll_print_list(list);
    printf("\nList after reversing:\n");
    reverse_list(list);
    sll_print_list(list);
    printf("\n");

    ///problema 2
    SL_LIST* ordered_list = create_single_linked_list();
    sll_insert_first(ordered_list,-1);
    sll_insert_last(ordered_list, 4);
    sll_insert_last(ordered_list, 8);
    sll_insert_last(ordered_list, 25);

    printf("Ordered list before insertion:\n");
    sll_print_list(ordered_list);
    printf("\n");

    insert_in_ordered_list(ordered_list, -2);
    printf("Ordered list after insertion:\n");
    sll_print_list(ordered_list);

    ///problema 3
    /// am considerat ca cerinta ar avea elementele de la 1 la n
    ///nu am stiut cum sa fac pentru k >= lungime
    printf("\nFinding n-k in ordered list:\n");
    SLL_NODE* found = find_length_sub_k(ordered_list, 1);
    if(found != NULL)
        printf("%d\n", found->key);
    else
        printf("wrong k\n");

    return 0;
}
