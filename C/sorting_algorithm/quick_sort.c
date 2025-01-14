#include "sort.h"

static inline void sort(item_t arr[], int left, int right)
{
    if (left < right)
    {
        swap(&arr[left], &arr[(left + right) / 2]);
        int i = left, j = right, pivot = arr[left];
        while (i < j)
        {
            while (i < j && arr[j] > pivot)
            {
                j--;
            }
            if (i < j)
            {
                arr[i++] = arr[j];
            }

            while (i < j && arr[i] < pivot)
            {
                i++;
            }
            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }
        arr[i] = pivot;
        sort(arr, left, i - 1);
        sort(arr, i + 1, right);
    }
}

void quick_sort(item_t arr[], int n)
{
    sort(arr, 0, n - 1);
}
