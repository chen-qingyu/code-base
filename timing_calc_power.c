#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long (*pfun_t)(int x, int n);

long long my_pow(int x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)
    {
        long long y = my_pow(x, n / 2);
        return y * y;
    }
    else
    {
        long long y = my_pow(x, (n - 1) / 2);
        return x * y * y;
    }
}

long long normal_pow(int x, int n)
{
    long long y = 1;
    while (n-- > 0)
    {
        y *= x;
    }
    return y;
}

long long std_pow(int x, int n)
{
    return (long long)pow(x, n);
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e5;   // 运行次数
    long long result; // 储存计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(3, 30); // 计算
    }
    end = clock();

    printf("method %d result: %lld\n", i, result);
    printf("method %d duration: %lf s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC);
}

int main(void)
{
    time_test(my_pow);     // 0.002000 s
    time_test(normal_pow); // 0.005000 s
    time_test(std_pow);    // 0.003000 s

    return 0;
}
