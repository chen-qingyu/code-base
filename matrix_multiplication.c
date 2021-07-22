#include <stdio.h>
#define MAX_SIZE 100

int main(void)
{
    int matrix1[MAX_SIZE][MAX_SIZE], matrix2[MAX_SIZE][MAX_SIZE];
    int matrix[MAX_SIZE][MAX_SIZE]; // 3个矩阵
    int row1, col1, row2, col2;     // 前两个矩阵的行数和列数

    printf("Please input matrix 1's row and col:\n");
    scanf("%d %d", &row1, &col1);
    printf("Please input matrix 1:\n");
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("Please input matrix 2's row and col:\n");
    scanf("%d %d", &row2, &col2);
    printf("Please input matrix 2:\n");
    for (int i = 0; i < row2; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            scanf("%d", &matrix2[i][j]);
        }
    }

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            for (int k = 0; k < col1; k++)
            {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("The result is:\n");
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}