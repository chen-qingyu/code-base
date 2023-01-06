#include "sort.h"

void selection_sort(item_t arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_position = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_position])
            {
                min_position = j;
            }
        }
        if (min_position != i)
        {
            item_t tmp = arr[i];
            arr[i] = arr[min_position];
            arr[min_position] = tmp;
        }
    }
}
