#include "ArrayQueue.h"

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 100

struct queue
{
    queue_data_t data[QUEUE_CAPACITY + 1]; // 循环队列，数组容量为队列有效容量加一
    int front;
    int rear;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*******************************
Interface functions implementation.
*******************************/

queue_t *ArrayQueue_Create(void)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void ArrayQueue_Destroy(queue_t *queue)
{
    free(queue);
}

int ArrayQueue_Size(const queue_t *queue)
{
    return (queue->rear - queue->front + (QUEUE_CAPACITY + 1)) % (QUEUE_CAPACITY + 1);
}

bool ArrayQueue_IsEmpty(const queue_t *queue)
{
    return ArrayQueue_Size(queue) == 0;
}

void ArrayQueue_Enqueue(queue_t *queue, queue_data_t data)
{
    if (ArrayQueue_Size(queue) == QUEUE_CAPACITY)
    {
        fprintf(stderr, "ERROR: The queue is full.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->data[queue->rear] = data;
}

queue_data_t ArrayQueue_Dequeue(queue_t *queue)
{
    if (ArrayQueue_IsEmpty(queue))
    {
        fprintf(stderr, "ERROR: The queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    queue->front = (queue->front + 1) % QUEUE_CAPACITY;

    return queue->data[queue->front];
}
