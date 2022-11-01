#include "MaxHeap.h"

#define HEAP_CAPACITY 100

#define MAX_ITEM INT_MAX // heap_data_t

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

heap_t *MaxHeap_Create(void)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if (heap == NULL)
    {
        fprintf(stderr, "ERROR: There was not enough memory.\n");
        exit(-2);
    }
    heap->data = (heap_data_t *)malloc((HEAP_CAPACITY + 1) * sizeof(heap_data_t));
    if (heap->data == NULL)
    {
        fprintf(stderr, "ERROR: There was not enough memory.\n");
        exit(-2);
    }

    heap->size = 0;
    heap->capacity = HEAP_CAPACITY;
    heap->data[0] = MAX_ITEM;

    return heap;
}

void MaxHeap_Destroy(heap_t *heap)
{
    free(heap->data);
    free(heap);
}

bool MaxHeap_IsFull(const heap_t *heap)
{
    return heap->size == heap->capacity;
}

bool MaxHeap_IsEmpty(const heap_t *heap)
{
    return heap->size == 0;
}

void MaxHeap_Insert(heap_t *heap, heap_data_t data)
{
    if (MaxHeap_IsFull(heap))
    {
        printf("The heap is full.\n");
        return;
    }

    int i;
    for (i = ++heap->size; heap->data[i / 2] < data; i /= 2)
    {
        heap->data[i] = heap->data[i / 2];
    }
    heap->data[i] = data;
}

heap_data_t MaxHeap_Delete(heap_t *heap)
{
    if (MaxHeap_IsEmpty(heap))
    {
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    int parent, child;
    heap_data_t maxItem, tmp;

    maxItem = heap->data[1];
    tmp = heap->data[heap->size--];

    for (parent = 1; parent * 2 <= heap->size; parent = child)
    {
        child = parent * 2;
        if ((child != heap->size) && (heap->data[child] < heap->data[child + 1]))
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
