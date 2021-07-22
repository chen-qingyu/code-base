#include <stdio.h>

int main(void)
{
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf(" %d * %d = %2d |", i, j, i * j);
            if (i == j)
            {
                printf("\n");
                for (int k = 0; k < i; k++)
                {
                    printf("-------------");
                }
                printf("\n");
            }
        }
    }
    printf("By ChenQingyu.\n");
    getchar();
    return 0;
}
