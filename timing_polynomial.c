/*
比较不同的计算多项式的算法的时间复杂度
f(x) = a0 + a1*x + a2*x^2 + a3*x^3 + ... + an*x^n

可用作比较算法时间复杂度的通用模板
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double (*pfun_t)(int n, double a[], double x);

double method_1(int n, double a[], double x);
double method_2(int n, double a[], double x);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 暴力算法
    time_test(method_2); // 秦九韶算法
    getchar();
    return 0;
}

double method_1(int n, double a[], double x)
{
    double y = 0;
    for (int i = 0; i <= n; i++)
    {
        y += a[i] * pow(x, i);
    }
    return y;
}

double method_2(int n, double a[], double x)
{
    double y = 0;
    for (int i = n; i >= 0; i--)
    {
        y = a[i] + x * y;
    }
    return y;
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e7;                              // 多次运行取平均值
    double a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 升幂排列的多项式系数
    double result;                               // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method((sizeof(a) / sizeof(a[0]) - 1), a, 1.1); // 计算f(1.1)的值
    }
    end = clock();

    printf("method %d result: %lf\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
