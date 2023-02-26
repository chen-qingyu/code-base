#include "sort.h"

/*
关于这个快速排序算法的几点，我需要说明一下：
1. 使用时应设置一个快排阈值，当待排序的元素数量大于这个阈值时才进入快排，否则调用简单排序。
因为快速排序会频繁递归，当待排序的元素数量充分小时，快速排序可能还不如简单排序快。
2. 快排的参数一般有三个：数组首地址、左边起始下标、右边结束下标，网上的快排程序大多都是这样的。
这里我把它简化到了两个参数：待排序的元素首地址、待排序的元素个数。
因为快排会频繁地递归，所以原始版本会push push push…… pop pop pop……，这个版本就是push push…… pop pop……
总的来说，就是减少了大概三分之一的函数调用开销。我一开始以为会增加程序的复杂度，降低可读性，但是写完之后发现似乎并没有降低可读性。
并且这样刚好符合 void xxxx_sort(item_t arr[], int n) 这样的函数接口，就不用再重新写一个符合接口的函数然后再调用递归了。
*/

static inline item_t median(item_t arr[], int n)
{
    int left = 0, right = n - 1;
    int center = (left + right) / 2;

    if (arr[left] > arr[center])
    {
        swap(&arr[left], &arr[center]);
    }
    if (arr[left] > arr[right])
    {
        swap(&arr[left], &arr[right]);
    }
    if (arr[center] > arr[right])
    {
        swap(&arr[center], &arr[right]);
    }

    swap(&arr[center], &arr[right - 1]);

    return arr[right - 1];
}

// TODO
void quick_sort(item_t arr[], int n)
{
    if (n < 3)
    {
        return;
    }

    int pivot = median(arr, n);
    int low = 0;
    int high = n - 2;

    while (1)
    {
        while (arr[++low] < pivot)
            ;
        while (arr[--high] > pivot)
            ;
        if (low < high)
        {
            swap(&arr[low], &arr[high]);
        }
        else
        {
            break;
        }
    }

    swap(&arr[low], &arr[n - 2]);

    quick_sort(arr, low);
    quick_sort(arr + low + 1, n - low - 1);
}
