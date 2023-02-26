#include <stdio.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

// 计算卷积
void conv(const int coef[], const int data[], int out[], int coef_len, int data_len)
{
    int k = coef_len + data_len - 1;

    for (int i = 0; i < k; i++)
    {
        for (int j = MAX(0, i + 1 - data_len); j <= MIN(i, coef_len - 1); j++)
        {
            out[i] += coef[j] * data[i - j];
        }
    }
}

int main(void)
{
    const int coef[] = {1, 2, 3, 4};
    const int data[] = {1, 1, 1, 1, 0, 0, 0, 0};
    int coef_len = sizeof(coef) / sizeof(coef[0]);
    int data_len = sizeof(data) / sizeof(data[0]);
    int out_len = coef_len + data_len - 1;
    int out[out_len];
    for (int i = 0; i < out_len; i++)
    {
        out[i] = 0;
    }

    conv(coef, data, out, coef_len, data_len);

    for (int i = 0; i < out_len; i++)
    {
        printf("%d ", out[i]);
    }

    return 0;
}
