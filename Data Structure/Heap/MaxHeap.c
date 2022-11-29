#include "MaxHeap.h"

#include <stdio.h>
#include <stdlib.h>

struct heap
{
    heap_data_t *data;
    int count;
    int capacity;
};

#define MAX_ITEM INT_MAX // heap_data_t

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

heap_t *MaxHeap_Create(void)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    check_pointer(heap);

    heap->count = 0;
    heap->capacity = 8;
    heap->data = (heap_data_t *)malloc(heap->capacity * sizeof(heap_data_t));
    check_pointer(heap->data);

    heap->data[0] = MAX_ITEM;

    return heap;
}

void MaxHeap_Destroy(heap_t *heap)
{
    free(heap->data);
    free(heap);
}

int MaxHeap_Size(const heap_t *heap)
{
    return heap->count;
}

bool MaxHeap_IsEmpty(const heap_t *heap)
{
    return heap->count == 0;
}

void MaxHeap_Push(heap_t *heap, heap_data_t data)
{
    if (heap->count == heap->capacity) // need to expand capacity
    {
        heap->capacity *= 2; // double the capacity
        heap->data = (heap_data_t *)realloc(heap->data, sizeof(heap_data_t) * heap->capacity);
        check_pointer(heap->data);
    }

    int i;
    for (i = ++heap->count; heap->data[i / 2] < data; i /= 2)
    {
        heap->data[i] = heap->data[i / 2];
    }
    heap->data[i] = data;
}

heap_data_t MaxHeap_Pop(heap_t *heap)
{
    if (heap->count == 0)
    {
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    heap_data_t maxItem = heap->data[1];
    heap_data_t tmp = heap->data[heap->count--];

    int parent, child;
    for (parent = 1; parent * 2 <= heap->count; parent = child)
    {
        child = parent * 2;
        if ((child != heap->count) && (heap->data[child] < heap->data[child + 1]))
        {
            child++;
        }

        if (tmp >= heap->data[child])
        {
            break;
        }
        else
        {
            heap->data[parent] = heap->data[child];
        }
    }
    heap->data[parent] = tmp;

    return maxItem;
}

heap_data_t MaxHeap_Top(heap_t *heap)
{
    if (heap->count == 0)
    {
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    return heap->data[1];
}
