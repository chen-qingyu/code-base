#include "Sort.h"

void PercDown(item_t arr[], int r, int n)
{
    /* 将n个元素的数组中以arr[r]为根的子堆调整为最大堆 */
    int parent, child;
    item_t tmp;

    tmp = arr[r];
    for (parent = r; (parent * 2 + 1) < n; parent = child)
    {
        child = parent * 2 + 1;
        if ((child != n - 1) && (arr[child] < arr[child + 1]))
        {
            child++;
        }
        if (tmp >= arr[child])
        {
            break;
        }
        else
        {
            arr[parent] = arr[child];
        }
    }
    arr[parent] = tmp;
}

void heapSort(item_t arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        PercDown(arr, i, n);
    }

    for (int i = n - 1; i > 0; i--)
    {
        item_t tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        PercDown(arr, 0, i);
    }
}
