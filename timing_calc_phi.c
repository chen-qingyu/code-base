#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double (*pfun_t)(int N);

double method_1(int N);
double method_2(int N);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 斐波那契数列
    time_test(method_2); // 连分数

    getchar();
    return 0;
}

double method_1(int N)
{
    long t1 = 1, t2 = 1;
    long next;
    for (int i = 0; i < N; ++i)
    {
        next = t1 + t2;
        t1 = t2;
        t2 = next;
    }
    return (double)t1 / t2;
}

double method_2(int N)
{
    if (N == 0)
    {
        return 0.618;
    }
    else
    {
        return 1.0 / (method_2(N - 1) + 1);
    }
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e5; // 多次运行取平均值
    int N = 40;     // 迭代次数
    double result;  // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(N); // 计算黄金分割比phi的值
    }
    end = clock();

    printf("method %d result: %lf\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
