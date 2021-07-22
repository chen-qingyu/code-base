#include <stdio.h>
#define N 10

int main(void)
{
    int arr[N][N] = {0};
    int i, j;

    for (i = 0; i < N; ++i)
    {
        arr[i][0] = 1;
    }
    for (i = 0; i < N; ++i)
    {
        arr[i][i] = 1;
    }

    for (i = 1; i < N; ++i)
    {
        for (j = 1; j < i; ++j)
        {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N - i; ++j)
        {
            printf("%3c", ' ');
        }
        for (j = 0; j <= i; ++j)
        {
            printf("%3d%3c", arr[i][j], ' ');
        }
        printf("\n\n");
    }

    getchar();
    return 0;
}
