#include <stdio.h>
#include <stdlib.h>
typedef struct node_type
{
    int id; /* numele nodului */
    /* alte informatii  utile */
    struct node_type *left, *right, *parent;
} NodeT;

void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}

void postorder( NodeT *p ){
    if ( p != NULL )
    {
        postorder ( p -> left );
        postorder ( p -> right );
        printf ( "%d " , p -> id );
    }

}

void inorder( NodeT *p ){
    if ( p != NULL )
    {
        inorder ( p -> left );
        printf ( "%d " , p -> id );
        inorder ( p -> right );
    }
}

int leaf_node(NodeT *node){
    if(node == NULL)
        return 0;
    else if(node->left == NULL && node->right == NULL)
        return 1;
    else
        return leaf_node(node->left) + leaf_node( node->right);   return 0;
}

int noduri_interne(NodeT *node){
   if(node == NULL)
       return 0;
   if(node->left != NULL || node->right != NULL)
       return 1 + noduri_interne(node->left) + noduri_interne(node->right);
}

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

int inaltime(NodeT *node){
   if(node == NULL)
       return -1;

   return 1 + max(inaltime(node->left), inaltime(node->right));
}


void preorder( NodeT *p )
/*
 * p = nodul curent;
*/
{
    if ( p != NULL )
    {
        printf( "%d ", p->id );
        preorder( p->left);
        preorder( p->right);
    }
}
///creaza un arbore binar prin citirea de la tastatura
NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int id;

    /* read node id */
    if ( branch == 0 )
        printf( "Valoarea pentru radacina [0 pt null] =" );
    else if ( branch == 1 )
        printf( "Fiul stang al nodului cu valoarea %d [0 pt null] =",
                parent->id );
    else
        printf( "Fiul drept al nodului cu valoarea %d [0 pt null] =",
                parent->id );
    scanf("%d", &id);
    if ( id == 0 )
        return NULL;
    else
    {
        /* construim nodul la care pointeaza p */
        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL ){
            printf( "Nu mai avem memorie in createBinTree" );
            exit(1);
        }
        /* fill in node */
        p->id = id;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}
NodeT *createBinTreeFromFile(FILE* f)
{
  NodeT *p;
  int c;

  /* se citeste id-ul nodului */
  fscanf(f, "%d", &c);
  if ( c == 0 )
    return NULL; /* arbore vid, nu facem nimic */
  else /* else inclus pentru claritate */
  { /* construim nodul la care pointeaza p */
    p = ( NodeT *) malloc( sizeof( NodeT ));
    if ( p == NULL )
      fatalError( "Nu mai avem memorie in createBinTree" );
    /* se populeaza nodul */
    p->id = c;
    p->left = createBinTreeFromFile(f);
    p->right = createBinTreeFromFile(f);
  }
  return p;
}

NodeT *createBinTreeFromFileWithParents(FILE* f, NodeT** parent)
{
    NodeT *p;
    int c;

    /* se citeste id-ul nodului */
    fscanf(f, "%d", &c);
    if ( c == 0 )
        return NULL; /* arbore vid, nu facem nimic */
    else /* else inclus pentru claritate */
    { /* construim nodul la care pointeaza p */
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Nu mai avem memorie in createBinTree" );
        /* se populeaza nodul */
        p->id = c;
        p->parent = (*parent);
        p->left = createBinTreeFromFileWithParents(f, p);
        p->right = createBinTreeFromFileWithParents(f, p);
    }
    return p;
}

void show_leaves(NodeT* root){
    if (root == NULL)
        return;

    if(root->left == NULL && root->right == NULL)
        printf("%d ", root->id);
    show_leaves(root->left);
    show_leaves(root->right);
}

NodeT* search(NodeT* root, int key){
    if(root == NULL)
        return NULL;

    if (root->id == key)
        return root;
    NodeT* left_node = search(root->left, key);
    if(left_node != NULL)
        return left_node;
    return search(root->right, key);
}

NodeT* createBalBinTree(int nbOfNodes){
    NodeT* p;
    int nLeft, nRight;

    if(nbOfNodes <= 0)
        return NULL;

    nLeft = nbOfNodes / 2;
    nRight = nbOfNodes - nLeft - 1;
    p = (NodeT*) malloc(sizeof (NodeT));
    printf("\nNode identifier = ");
    scanf("%d", &(p->id));
    p->left = createBalBinTree(nLeft);
    p->right = createBalBinTree(nRight);

    return p;
}

void show_internal_nodes(NodeT* root){
    if (root == NULL)
        return;
    if(root->left != NULL || root->right != NULL)
        printf("%d ", root->id);
    show_internal_nodes(root->left);
    show_internal_nodes(root->right);
}

void swap_subtrees(NodeT* root){
    if (root == NULL)
        return;
    NodeT* t = NULL;
    t = root->left;
    root->left = root->right;
    root->right = t;
}

int max_depth(NodeT* root){///basically tree height
    if(root == NULL)
        return -1;

    int lmax, rmax;
    lmax = max_depth(root->left);
    rmax = max_depth(root->right);
        if(lmax > rmax)
        return lmax + 1;
    return rmax + 1;
}

int diameter(NodeT* root){
    if(root == NULL)
        return 0;
    int hleft = inaltime(root->left);
    int hright = inaltime(root->right);
    int dleft = diameter(root->left);
    int dright = diameter(root->right);

    int sum = hleft + hright + 2;
    sum = max(sum, dleft);
    sum = max(sum, dright);
    return sum;
}

void print_nodes_and_parents_preorder(NodeT* root){
    if (root == NULL)
        return;

    printf("node = %d, parent = %d\n", root->id, root->parent);
    print_nodes_and_parents_preorder(root->left);
    print_nodes_and_parents_preorder(root->right);
}

int grad_rudenie(NodeT* root, int child1, int child2){

    NodeT *p1 = search(root, child1);
    NodeT *p2 = search(root, child2);
    if(p1 == NULL || p2 == NULL)
        return -1;
    ///ori caut parintii si construiesc drum intre ei, ori merg simultan pe parinti
    int grad1 = 0;
    int grad2 = 0;
    ///fiecare muchie reprezinta un grad de rudenie presupun ??
    //nu merge varianta de aici pt ca daca sutn pe acelasi copac cu o ramura mai lung ddecat alta , una va creste mai
    //mult decat trebuie
//    do{
//        if(p1->parent != NULL)
//        {
//            p1 = p1->parent;
//            grad1++;
//        }
//        if(p2->parent != NULL)
//        {
//            p2 = p2->parent;
//            grad2++;
//        }
//    }while(p1 != p2);

//ar trebuie sa caut la fiecare pas prin arbore cei doi copii, pana cand nu ii mai gasesc

    return grad1 + grad2;
}

int main()
{
    NodeT *root;
    FILE *f = fopen("ArboreBinar.txt", "r");
    if (!f){
        printf("Nu se poate deschide fisierul ArboreBinar.txt\n");
        return -1;
    }
    root = createBinTreeFromFile(f);
    fclose(f);

    NodeT* root_w_parents = NULL;
    FILE* f1 = fopen("ArboreBinar.txt", "r");
    if (!f1){
        printf("Nu se poate deschide fisierul ArboreBinar.txt\n");
        return -1;
    }
    NodeT *root_father = NULL;
    root_w_parents = createBinTreeFromFileWithParents(f, &root_father);
    fclose(f1);

    printf( "\nParcurgere in preordine\n" );
    preorder( root );
    printf( "\nParcurgere in postordine\n" );
	postorder(root);
    printf( "\nParcurgere in inordine\n" );
	inorder(root);
    printf("\n");

    //////////////////////////////////////
    printf("TEST ARBORE CU PARINTI");
    printf( "\nParcurgere in preordine\n" );
    preorder( root_w_parents );
    printf( "\nParcurgere in postordine\n" );
    postorder(root_w_parents);
    printf( "\nParcurgere in inordine\n" );
    inorder(root_w_parents);
    printf("\n");
    print_nodes_and_parents_preorder(root_w_parents);
    printf("\n");

	int nr_frunze = leaf_node(root);
	printf("Numarul de frunze este %d\n", nr_frunze);//3

    printf( "\nFrunzele sunt: \n" );
    show_leaves(root);

    printf("\nNoduri interne = %d \n", noduri_interne(root));//5
    printf("Nodurile interne sunt: ");
    show_internal_nodes(root);

    printf("\nInaltimea arborelui = %d \n", inaltime(root)); //3

    NodeT* searched_node = search(root, 7);
    if(searched_node != NULL)
    {
        printf("\nSearched node is: %d\n", searched_node->id);
        printf("Height of searched node is: %d\n", inaltime(searched_node));
    }
    else
        printf("\nNode doesn't exist\n");

//    NodeT * root_bal = NULL ;
//    int nbOfNodes = 0;
//    printf ("\n Numarul de noduri din arbore este :");
//    scanf ("%d" , & nbOfNodes );
//    root_bal = createBalBinTree ( nbOfNodes );
//
//    printf( "\nParcurgere in preordine\n" );
//    preorder( root_bal);
//    printf( "\nParcurgere in postordine\n" );
//    postorder(root_bal);
//    printf( "\nParcurgere in inordine\n" );
//    inorder(root_bal);
//    printf("\n");

    printf("Diameter of first tree is: %d\n", diameter(root));

    return 0;
}
