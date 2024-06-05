#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int *array;
    int capacity;
    int head;
    int tail;
}QUEUE;

QUEUE *create_queue(int capacity) {
    QUEUE *queue = NULL;

    queue = (QUEUE*) malloc(sizeof(QUEUE));
    if(queue == NULL)
        return NULL; ///couldn't allocate mem

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

    if (queue->head == queue->tail + 1){///queue is full, we only lose 1 slot of information
        printf("queue is full\n");
        return;
    }
    queue->array[queue->tail] = key;
    queue->tail = (queue->tail + 1) % queue->capacity;
}

int queue_dequeue(QUEUE *queue) {
    if (queue == NULL)///queue not created
        return -1;
    if (queue->array == NULL)///array not created
        return -1;

    if(queue->tail == queue->head) ///queue is empty
        return -1;
    int key = queue->array[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;

    return key;
}

void print_queue_contents(const QUEUE *queue)
{
    if (queue == NULL)///queue not created
        return;
    if (queue->array == NULL)///array not created
        return;
    if(queue->tail == queue->head) ///queue is empty
        return;

    if (queue->tail <= queue->head)///reverse order
    {
        for(int i = queue->head; i < queue->capacity; i++ ){
            printf("%d ", queue->array[i] );
        }
        for(int i = 0; i < queue->tail; i++){
            printf("%d ", queue->array[i] );
        }
    }
    else {///normal order
        for(int i = queue->head; i < queue->tail; i++){
            printf("%d ", queue->array[i] );
        }
    }
    printf("\n");
}



int main() {
    QUEUE *queue = NULL;

    queue = create_queue(7);///I can only have 6 elements

    print_queue_contents(queue);//nothing

    queue_enqueue(queue, 1);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 5);
    queue_enqueue(queue, 2);

    print_queue_contents(queue); // 1 3 5 2

    queue_dequeue(queue);
    queue_dequeue(queue);

    print_queue_contents(queue); // 5 2

    queue_enqueue(queue, 4);
    queue_enqueue(queue, 9);
    queue_enqueue(queue, 2);
    queue_enqueue(queue, 6);

    print_queue_contents(queue); // 5 2 4 9 2 6

    queue_dequeue(queue);

    print_queue_contents(queue); // 2 4 9 2 6

    queue_enqueue(queue, 3);

    print_queue_contents(queue); // 2 4 9 2 6 3

    queue_enqueue(queue, 9);  // overflow

    destroy_queue(&queue);

    return 0;
}
