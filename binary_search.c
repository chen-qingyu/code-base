#include <assert.h>
#include <stdio.h>

int binary_search(int arr[], int size, int element)
{
    int left = 0, right = size - 1;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (element > arr[mid])
        {
            left = mid + 1;
        }
        else if (element < arr[mid])
        {
            right = mid - 1;
        }
        else // element == arr[mid], found
        {
            return mid;
        }
    }
    return -1; // not found
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(binary_search(arr, size, 0) == -1);
    assert(binary_search(arr, size, 1) == 0);
    assert(binary_search(arr, size, 5) == 4);
    assert(binary_search(arr, size, 9) == 8);
    assert(binary_search(arr, size, 10) == -1);

    printf("Test OK.\n");

    return 0;
}
