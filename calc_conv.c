#include <stdio.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

void conv(int coef[], int data[], int out[], int coef_len, int data_len);

int main(void)
{
    int coef[] = {1, 2, 3, 4};
    int data[] = {1, 1, 1, 1, 0, 0, 0, 0};
    int coef_len = sizeof(coef) / sizeof(coef[0]);
    int data_len = sizeof(data) / sizeof(data[0]);
    int out[coef_len + data_len - 1];
    for (int i = 0; i < coef_len + data_len - 1; i++)
    {
        out[i] = 0;
    }

    conv(coef, data, out, coef_len, data_len);

    for (int i = 0; i < coef_len + data_len - 1; i++)
    {
        printf("%d ", out[i]);
    }

    return 0;
}

void conv(int coef[], int data[], int out[], int coef_len, int data_len)
{
    int i, j;
    int k = coef_len + data_len - 1;

    for (i = 0; i < k; i++)
    {
        for (j = MAX(0, i + 1 - data_len); j <= MIN(i, coef_len - 1); j++)
        {
            out[i] += coef[j] * data[i - j];
        }
    }
}
