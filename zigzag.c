#include <stdio.h>
#include <stdlib.h>

void printArr(int arr[][4], int size)
{
    printf("- begin -\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("-  end  -\n");
}

void zigzag1(int arr[][4], int size)
{
    int *tmp = malloc(sizeof(int) * size * size);
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tmp[k++] = arr[i][j]; // flatten array
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int s = i + j;
            int t;
            if (s < size)
            {
                t = s * (s + 1) / 2 + ((i + j) % 2 ? i : j);
                arr[i][j] = tmp[t];
            }
            else
            {
                s = size * 2 - 2 - i - j;
                t = size * (size - 1) - s * (s + 1) / 2 + ((i + j) % 2 ? i : j);
                arr[i][j] = tmp[t];
            }
        }
    }
    free(tmp);
}

void zigzag2(int arr[][4], int size)
{
    int i = 0;
    int j = 0;
    int *tmp = malloc(size * size * sizeof(int));

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            *((tmp + i * size) + j) = *(*(arr + x) + y);

            if ((i == size - 1 || i == 0) && j % 2 == 0)
            {
                j++;
            }
            else if ((j == 0 || j == size - 1) && i % 2 == 1)
            {
                i++;
            }
            else if ((i + j) % 2 == 0)
            {
                i--;
                j++;
            }
            else if ((i + j) % 2 == 1)
            {
                i++;
                j--;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = tmp[i * size + j];
        }
    }

    free(tmp);
}

int main(void)
{
    int arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    const int size = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, size);
    zigzag2(arr, size);
    printArr(arr, size);
    return 0;
}
