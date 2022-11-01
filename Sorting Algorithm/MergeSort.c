#include "Sort.h"

void merge(item_t arr[], item_t tmpArr[], int left, int mid, int right)
{
    int tmp = left;
    int start = left, end = right;
    int leftEnd = mid - 1;

    while (left <= leftEnd && mid <= right)
    {
        if (arr[left] <= arr[mid])
        {
            tmpArr[tmp++] = arr[left++];
        }
        else
        {
            tmpArr[tmp++] = arr[mid++];
        }
    }

    while (left <= leftEnd)
    {
        tmpArr[tmp++] = arr[left++];
    }
    while (mid <= right)
    {
        tmpArr[tmp++] = arr[mid++];
    }

    for (int i = start; i <= end; i++)
    {
        arr[i] = tmpArr[i];
    }
}

void mergePass(item_t arr[], item_t tmpArr[], int n, int length)
{
    int i;

    for (i = 0; i <= n - 2 * length; i += 2 * length)
    {
        merge(arr, tmpArr, i, i + length, i + 2 * length - 1);
    }

    if (i + length < n)
    {
        merge(arr, tmpArr, i, i + length, n - 1);
    }
    else
    {
        for (int j = i; j < n; j++)
        {
            tmpArr[j] = arr[j];
        }
    }
}

void mergeSort(item_t arr[], int n)
{
    int length = 1;
    item_t* tmpArr = malloc(n * sizeof(item_t));
    if (tmpArr == NULL)
    {
        fprintf(stderr, "ERROR: file %s, function %s, line %d : There was not enough memory.\n", __FILE__, __FUNCTION__, __LINE__);
        exit(-2);
    }

    while (length < n)
    {
        mergePass(arr, tmpArr, n, length);
        length *= 2;
        mergePass(tmpArr, arr, n, length);
        length *= 2;
    }
    free(tmpArr);
}
