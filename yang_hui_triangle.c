#include <stdio.h>

#define LEVEL 13

int main(void)
{
    // initialize
    int arr[LEVEL][LEVEL] = {0};
    for (int r = 0; r < LEVEL; ++r)
    {
        arr[r][0] = 1;
    }
    for (int r = 0; r < LEVEL; ++r)
    {
        arr[r][r] = 1;
    }

    // calculate
    for (int r = 1; r < LEVEL; ++r)
    {
        for (int c = 1; c < r; ++c)
        {
            arr[r][c] = arr[r - 1][c - 1] + arr[r - 1][c];
        }
    }

    // print
    for (int r = 0; r < LEVEL; ++r)
    {
        for (int c = 0; c < LEVEL - r; ++c)
        {
            printf("%3c", ' ');
        }
        for (int c = 0; c <= r; ++c)
        {
            printf("%3d%3c", arr[r][c], ' ');
        }
        printf("\n\n");
    }

    return 0;
}
