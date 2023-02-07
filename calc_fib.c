#include <stdio.h>

// 计算Fibonacci数列的第n项(f(0)=0,f(1)=1)
unsigned long long fib(int n)
{
    unsigned long long fst = 0, snd = 1;
    while (n-- > 0)
    {
        unsigned long long tmp = fst + snd;
        fst = snd;
        snd = tmp;
    }
    return fst;
}

int main(void)
{
    for (int i = 0; i < 50; ++i)
    {
        printf("fib(%d) = %llu\n", i, fib(i));
    }

    return 0;
}
