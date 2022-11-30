#include "ArrayList.h"

#include <stdio.h>
#include <stdlib.h>

struct list
{
    // Number of elements.
    int count;

    // Available capacity.
    int capacity;

    // Pointer to the data.
    list_data_t *data;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out Of Range: %d not in [%d, %d)\n", pos, begin, end);
        exit(EXIT_FAILURE);
    }
}

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

list_t *ArrayList_Create(void)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    check_pointer(list);

    list->count = 0;
    list->capacity = 8;
    list->data = (list_data_t *)malloc(sizeof(list_data_t) * list->capacity);
    check_pointer(list->data);

    return list;
}

void ArrayList_Destroy(list_t *list)
{
    free(list->data);
    free(list);
}

int ArrayList_Size(const list_t *list)
{
    return list->count;
}

bool ArrayList_IsEmpty(const list_t *list)
{
    return list->count == 0;
}

list_data_t ArrayList_At(const list_t *list, int i) // list[i]
{
    check_bounds(i, 0, list->count);

    return list->data[i];
}

int ArrayList_Find(const list_t *list, list_data_t data)
{
    int index = 0;

    while (index < list->count && list->data[index] != data)
    {
        index++;
    }

    return index < list->count ? index : LIST_NOT_FOUND;
}

void ArrayList_Insert(list_t *list, int i, list_data_t data)
{
    check_bounds(i, 0, list->count + 1);

    if (list->count == list->capacity) // need to expand capacity
    {
        list->capacity *= 2; // double the capacity
        list->data = (list_data_t *)realloc(list->data, sizeof(list_data_t) * list->capacity);
        check_pointer(list->data);
    }

    for (int j = list->count; j > i; j--)
    {
        list->data[j] = list->data[j - 1];
    }
    list->data[i] = data;
    ++list->count;
}

void ArrayList_Delete(list_t *list, int i)
{
    check_bounds(i, 0, list->count);

    for (int j = i + 1; j < list->count; j++)
    {
        list->data[j - 1] = list->data[j];
    }
    --list->count;
}

void ArrayList_Traverse(list_t *list, void (*pTrav)(list_data_t data))
{
    for (int i = 0; i < list->count; i++)
    {
        pTrav(list->data[i]);
    }
}

void ArrayList_Reverse(list_t *list)
{
    for (int i = 0, j = list->count - 1; i < j; ++i, --j)
    {
        list_data_t tmp = list->data[i];
        list->data[i] = list->data[j];
        list->data[j] = tmp;
    }
}
