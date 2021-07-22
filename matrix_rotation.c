#include <stdio.h>

int main(void)
{
    int a[4][4], b[4][4];
    int r, c;
    printf("Please enter the 4x4 matrix:\n");
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            scanf("%d", &a[r][c]);
        }
    }
    printf("The matrix is:\n");
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            printf("%-5d", a[r][c]);
        }
        printf("\n");
    }
    printf("The rotated matrix is:\n");
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            printf("%-5d", a[c][3 - r]);
        }
        printf("\n");
    }

    return 0;
}
