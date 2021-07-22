#include <stdio.h>

int main(void)
{
    int a, b, tmp;
    scanf("%d %d", &a, &b);
    while (b != 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    if (a == 1)
    {
        printf("YES");
    }
    else
    {
        printf("No");
    }

    return 0;
}
