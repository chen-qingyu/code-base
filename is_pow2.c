#include <stdio.h>

int power2(int);

int main(void)
{
    int x = 0;
    while (1)
    {
        printf("Please enter a number to judge the power of 2, \"q\" to quit: ");
        if (scanf("%d", &x))
        {
            if (x & (x - 1) || x == 0)
            {
                printf("%d isn't the power of 2.\n", x);
            }
            else
            {
                printf("%d is the %d power of 2.\n", x, power2(x));
            }
        }
        else
        {
            break;
        }
    }

    printf("Bye!\n");
    return 0;
}

int power2(int x)
{
    int i = 0;
    while (x > 1)
    {
        x >>= 1;
        i++;
    }
    return i;
}
