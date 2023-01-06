#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int item_t;

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void bubble_sort(item_t arr[], int n);
void insertion_sort(item_t arr[], int n);
void shell_sort(item_t arr[], int n);
void selection_sort(item_t arr[], int n);
void heap_sort(item_t arr[], int n);
void merge_sort(item_t arr[], int n);
void quick_sort(item_t arr[], int n);
void radix_sort(item_t arr[], int n);

#endif // SORT_H
