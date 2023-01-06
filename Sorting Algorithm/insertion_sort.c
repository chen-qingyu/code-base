#include "sort.h"

void insertion_sort(item_t arr[], int n)
{
    for (int i = 1, j; i < n; i++)
    {
        item_t tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}
