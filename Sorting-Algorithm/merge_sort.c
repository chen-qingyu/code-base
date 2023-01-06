#include "sort.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void merge_sort(item_t arr[], int n)
{
    item_t* data = arr;
    item_t* space = (item_t*)malloc(n * sizeof(item_t));
    check_pointer(space);

    for (int seg = 1; seg < n; seg <<= 1)
    {
        for (int start = 0; start < n; start += seg + seg)
        {
            int low = start, mid = MIN(start + seg, n), high = MIN(start + seg + seg, n);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
            {
                space[k++] = data[start1] < data[start2] ? data[start1++] : data[start2++];
            }
            while (start1 < end1)
            {
                space[k++] = data[start1++];
            }
            while (start2 < end2)
            {
                space[k++] = data[start2++];
            }
        }
        item_t* tmp = data;
        data = space;
        space = tmp;
    }

    if (data != arr)
    {
        for (int i = 0; i < n; i++)
        {
            space[i] = data[i];
        }
        space = data;
    }

    free(space);
}
