#include <math.h>
#include <stdio.h>

int f(double x, double y)
{
    return y > 0 == sin(x) < y;
}

int main(void)
{
    double x, y;
    double dx = 1.0 / 16, dy = 1.0 / 16;
    for (y = 1.0; y >= -1.0; y -= dy)
    {
        for (x = 0.0; x < 6.28; x += dx)
        {
            putchar(f(x, y) ? ' ' : '*');
        }
        putchar('\n');
    }
    getchar();
    return 0;
}
