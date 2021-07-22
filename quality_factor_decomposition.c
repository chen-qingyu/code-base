#include <stdio.h>

int main()
{
    long n;
    scanf("%ld", &n);
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            printf("%d ", i);
            n /= i;
        }
    }
    if (n != 1)
    {
        printf("%d ", n);
    }
    return 0;
}