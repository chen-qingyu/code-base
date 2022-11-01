#include "List.h"

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

// Check whether the position is within the valid range. (begin <= pos < end).
static void checkBounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out Of Range.");
        exit(EXIT_FAILURE);
    }
}

/*******************************
Interface functions implementation.
*******************************/

list_t *List_Create(void)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL)
    {
        fprintf(stderr, "ERROR: (file %s, line %d) There was not enough memory.\n", __FILE__, __LINE__);
        exit(-2);
    }

    list->count = 0;
    list->capacity = 8;
    list->data = (list_data_t *)malloc(sizeof(list_data_t) * list->capacity);

    return list;
}

void List_Destroy(list_t *list)
{
    free(list->data);
    free(list);
}

int List_Size(const list_t *list)
{
    return list->count;
}

bool List_IsEmpty(const list_t *list)
{
    return list->count == 0;
}

list_data_t List_At(const list_t *list, int i) // list[i]
{
    checkBounds(i, 0, list->count);

    return list->data[i];
}

int List_Find(const list_t *list, list_data_t data)
{
    int index = 0;

    while (index < list->count && list->data[index] != data)
    {
        index++;
    }

    return (index < list->count) ? index : -1;
}

void List_Insert(list_t *list, int i, list_data_t data)
{
    checkBounds(i, 0, list->count + 1);

    if (list->count == list->capacity) // Expand capacity
    {
        list->capacity *= 2; // Double the capacity
        list_data_t *tmp = (list_data_t *)malloc(sizeof(list_data_t) * list->capacity);
        for (size_t i = 0; i < list->count; ++i)
        {
            *(tmp + i) = list->data[i];
        }
        free(list->data);
        list->data = tmp;
    }

    for (int j = list->count; j > i; j--)
    {
        list->data[j] = list->data[j - 1];
    }
    list->data[i] = data;
    ++list->count;
}

void List_Delete(list_t *list, int i)
{
    checkBounds(i, 0, list->count);

    for (int j = i + 1; j < list->count; j++)
    {
        list->data[j - 1] = list->data[j];
    }
    --list->count;
}

void List_Traverse(list_t *list, void (*pTrav)(list_data_t data))
{
    for (int i = 0; i < list->count; i++)
    {
        pTrav(list->data[i]);
    }
}

void List_Reverse(list_t *list)
{
    for (int i = 0, j = list->count - 1; i < j; ++i, --j)
    {
        list_data_t tmp = list->data[i];
        list->data[i] = list->data[j];
        list->data[j] = tmp;
    }
}
