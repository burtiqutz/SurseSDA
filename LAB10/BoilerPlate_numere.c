#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _node{
    int key;
    struct _node* next;
}NodeT;
NodeT* list;
void insertOrdered(int x){
    NodeT* node = list;
    NodeT *prev = NULL;
    if(list == NULL){
        list = (NodeT*) malloc(sizeof(NodeT));
        list->next = NULL;
    }
    while(x > node->key){
        prev = node;
        node = node->next;
    }
    NodeT *new = (NodeT*) malloc(sizeof(NodeT));
    new->key = x;
    new->next = NULL;
    if(new == NULL){
        exit(-1);
    }

    if(node == NULL){//last node
        prev->next = new;
    } else {
        prev->next = new;
        new->next = node;
    }
}
void insertInList(int* a, int n){
    for(int i = 0; i < n; i++){
        insertOrdered(a[i]);
    }
}
long long solve(int* a, int n){
	//returneaza costul pentru descompunerea optima	
	long long cost = 0;
    insertInList(a, n);

	return cost;
}

int main(){
	int tests;
	long long sol;
	int n;
	int* a;
	FILE* f = fopen("date_numere.txt", "r");
	if (f==NULL){
	  printf("Fisier inexistent\n");
	  return -1;
	}
	fscanf(f,"%d", &tests);
	for (int testi = 0; testi < tests; testi++){
		fscanf(f, "%d%I64d", &n, &sol);
		a = (int*)malloc(n*sizeof(int));
		for (int i = 0; i < n; i++)
			fscanf(f, "%d", a + i);		
		long long cost = solve(a, n);
		printf("test %d: result %10I64d, expected %10I64d\n", testi, cost, sol);
		free(a);
	}
	fclose(f);
	return 0;
}
