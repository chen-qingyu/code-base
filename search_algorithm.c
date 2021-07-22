#include <stdio.h>

int sequential_search(int arr[], int size, int search);
int binary_search(int arr[], int size, int search);

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key, search = 9;

    // key = sequential_search(arr, size, search);
    key = binary_search(arr, size, search);

    printf("search: %d\n", search);
    if (key == -1)
    {
        printf("Not find.\n");
    }
    else
    {
        printf("arr[%d] == %d\n", key, search);
    }

    getchar();
    return 0;
}

int sequential_search(int arr[], int size, int search)
{
    for (int i = 0; i < size; ++i)
    {
        if (search == arr[i])
        {
            return i;
        }
    }
    return -1;
}

int binary_search(int arr[], int size, int search)
{
    int left = 0, right = size - 1, mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (search > arr[mid])
        {
            left = mid + 1;
        }
        else if (search < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
