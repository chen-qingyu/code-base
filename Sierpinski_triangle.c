#include <math.h>
#include <stdio.h>
#include <string.h>

int map[1024][1024];
void Sierpinski_triangle(int, int, int);

int main(void)
{
    int n;
    puts("Enter the size(1-5, q to quit) of Sierpinski triangle and look it~\n");
    while (printf("Enter: ") && scanf("%d", &n))
    {
        if (n < 0 || n > 5)
        {
            continue;
        }
        memset(map, 0, sizeof(map));
        Sierpinski_triangle(0, 0, n);
        for (int j = 0; j < pow(2, n); j++)
        {
            for (int k = 0; k < pow(2, n + 1); k++)
            {
                putchar(map[j][k] == 1 ? '*' : ' ');
            }
            putchar('\n');
        }
    }
    puts("\nBye~");

    return 0;
}

void Sierpinski_triangle(int x, int y, int num)
{
    if (num == 0)
    {
        map[x][y] = 1;
    }
    else
    {
        int temp = pow(2, num - 1);
        Sierpinski_triangle(x, y + temp, num - 1);
        Sierpinski_triangle(x + temp, y + temp * 2, num - 1);
        Sierpinski_triangle(x + temp, y, num - 1);
    }
}
