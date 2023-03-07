#include <stdio.h>

// 计算Fibonacci数列的前n项(f(0)=0,f(1)=1)，结果放进f数组里
void fib(int n, unsigned int f[])
{
    unsigned int fst = 0, snd = 1;
    for (int i = 0; i < n; i++)
    {
        f[i] = fst;
        unsigned int tmp = fst + snd;
        fst = snd;
        snd = tmp;
    }
}

int main(void)
{
    const int size = 48;
    unsigned int f[size];

    fib(size, f);

    for (int i = 0; i < size; ++i)
    {
        printf("fib(%d) = %u\n", i, f[i]);
    }

    return 0;
}
