#include <math.h>
#include <stdio.h>
#include <string.h>

int map[1024][1024];

void sierpinski_triangle(int x, int y, int level)
{
    if (level == 0)
    {
        map[x][y] = 1;
    }
    else
    {
        int temp = pow(2, level - 1);
        sierpinski_triangle(x, y + temp, level - 1);
        sierpinski_triangle(x + temp, y + temp * 2, level - 1);
        sierpinski_triangle(x + temp, y, level - 1);
    }
}

int main(void)
{
    int n;
    puts("Please input the size (0-6) of Sierpinski triangle and look it~ (q to quit)\n");
    while (printf("size: ") && scanf("%d", &n))
    {
        if (n < 0 || n > 6)
        {
            puts("Please input the size (0-6) of Sierpinski triangle and look it~ (q to quit)\n");
            continue;
        }

        memset(map, 0, sizeof(map));
        sierpinski_triangle(0, 0, n);

        int row = pow(2, n);
        int col = pow(2, n + 1);
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                putchar(map[r][c] == 1 ? '*' : ' ');
            }
            putchar('\n');
        }
    }
    puts("Bye~");

    return 0;
}
