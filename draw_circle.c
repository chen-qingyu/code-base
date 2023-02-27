#include <stdio.h>

#define R 10

int f(int x, int y)
{
    return (x - R) * (x - R) + (y - R) * (y - R) <= R * R;
}

int main(void)
{
    for (int y = 0; y <= 2 * R; y++)
    {
        for (int x = 0; x <= 2 * R; x++)
        {
            printf(f(x, y) ? "* " : "  ");
        }
        printf("\n");
    }

    return 0;
}
