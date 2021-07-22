#include <stdio.h>

int isPrime(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    for (int i = 2; i < 100; i++)
    {
        isPrime(i) ? printf("%d ", i) : 0;
    }
    return 0;
}
