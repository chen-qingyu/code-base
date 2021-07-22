#include <stdio.h>

int main(void)
{
    int a, b, gcd;
    scanf("%d %d", &a, &b);
    if (a <= 0 || b <= 0)
    {
        return 0;
    }
    for (gcd = a < b ? a : b; gcd > 0; gcd--)
    {
        if ((a % gcd == 0) && (b % gcd == 0))
        {
            break;
        }
    }
    printf("GCD: %d\nLCM: %d\n", gcd, (a * b) / gcd);
    getchar();
    getchar();
    return 0;
}
