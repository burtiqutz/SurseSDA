#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int * array ; /* change this type to store other types of values */
    int size ;
    int capacity ;
} SEQ_LIST ;

SEQ_LIST * create_seq_list ( int init_capacity ) {
    SEQ_LIST* list = NULL;

    list = malloc(sizeof(SEQ_LIST));
    if(list != NULL) {
        memset(list, 0, sizeof(SEQ_LIST));
    }

    list->capacity = init_capacity;
    list->array = malloc(init_capacity * sizeof(int));
    list->size = 0;

    return list;
}

void destroy_seq_list ( SEQ_LIST** list ) {
    free((*list)->array);
    free(*list);
    *list = NULL;
}

void print ( const SEQ_LIST * list ){
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void seql_insert_first ( SEQ_LIST * list , int key ) {
    if(list->size == list->capacity) {//list is full
        realloc(list->array, 2 * list->capacity * sizeof (int));
        list->capacity = 2 * list->capacity;//updating capacity
    }
    if(list == NULL){
        perror("couldnt allocate mem");
        exit(-1);
    }
    for(int i = list->size; i >= 1; i-- ) {
        list->array[i] = list->array[i - 1];
    }
    list->array[0] = key;
    list->size++;
}

void seql_insert_last ( SEQ_LIST * list , int key) {
    if(list->size == list->capacity) {//list is full
        realloc(list->array, 2 * list->capacity * sizeof (int));
        list->capacity = 2 * list->capacity;//updating capacity
    }
    if(list == NULL){
        perror("couldnt allocate mem");
        exit(-2);
    }
    list->array[list->size] = key;
    list->size++;
}

int seql_search ( const SEQ_LIST * list , int key ){/* return value is the position */
    int i = 0;
    while(list->array[i] != key && i != list->size) {
        i++;
    }

    return i;
}

void seql_delete_first ( SEQ_LIST * list ) {
    for(int i = 0; i < list->size; i++) {
        list->array[i] = list->array[i+1];
    }
    list->size--;
}

void seql_delete_last ( SEQ_LIST * list) {
    list->array[list->size - 1] = 0;
    list->size--;
}

void seql_delete_key ( SEQ_LIST * list , int key ){
    int pos = seql_search(list, key);
    if (pos == -1){
        return;
    }

    for(int i = pos; i < list->size; i++) {
        list->array[i] = list->array[i+1];
    }
    list->size--;
}

int main() {

    SEQ_LIST* list = create_seq_list(8);
    if(list == NULL) {
        perror("failed init main");
        exit(-3);
    }

    seql_insert_first(list, 5);
    seql_insert_first(list, 2);
    seql_insert_first(list, 7);

    print(list);
    printf("%d\n", seql_search(list, 2));
    printf("%d\n", seql_search(list, 20));//if key doesnt exist it will be the val of size

    seql_delete_key(list,12);
    print(list);

    destroy_seq_list(&list);
    return 0;
}
