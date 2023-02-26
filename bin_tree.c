#include <limits.h>
#include <stdio.h>

#define SIZE (CHAR_BIT * sizeof(int))

void dtob(int n, char* p);
void show(const char* p);

int main(void)
{
    char bin[SIZE + 1];

    for (int num = 1; num < 256; ++num)
    {
        printf("%3d: ", num);
        dtob(num, bin);
        show(bin);
    }

    return 0;
}

void dtob(int n, char* p)
{
    for (int i = SIZE - 1; i >= 0; i--, n >>= 1)
    {
        p[i] = (1 & n) + '0';
    }
    p[SIZE] = '\0';
}

void show(const char* p)
{
    for (int i = 0; p[i] != '\0'; i++)
    {
        putchar(p[i] == '0' || p[i] == '\0' ? ' ' : '*');
    }
    putchar('\n');
}
