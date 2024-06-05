#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *array;
    int capacity;
    int head;
    int tail;
	int size;
}QUEUE;

QUEUE *create_queue(int capacity) {
    QUEUE *queue = NULL;

    queue = (QUEUE*) malloc(sizeof(QUEUE));
    if(queue == NULL)
        return NULL; ///couldnt allocate mem

    memset(queue, 0, sizeof(QUEUE));
    queue->array = (int*) malloc(capacity * sizeof(int));
    queue->capacity = capacity;

    return queue;
}

void destroy_queue(QUEUE **queue) {
    if(*queue == NULL)
        return;

    free((*queue)->array);
    (*queue)->array = NULL;
    free(*queue);
    *queue = NULL;
}

void queue_enqueue(QUEUE *queue, int key) {
    if (queue == NULL)
        return;

    if(queue->tail == queue->head && queue->size == queue->capacity) ///queue is full
        return;

    queue->array[queue->tail] = key;
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
}

int queue_dequeue(QUEUE *queue) {
    if (queue == NULL)///queue not created
        return -1;
    if (queue->array == NULL)///array not created
        return -1;
    if(queue->tail == queue->head && queue->size == 0) ///queue is empty
        return -1;

    int key = queue->array[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return key;
}

void print_queue_contents(const QUEUE *queue)
{
    if (queue == NULL)///queue not created
        return;
    if (queue->array == NULL)///array not created
        return;
    if(queue->tail == queue->head && queue->size == 0) ///queue is empty
        return;

    for(int i = 0; i < queue->size; i++) {
        printf("%d ", queue->array[(queue->head + i) % queue->capacity] );
    }
    printf("\n");
}



int main() {
    QUEUE *queue = NULL;

    queue = create_queue(7);

    queue_enqueue(queue, 1);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 5);
    queue_enqueue(queue, 2);

    print_queue_contents(queue); // 1 3 5 2
    printf("\n");

    queue_dequeue(queue);
    queue_dequeue(queue);

    print_queue_contents(queue); // 5 2
    printf("\n");

    queue_enqueue(queue, 4);
    queue_enqueue(queue, 9);
    queue_enqueue(queue, 2);
    queue_enqueue(queue, 6);

    print_queue_contents(queue); // 5 2 4 9 2 6
    printf("\n");

    queue_dequeue(queue);

    print_queue_contents(queue); // 2 4 9 2 6
    printf("\n");

    queue_enqueue(queue, 3);
    queue_enqueue(queue, 7);

    print_queue_contents(queue); // 2 4 9 2 6 3 7
    printf("\n");

    queue_enqueue(queue, 9);  // overflow

    destroy_queue(&queue);

    return 0;
}
