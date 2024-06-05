#include <stdio.h>
#include <stdlib.h>

typedef struct _TREE_NODE
{
    int key;
    struct _TREE_NODE *left;
    struct _TREE_NODE *right;
} TREE_NODE;

TREE_NODE* alloc(int x)
{
    TREE_NODE* q = calloc(1, sizeof(TREE_NODE));
	if (q == NULL)
		return NULL;
    q->key = x;
    return q;
}

void insertNode(TREE_NODE** root, int key) {
    if(root == NULL)
        return;

    if ( (*root) == NULL){
        (*root) = alloc(key);
        if((*root) == NULL){
            perror("alloc issue root");
            exit(-1);
        }
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }


    TREE_NODE* current = (*root);
    int run = 1;
    while(run){///is this the right condition??
        if(key < current->key){
            if(current->left == NULL){///if we have space
                current->left = alloc(key);
                if(current->left == NULL){
                    perror("alloc issue insertion left");
                    exit(-2);
                }
                return;///we exit the loop&func
            }
            else {
                current = current->left;///else we keep searching
            }
        }
        else if (key > current->key){
            if(current->right == NULL){
                current->right = alloc(key);
                if(current->right == NULL){
                    if(current->right == NULL){
                        perror("alloc issue insertion right");
                        exit(-2);
                    }
                }
                return; ///exit loop&func
            }
            else {
                current = current->right;
            }
        }
        else{
            return;
        }
    }
}

TREE_NODE* searchKey(TREE_NODE* root, int key) {
    /* Arborele este vid sau cheia cautata key este in radacina , atunci returnam radacina */
    if ( root == NULL || root -> key == key )
        return root ;
/* Daca cheia key este mai mare decat cheia radacinii , se reia algoritmul pentru
subarborele drept */
    if ( root -> key < key )
        return searchKey( root -> right , key );
/* Daca cheia key este mai mica decat cheia radacinii , se reia algoritmul pentru subarborele
stang */
    return searchKey( root -> left , key );
}

TREE_NODE* findMin(TREE_NODE* root) {
    if(root == NULL)
        return NULL;

    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

TREE_NODE* findMax(TREE_NODE* root) {
    if(root == NULL){
        return NULL;
    }
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

TREE_NODE* succesor(TREE_NODE* root, TREE_NODE* node) {
    if(root == NULL || node == NULL)
        return NULL;
    if(node->right != NULL){
        return findMin(node->right);
    }

    TREE_NODE* p = NULL;
    TREE_NODE *succesor = NULL;
    p = root;
    while(p != node){///traversing tree
        if (p->key > node->key)
        {
            succesor = p;
        }
        if(node->key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }

    }
    return succesor;
}

TREE_NODE* predecesor(TREE_NODE* root, TREE_NODE* node) {
    if(root == NULL || node == NULL)
        return NULL;
    if(node->left != NULL){
        return findMax(node->left);
    }

    TREE_NODE *p = NULL;
    TREE_NODE *predecessor = NULL;
    p = root;
    while(p != node){///traversing tree
        if (p->key < node->key)
        {
            predecessor = p;
        }
        if(node->key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }

    }
    return predecessor;
}
///recursive
void deleteKey(TREE_NODE** root, int key) {
    if(root == NULL)
        return;

    if((*root) == NULL)
        return;

    TREE_NODE *node = *root;

    if(key < node->key){
        deleteKey(&(node->left), key);
    }
    else if(key > node->key){
        deleteKey(&(node->right), key);
    }
    else {
        ///key to be deleted
        if(node->left == NULL && node->right == NULL){
            ///frunza
            free(node);
            *root = NULL;///adresa nodului in care suntem
            return;
        }
        if(node->left == NULL){
           ///right child only
           *root = node->right;
           free(node);
           return;
        }
        if(node->right != NULL){
            ///left child only
            *root = node->left;
            free(node);
            return;
        }

        ///both children
        TREE_NODE *successor = node->right;
        TREE_NODE *suc_parent = node;
        while(successor->left != NULL){
            suc_parent = successor;
            successor = successor->left;
        }
        ///swap node and successor
        int aux = node->key;
        node->key = successor->key;
        successor->key = aux;
        ///2 cazuri, fix primul din dreapta sau o data in dreapta si maxim stanga
        if(suc_parent->left == successor){
            suc_parent->right = successor->right;
            free(successor);
        }
        else {
            suc_parent->left = successor->right;
            free(successor);
        }
    }

}

void inOrder(TREE_NODE* root) {
    if(root != NULL){
        inOrder(root->left);
        printf ( "%d " , root -> key );
        inOrder(root->right);
    }
}

void preOrder(TREE_NODE* root) {
    if ( root != NULL )
    {
        printf ( "%d " , root -> key );
        preOrder ( root -> left );
        preOrder ( root -> right );
    }
}

void postOrder(TREE_NODE* root) {
    if ( root != NULL )
    {
        postOrder ( root -> left );
        postOrder ( root -> right );
        printf ( "%d " , root -> key );
    }
}

int main()
{
    TREE_NODE* root = NULL;

    int keys[] = {15, 6, 18, 17, 20, 3, 7, 2, 4, 13, 9};
    for (int i = 0; i < sizeof(keys) / sizeof(int); i++)
        insertNode(&root, keys[i]);

    printf( "\nPreorder listing\n" );
    preOrder( root);
    printf( "\nInorder listing\n" );
    inOrder( root );
    printf( "\nPostorder listing\n" );
    postOrder( root);
    printf("\n");

    int search_keys[] = {15, 6, 18, 17, 20, 3, 7, 2, 4, 13, 9, -1, 0, 12, 30};
    for(int i = 0; i < sizeof(search_keys) / sizeof(int); i++){
        TREE_NODE* q = searchKey(root, search_keys[i]);
        if (q)
            printf("nodul cu cheia %d a fost gasit la %p\n", search_keys[i], q);
        else
            printf("nodul cu cheia %d nu a fost gasit\n", search_keys[i]);
    }

    TREE_NODE* q = findMin(root);
    printf("Nodul cu cheie minima este: %d %p\n", q->key, q);
    printf("Parcurgere succesori:\n");
    while(q){
        printf("%d ", q->key);
        q = succesor(root, q);
    }
    printf("\n");

    q = findMax(root);
    printf("Nodul cu cheie maxima este: %d %p\n", q->key, q);
    printf("Parcurgere predecesori:\n");
    while(q){
        printf("%d ", q->key);
        q = predecesor(root, q);
    }
    printf("\n");

    int delete_keys[] = {9, 7, 3, 15, 18, -1, 0, 12, 30, 2, 4, 6, 13, 17, 20, 21, 20};
    printf("Arborele inainte de stergeri:\n");
    inOrder(root);
    printf("\n");
    for(int i = 0; i < sizeof(delete_keys) / sizeof(int); i++){
        deleteKey(&root, delete_keys[i]);
        printf("dupa stergere nod cu %d\n", delete_keys[i]);
        inOrder(root);
        printf("\n");
    }

    return 0;
}
