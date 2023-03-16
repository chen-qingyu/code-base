#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define INT_BIT (CHAR_BIT * sizeof(int))

int count_bit1_1(int x);
int count_bit1_2(int x);
int count_bit1_3(int x);
int count_bit1_4(int x);

typedef int (*function_t)(int x);
void time_test(function_t function, const char* message, int x);

int main(void)
{
    int xs[] = {-1, 0, 9, 2147483647};
    for (int i = 0; i < sizeof(xs) / sizeof(int); i++)
    {
        printf("Count bit 1 in %d:\n", xs[i]);
        time_test(count_bit1_1, "Rotate right", xs[i]);
        time_test(count_bit1_2, "Optimized rotate right", xs[i]);
        time_test(count_bit1_3, "Eliminate the rightmost 1", xs[i]);
        time_test(count_bit1_4, "Look-up table", xs[i]);
        printf("\n");
    }

    return 0;
}

// O(INT_BIT)
int count_bit1_1(int x)
{
    int cnt = 0;

    for (int i = 0; i < INT_BIT; i++)
    {
        cnt += (x >> i) & 1;
    }

    return cnt;
}

// O(INT_BIT - N), N=前导零个数分布均值
int count_bit1_2(int x)
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

// O(INT_BIT/2 - N), N=前导零个数分布均值
int count_bit1_3(int x)
{
    int cnt = 0;

    while (x != 0)
    {
        x &= x - 1;
        cnt++;
    }

    return cnt;
}

// O(INT_BIT/M - N), M=log2(sizeof(table))，N=前导零个数分布均值
int count_bit1_4(int x)
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

void time_test(function_t function, const char* message, int x)
{
    int result;

    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        result = function(x);
    }
    clock_t end = clock();

    printf("result: %d, duration: %6.2lfms (%s)\n", result, (double)(end - start) / CLOCKS_PER_SEC * 1000, message);
}
