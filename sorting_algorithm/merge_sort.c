#include "sort.h"

static inline void merge(item_t arr[], int start, int median, int stop, item_t space[])
{
    int lb = median - start;
    int lc = stop - median;

    item_t* A = arr + start;  // A[0, stop - start) = arr[start, stop)
    item_t* B = space;        // B[0, lb) = arr[start, median)
    item_t* C = arr + median; // C[0, lc) = arr[median, stop)

    for (int i = 0; i < lb; i++)
    {
        B[i] = A[i];
    }
    for (int i = 0, j = 0, k = 0; j < lb;)
    {
        if ((k < lc) && (C[k] < B[j]))
        {
            A[i++] = C[k++];
        }
        if ((lc <= k) || (B[j] <= C[k]))
        {
            A[i++] = B[j++];
        }
    }
}

static inline void sort(item_t arr[], int start, int stop, item_t space[])
{
    if (stop - start <= 1)
    {
        return;
    }

    int median = (start + stop) >> 1;
    sort(arr, start, median, space);        // sort [start, median)
    sort(arr, median, stop, space);         // sort [median, stop)
    merge(arr, start, median, stop, space); // merge [start, stop)
}

void merge_sort(item_t arr[], int n)
{
    item_t* space = (item_t*)malloc(n * sizeof(item_t));
    check_pointer(space);

    sort(arr, 0, n, space);

    free(space);
}
