#include <math.h>
#include <stdio.h>

#define L (3.14 * 2)

int f(double x, double y)
{
    return (y > 0) == (sin(x) < y);
}

int main(void)
{
    double dx = 1.0 / 16, dy = 1.0 / 16;
    for (double y = 1.0; y >= -1.0; y -= dy)
    {
        for (double x = 0.0; x < L; x += dx)
        {
            putchar(f(x, y) ? ' ' : '*');
        }
        putchar('\n');
    }

    return 0;
}
