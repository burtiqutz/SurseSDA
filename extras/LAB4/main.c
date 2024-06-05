#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    int id ; /* node name */
    struct node_type * left , * right ;
} NodeT;

NodeT * createBinTreeFromFile ( FILE * f)
{
    NodeT *p;
    int c;
/* se citeste id - ul nodului */
    fscanf (f , "%d" , &c);
    if ( c == 0 )
        return NULL ; /* arbore vid , nu facem nimic */
    else /* else inclus pentru claritate */
    { /* construim nodul la care pointeaza p */
        p = ( NodeT *) malloc ( sizeof ( NodeT ));
        if ( p == NULL ) {
            puts ( " Nu mai avem memorie in createBinTree " );
            exit (1) ;
        }
/* se populeaza nodul */
        p -> id = c;
        p -> left = createBinTreeFromFile (f);
        p -> right = createBinTreeFromFile (f);
    }
    return p;
}

void preorder ( NodeT *p )
// p = nodul curent ;
{
    if ( p != NULL )
    {
        printf ( "%d " , p -> id );
        preorder ( p -> left );
        preorder ( p -> right );
    }
}

void inorder ( NodeT *p )
// p = nodul curent ;
{
    if ( p != NULL )
    {
        inorder ( p -> left );
        printf ( "%d " , p -> id );
        inorder ( p -> right );
    }
}

void postorder ( NodeT *p )
// p = nodul curent ;
{
    if ( p != NULL )
    {
        postorder ( p -> left );
        postorder ( p -> right );
        printf ( "%d " , p -> id );
    }
}

int leaf_node(NodeT* node) {
    if(node == NULL)
        return 0;
    else if(node->left == NULL && node->right == NULL)
        return 1;
    else
        return leaf_node(node->left) + leaf_node( node->right);
}

void show_leaves(NodeT* root){
    if (root == NULL)
        return;

    if(root->right == NULL && root->left == NULL)
        printf("%d ", root->id);
    show_leaves(root->left);
    show_leaves(root->right);
}

int count_intern(NodeT* root){
    if (root == NULL)
        return 0;

    if(root->left != NULL && root->right != )
}

int main() {
    NodeT * root ;
    FILE *f = fopen ("ArboreBinar.txt" , "r");
    if (! f){
        printf (" Nu se poate deschide fisierul ArboreBinar . txt \n");
        return -1;
    }
    root = createBinTreeFromFile (f);

    printf("Preorder print: ");
    preorder(root);
    puts("");
    printf("Inorder print: ");
    inorder(root);
    puts("");
    printf("Postorder print: ");
    postorder(root);
    puts("");
    puts("");

    printf("There are %d leaves\n", leaf_node(root));
    printf("Leaf nodes are: ");
    show_leaves(root);
    puts("");

    fclose (f);
    return 0;
}
