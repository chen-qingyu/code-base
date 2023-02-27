#include <limits.h>
#include <stdio.h>

#define SIZE (CHAR_BIT * sizeof(int))

void dtob(int n, char* p);
void show(const char* p);

int main(void)
{
    char bin[SIZE + 1];
    int num;

    puts("Enter integers and see them in binary (q to quit):\n");
    while (scanf("%d", &num))
    {
        dtob(num, bin);
        show(bin);
    }
    puts("Bye~");

    return 0;
}

void dtob(int n, char* p)
{
    for (int i = SIZE - 1; i >= 0; i--)
    {
        p[i] = (1 & n) + '0';
        n >>= 1;
    }
    p[SIZE] = '\0';
}

void show(const char* p)
{
    for (int i = 0; p[i] != '\0'; i++)
    {
        putchar(p[i]);
        if ((i + 1) % 4 == 0)
        {
            putchar(' ');
        }
    }
    printf("\n\n");
}
