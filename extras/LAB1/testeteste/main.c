#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SLL_NODE
{
    int key ; /* key field */
    struct _SLL_NODE * next ; /* reference / pointer to next node */
} SLL_NODE ;

typedef struct
{
    SLL_NODE * first ; /* reference / pointer to the first node */
    SLL_NODE * last ; /* reference / pointer to the last node */

} SL_LIST ;

SLL_NODE * sll_search ( const SL_LIST * list , int givenKey ) {
    SLL_NODE* crt_node = list->first;
    while(crt_node != NULL) {
        if(crt_node->key == givenKey) {
            return crt_node;
        }
        else{
            crt_node = crt_node->next;
        }
    }
}

int main() {

    SL_LIST * list = NULL ;
    list = ( SL_LIST *) malloc ( sizeof ( SL_LIST ));
    if ( list != NULL ) {
        memset ( list , 0, sizeof ( SL_LIST ));
    }

    SLL_NODE* node = NULL;
    node = (SLL_NODE*) malloc(sizeof (SLL_NODE));
    if(node != NULL) {
        memset(node, 0, sizeof(SLL_NODE));
        node->key = 69;
    }

    if(list->first == NULL) {
        list->first = node;
        list->last  = node;
    }

        return 0;
}
