#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* IORDACHE ALEXANDRU */

typedef struct __DLL_NODE{
    int key;
    struct __DLL_NODE *next;
    struct __DLL_NODE *prev;
}DLL_NODE;

typedef struct _DL_LIST{
    DLL_NODE *first;
    DLL_NODE *last;
}DL_LIST;

DLL_NODE *create_node(int key){
    DLL_NODE *node = NULL;
    node = malloc(sizeof (DLL_NODE));
    if(node != NULL)
        memset(node, 0, sizeof(DLL_NODE));
    node->key = key;
    return node;
}

void insert_last(DL_LIST *list, int key){
    if(list == NULL)
        return;

    DLL_NODE *to_insert = create_node(key);
    if(to_insert == NULL)
        return;

    if(list->first == NULL){
        ///empty list
        list->first = to_insert;
        list->last = to_insert;
    } else {
        list->last->next = to_insert;
        to_insert->prev = list->last;
        list->last = to_insert;
    }
}

void print_forward(DL_LIST* list){
    if (list == NULL)
        return;

    DLL_NODE *node = NULL;
    for(node = list->first; node != NULL; node = node->next){
        printf("%d ", node->key);
    }
    printf("\n");
}

void delete_key(DL_LIST* list, int given_key){
    if (list == NULL)
        return;
    if(list->first == NULL)
        return;///empty list

    DLL_NODE *node = NULL;
    for(node = list->first; node != NULL; node = node->next){
        if(node->key == given_key){
            break;
        }
    }

    if(node == NULL)
        return;///didn't find node

    if(list->first == node){
        ///if we delete 1st node
        list->first = node->next;
        list->first->prev = NULL;
        if(list->first == NULL){///if we emptied list
            list->last = NULL;
        }
        free(node);
        return;
    }else {
        if(node == list->last){
            ///if we delete last node
            list->last = list->last->prev;
            list->last->next = NULL;
            free(node);
            return;
        }
        else{
            node->prev->next = node->next;
            node->next->prev = node->prev;
            free(node);
            return;
        }
    }
}

int get_position(DLL_NODE *node){
    if(node == NULL)
        return -1;
    int i = 0;
    while(node != NULL){
        node = node->prev;
        i++;
    }

    i--;
    return i;
}

int is_palindrome(DL_LIST* list){
    if (list == NULL)
        return 0;

    if(list->first == list->last)
        return 1;

    DLL_NODE *left = list->first;
    DLL_NODE *right = list->last;

    while(left != NULL && right != NULL){
    ///1st for even, 2nd for odd
        if(left->next == right)
            return 1;///am parcurs tot
        if(left->next == right->prev)
            return 1;///am parcurs tot iar
        if(left->key != right->key)
            return 0;

        left = left->next;
        right = right->prev;
    }

    return 1;///is this needed
}

void delete_key_first_last(DL_LIST* L, int given_key){
    if (L == NULL)
    {
        printf("List doesn't exist\n");
        return;
    }

    if(L->first == NULL)
    {
        printf("List is empty\n");
        return;
    }

    DLL_NODE *node = NULL;
    node = L->first;
    int count = 0;

    while(node != NULL) {///first delete
        if(node->key == given_key){
            delete_key(L, given_key);///deleted
            count++;
            break;
        }
        node = node->next;
    }

    if(L->first == NULL){///we can't delete other nodes
        if(count > 0){
            printf("Could only delete once\n");
            return;
        } else{
            printf("Couldn't delete any nodes\n");
            return;
        }
    }

    node = L->first;
    DLL_NODE *last_pos = NULL;
    while(node != NULL){
        if(node->key == given_key){
            last_pos = node;
            count++;
        }
        node = node->next;
    }
    if(last_pos == NULL){
        ///didn't find another key to delete
        if(count > 0){
            printf("Could only delete once\n");
            return;
        } else{
            printf("Couldn't delete any nodes\n");
            return;
        }
    } else {
        ///have to delete last appearance
        //copy pasted from delete, can't use delete because that deletes 1st appearance
        if(L->first == last_pos){
            ///if we delete 1st node
            L->first = last_pos->next;
            L->first->prev = NULL;
            if(L->first == NULL){///if we emptied list
                L->last = NULL;
            }
            free(node);
            return;
        }else {
            if(last_pos == L->last){
                ///if we delete last node
                L->last = L->last->prev;
                L->last->next = NULL;
                free(node);
                return;
            }
            else{
                last_pos->prev->next = last_pos->next;
                last_pos->next->prev = last_pos->prev;
                free(node);
                return;
            }
        }
    }

    ///sorry for the cheesy code D;
}

int main() {
    ///INITIALIZING LIST
    DL_LIST *list = NULL;
    list = malloc(sizeof (DL_LIST));
    if(list == NULL)
        return -1;
    memset(list, 0, sizeof(DL_LIST));

    insert_last(list, 5);
    insert_last(list, 2);
    insert_last(list, 7);
    insert_last(list, 12);
    insert_last(list, 35);
    insert_last(list, 2);
    insert_last(list, 6);

    print_forward(list);
    //5 2 7 12 35 2 6
    delete_key(list, 5);
    print_forward(list);
    //2 7 12 35 2 6

    delete_key(list, 6);
    print_forward(list);
    //2 7 12 35 2

    delete_key(list, 12);
    print_forward(list);
    //2 7 35 2

    DLL_NODE *searched = list->first->next->next->next;
    printf("%d\n", get_position(searched));

    ///delete first last tests

    insert_last(list, 1);
    insert_last(list, 11);
    insert_last(list, 2);
    insert_last(list, 1);
    print_forward(list);
    delete_key_first_last(list, 2);
    print_forward(list);

    /* PALINDROME */
    puts("------------PALINDROMES-----------");
    DL_LIST *palindrom = NULL;
    palindrom = malloc(sizeof (DL_LIST));
    if(palindrom == NULL)
        return -1;
    memset(palindrom, 0, sizeof(DL_LIST));

    insert_last(palindrom, 2);
    printf("Palindrome: ");
    print_forward(palindrom);
    int true = is_palindrome(palindrom);
    if(true){
        printf("is palindrome\n");
    }
    else {
        printf("not palindrome\n");
    }
    insert_last(palindrom, 1);
    insert_last(palindrom, 3);
    //insert_last(palindrom, 7); //checking odd number
    insert_last(palindrom, 3);
    insert_last(palindrom, 1);
    insert_last(palindrom,2);
    printf("Palindrome: ");
    print_forward(palindrom);
    true = is_palindrome(palindrom);
    if(true){
        printf("is palindrome\n");
    }
    else {
        printf("not palindrome\n");
    }

    insert_last(palindrom, 13);
    printf("Palindrome: ");
    print_forward(palindrom);
    true = is_palindrome(palindrom);
    if(true){
        printf("is palindrome\n");
    }
    else {
        printf("not palindrome\n");
    }


    return 0;
}
