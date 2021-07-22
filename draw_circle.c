#include <stdio.h>

#define WIDTH 20
#define HEIGHT 20

int f(int x, int y)
{
    return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;
}

int main(void)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            printf(f(x, y) ? "* " : "  ");
        }
        puts("");
    }
    getchar();
    return 0;
}