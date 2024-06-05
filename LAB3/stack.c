#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    STACK *stack = NULL;

    stack = create_stack();

    stack_push(stack, 8);
    stack_push(stack, 4);
    stack_push(stack, 3);
    stack_push(stack, 6);

    print_stack_contents(stack);  // 6 3 4 8
    printf("\n");

    stack_pop(stack);
    stack_pop(stack);

    print_stack_contents(stack);  // 4 8
    printf("\n");

    stack_push(stack, 2);
    stack_push(stack, 6);

    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);

    print_stack_contents(stack);  // 8
    printf("\n");

    stack_pop(stack);
    stack_pop(stack); // the stack is already empty

    destroy_stack(&stack);
    stack = NULL;

    return 0;
}
