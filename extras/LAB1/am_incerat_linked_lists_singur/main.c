#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeT {
    int key;
    struct NodeT* next;
}Node;

typedef struct LIST{
    Node* first;
}List;

struct LIST* init_list() {
    List* list =  NULL;

    list = malloc(sizeof (List));
    if(list != NULL)
        memset(list, 0, sizeof (List));

    return list;
}

void create_node(List* list, int given_key) {// created node isnt linked
    Node* node = NULL;
    node = malloc(sizeof(Node));
    if(node != NULL) {
        memset(node, 0, sizeof(Node));
    }
    node->key = given_key;

    if(list->first == NULL) {//list is empty
        list->first = node;
        node->next = NULL;
    } else {
        Node* crt_node = list->first;
        while(crt_node->next != NULL) {
            crt_node = crt_node->next;
        }

        crt_node->next = node;
        node->next = NULL;
    }
}

int main() {

    List* list = init_list();
    create_node(list, 4);
    printf("%d", list->first->key);

    return 0;
}
