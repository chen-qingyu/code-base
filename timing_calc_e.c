#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double (*pfun_t)(int N);

double method_1(int N);
double method_2(int N);
double method_3(int N);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 直接利用定义求极限
    time_test(method_2); // 级数求和
    time_test(method_3); // 不知名的高级方法

    getchar();
    return 0;
}

double method_1(int N)
{
    return pow(1 + 1.0 / N, N);
}

double method_2(int N)
{
    double e = 1, n = 1;
    for (int i = 1; i < N; ++i)
    {
        n *= 1.0 / i;
        e += n;
    }
    return e;
}

double method_3(int N)
{
    unsigned i, j, k = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j <= RAND_MAX; j += rand())
        {
            k++;
        }
    }
    return (double)k / N;
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e5; // 多次运行取平均值
    int N = 1000;   // 迭代次数
    double result;  // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(N); // 计算自然常数e的值
    }
    end = clock();

    printf("method %d result: %lf\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
