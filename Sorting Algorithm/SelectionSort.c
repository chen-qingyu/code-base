#include "Sort.h"

void selectionSort(item_t arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minPosition = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minPosition])
            {
                minPosition = j;
            }
        }
        if (minPosition != i)
        {
            item_t tmp = arr[i];
            arr[i] = arr[minPosition];
            arr[minPosition] = tmp;
        }
    }
}
