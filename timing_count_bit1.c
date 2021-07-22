/*
比较不同的计算位1的个数的算法的时间复杂度
*/

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_BIT (CHAR_BIT * sizeof(int))

typedef int (*pfun_t)(int x);

int method_1(int x);
int method_2(int x);
int method_3(int x);
int method_4(int x);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 循环右移
    time_test(method_2); // 优化的循环右移
    time_test(method_3); // x &= x - 1消去最右边的1
    time_test(method_4); // 查表
    return 0;
}

// 平均循环（INT_BIT）次
int method_1(int x)
{
    int cnt = 0;

    for (int i = 0; i < INT_BIT; i++)
    {
        cnt += (x >> i) & 1;
    }

    return cnt;
}

// 平均循环（INT_BIT - N）次，N=前导零个数分布均值
int method_2(int x)
{
    int cnt = 0;

    if (x < 0)
    {
        // 去掉最高位方便逻辑右移，可移植
        x &= ~(1 << (INT_BIT - 1));
        cnt++;
    }

    while (x != 0)
    {
        cnt += x & 1;
        x >>= 1;
    }

    return cnt;
}

// 平均循环（INT_BIT/2 - N）次
int method_3(int x)
{
    int cnt = 0;

    while (x != 0)
    {
        x &= x - 1;
        cnt++;
    }

    return cnt;
}

// 平均循环（INT_BIT/M - N）次，M=log2(sizeof(table))，N=前导零个数分布均值
int method_4(int x)
{
    // 0-15 位1的个数(M=4)
    static int table[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

    int cnt = 0;

    if (x < 0)
    {
        // 去掉最高位方便逻辑右移，可移植
        x &= ~(1 << (INT_BIT - 1));
        cnt++;
    }

    while (x != 0)
    {
        cnt += table[x & 0xf];
        x >>= 4;
    }

    return cnt;
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e6; // 多次运行取平均值
    int result;     // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(9); // 计算9中位1的个数 => 2
    }
    end = clock();

    printf("method %d result: %d\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
