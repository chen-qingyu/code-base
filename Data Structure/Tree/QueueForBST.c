#include "BinarySearchTree.h"

#include "QueueForBST.h"

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

queue_t *Queue_Create(void)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void Queue_Destroy(queue_t *queue)
{
    free(queue);
}

int Queue_Size(const queue_t *queue)
{
    return (queue->rear - queue->front + (QUEUE_CAPACITY + 1)) % (QUEUE_CAPACITY + 1);
}

bool Queue_IsEmpty(const queue_t *queue)
{
    return Queue_Size(queue) == 0;
}

void Queue_Enqueue(queue_t *queue, queue_data_t data)
{
    if (Queue_Size(queue) == QUEUE_CAPACITY)
    {
        fprintf(stderr, "The queue is full.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->data[queue->rear] = data;
}

queue_data_t Queue_Dequeue(queue_t *queue)
{
    if (Queue_IsEmpty(queue))
    {
        fprintf(stderr, "The queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    queue->front = (queue->front + 1) % QUEUE_CAPACITY;

    return queue->data[queue->front];
}
