#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum {WHITE, GREY, BLACK};

typedef struct _STACK_NODE {
    int key;
    struct _STACK_NODE *next;
} STACK_NODE;

typedef struct {
    STACK_NODE *top;
}STACK;

STACK_NODE *create_stack_node(int value) {
    STACK_NODE* node = NULL;
    node = malloc(sizeof(STACK_NODE));

    if(node == NULL) {
        return NULL;
    }

    memset(node, 0, sizeof (STACK_NODE ));
    node->key = value;

    return node;
}

STACK *create_stack() {
    STACK *stack = NULL;
    stack = (STACK*) malloc(sizeof(STACK));
    if(stack == NULL)
        return NULL;
    memset(stack, 0, sizeof(STACK));

    return stack;
}

void destroy_stack(STACK **stack) {
    if(*stack == NULL)
        return;

    STACK_NODE* node = (*stack)->top;
    STACK_NODE *prev = NULL;
    while(node != NULL){
        prev = node;
        node = node->next;
        free(prev);
    }

    free(*stack);
    *stack = NULL;
}

void stack_push(STACK *stack, int key) {
    if (stack == NULL)
        return;

    STACK_NODE* new = NULL;
    new = (STACK_NODE *) create_stack_node(key);
    if(new == NULL)
        return;

    new->next = stack->top;
    stack->top = new;
}

int stack_pop(STACK *stack) {
    if(stack == NULL)
        return -1;

    STACK_NODE* node = stack->top;
    if (node == NULL)
        return -1;
    int key = 0;
    stack->top = stack->top->next;
    key = node->key;
    free(node);

    return key;
}

void print_stack_contents(const STACK *stack) {
    if (stack == NULL)
        return;
    if(stack->top == NULL)
        return;
	STACK_NODE* node = stack->top;
    while(node != NULL){
        printf("%d ", node->key);
        node = node->next;
    }
    printf("\n");
}

typedef struct {
    int numVertices;
    int** adjMatrix;
} Graph;

typedef struct {
    int *array;
    int capacity;
    int head;
    int tail;
    int size;
} QUEUE;

QUEUE *create_queue(int capacity) {
    QUEUE *queue = NULL;

    queue = (QUEUE*)malloc(sizeof(QUEUE));
    if(queue == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    memset(queue, 0, sizeof(QUEUE));
    queue->array = (int*)malloc(capacity * sizeof(int));
    queue->capacity = capacity;

    return queue;
}

bool isEmpty(QUEUE* queue) {
    return queue->size == 0;
}

void queue_enqueue(QUEUE *queue, int key) {
    if(queue == NULL)
        return;

    if(queue->tail == queue->head && queue->size == queue->capacity) {
        perror("Stack is full");
        return;
    }
    queue->array[queue->tail] = key;
    queue->tail = (queue->tail + 1) % (queue->capacity);
    queue->size++;
}

int queue_dequeue(QUEUE *queue) {
    if (queue == NULL)
        return -1;
    if (queue->array == NULL)
        return -1;
    if(queue->tail == queue->head && queue->size == 0)
        return -1;

    int key = queue->array[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return key;
}

typedef struct {
    int* parent;
    int* distance;
} BFSInfo;

BFSInfo BFS(Graph* graph, int startVertex) {
    BFSInfo info;
    info.parent = (int*)malloc(graph->numVertices * sizeof(int));
    info.distance = (int*)malloc(graph->numVertices * sizeof(int));

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = WHITE;
        info.distance[i] = -1;
        info.parent[i] = -1;
    }

    QUEUE* queue = create_queue(graph->numVertices);
    visited[startVertex] = GREY;
    info.distance[startVertex] = 0;
    queue_enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = queue_dequeue(queue);
        printf("Visited vertex: %d, Parent: %d, Distance: %d\n", currentVertex, info.parent[currentVertex], info.distance[currentVertex]);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] && visited[i] == WHITE) {
                visited[i] = GREY;
                info.parent[i] = currentVertex;
                info.distance[i] = info.distance[currentVertex] + 1;
                queue_enqueue(queue, i);
            }
        }
        visited[currentVertex] = BLACK;
    }

    free(visited);
    free(queue->array);
    free(queue);

    return info;
}

Graph* createAndInitGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    graph->adjMatrix[0][1] = 1;
    graph->adjMatrix[1][0] = 1;
    graph->adjMatrix[0][2] = 1;
    graph->adjMatrix[2][0] = 1;
    graph->adjMatrix[1][3] = 1;
    graph->adjMatrix[3][1] = 1;
    graph->adjMatrix[1][4] = 1;
    graph->adjMatrix[4][1] = 1;
    graph->adjMatrix[2][4] = 1;
    graph->adjMatrix[4][2] = 1;
    graph->adjMatrix[3][5] = 1;
    graph->adjMatrix[5][3] = 1;
    graph->adjMatrix[4][5] = 1;
    graph->adjMatrix[5][4] = 1;

//    graph->adjMatrix[0][3] = 1;
//    graph->adjMatrix[3][0] = 1;

    return graph;
}

enum {red, black, not_visited};

void process_cycle(BFSInfo* info, int vertex1, int vertex2){
    STACK* stack;
    stack = create_stack();
    while(vertex1 != vertex2){
        printf("%d ", vertex1);
        stack_push(stack, vertex2);
        vertex1 = *info[vertex1].parent;
        vertex2 = *info[vertex2].parent;
    }
    printf("%d ", vertex1);
    print_stack_contents(stack);
}

bool is_bipartite(Graph* graph, int startVertex){
    BFSInfo* info = (BFSInfo*) malloc(sizeof(BFSInfo));
    info->parent = (int*)malloc(graph->numVertices * sizeof(int));
    info->distance = (int*)malloc(graph->numVertices * sizeof(int));

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = not_visited;
        info->distance[i] = -1;
        info->parent[i] = -1;
    }

    QUEUE* queue = create_queue(graph->numVertices);
    visited[startVertex] = red;
    info->distance[startVertex] = 0;
    queue_enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = queue_dequeue(queue);
        //printf("Visited vertex: %d, Parent: %d, Distance: %d\n", currentVertex, info->parent[currentVertex], info->distance[currentVertex]);

        for (int i = 0; i < graph->numVertices; i++) {
            ///TODO
            if (graph->adjMatrix[currentVertex][i] && visited[i] == not_visited) {
                ///trebuie inca un check pt a vedea daca urmatorul nod e de ac culoare
                visited[i] = (visited[currentVertex] == red) ? black : red;
                info->parent[i] = currentVertex;
                info->distance[i] = info->distance[currentVertex] + 1;
                queue_enqueue(queue, i);
            } else if(graph->adjMatrix[currentVertex][i] && visited[i] == visited[currentVertex] && currentVertex != i){
                ///found a node with same color
                process_cycle(info, currentVertex, i);
                return false;
            }
        }
    }
    return true;
}



int main() {
    int numVertices = 6;
    Graph* graph = createAndInitGraph(numVertices);

    BFSInfo info = BFS(graph, 0);

    free(info.parent);
    free(info.distance);
    for (int i = 0; i < numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    graph = createAndInitGraph(numVertices);

    bool bi = is_bipartite(graph, 0);
    if (bi)
        puts("bipartite");
    else puts ("not bipartite");
    free(graph->adjMatrix);
    free(graph);


    return 0;
}
