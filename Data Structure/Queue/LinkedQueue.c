#include "Queue.h"

#include <stdio.h>
#include <stdlib.h>

struct node
{
    queue_data_t data;
    struct node *next;
};

struct queue
{
    struct node *front;
    struct node *rear;
    int count;
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

    queue->front = (struct node *)malloc(sizeof(struct node));
    check_pointer(queue->front);

    queue->rear = queue->front;
    queue->front->next = NULL;
    queue->count = 0;

    return queue;
}

void Queue_Destroy(queue_t *queue)
{
    while (queue->front)
    {
        struct node *current = queue->front->next;
        free(queue->front);
        queue->front = current;
    }
    free(queue);
}

int Queue_Size(const queue_t *queue)
{
    return queue->count;
}

bool Queue_IsEmpty(const queue_t *queue)
{
    return queue->count == 0;
}

void Queue_Enqueue(queue_t *queue, queue_data_t data)
{
    struct node *add = (struct node *)malloc(sizeof(struct node));
    check_pointer(add);

    add->data = data;
    add->next = NULL;

    queue->rear->next = add;
    queue->rear = add;

    ++queue->count;
}

queue_data_t Queue_Dequeue(queue_t *queue)
{
    if (queue->count == 0)
    {
        fprintf(stderr, "ERROR: The queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *del = queue->front->next;
    queue_data_t data = del->data;

    queue->front->next = del->next;
    free(del);

    --queue->count;

    return data;
}
