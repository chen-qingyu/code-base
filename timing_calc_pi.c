#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double (*pfun_t)(int N);

double method_1(int N);
double method_2(int N);
double method_3(int N);
double method_4(int N);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 蒙特·卡罗法
    time_test(method_2); // 均匀撒点
    time_test(method_3); // 级数求和
    time_test(method_4); // 收敛更快的级数求和

    getchar();
    return 0;
}

double method_1(int N)
{
    double x, y, hits = 0;
    for (int i = 0; i < N; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y < 1.0)
        {
            hits++;
        }
    }
    return (hits / N) * 4;
}

double method_2(int N)
{
    double x, y, hits = 0;
    for (x = 0; x * x < N; x++)
    {
        for (y = 0; y * y < N; y++)
        {
            if (x * x + y * y < N)
            {
                hits++;
            }
        }
    }
    return (hits / N) * 4;
}

double method_3(int N)
{
    double pi = 0, k = 1;
    for (int i = 0; i < N; i++)
    {
        pi += k / (2 * i + 1);
        k = -k;
    }
    return pi * 4;
}

double method_4(int N)
{
    double pi = 1, n = 1;
    for (double i = 1; i < N; i++)
    {
        n *= i / (2 * i + 1);
        pi += n;
    }
    return pi * 2;
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e4; // 多次运行取平均值
    int N = 2000;   // 迭代次数
    double result;  // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(N); // 计算圆周率pi的值
    }
    end = clock();

    printf("method %d result: %lf\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
