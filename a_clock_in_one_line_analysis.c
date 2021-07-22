#include <stdio.h>

int main(void)
{
    for (int i = 447; i >= 0; i--)
    {
        if (i % 64)
        {
            char a = ">'txiZ^(~z?"[__TIME__[7 - i / 8 % 8] - 48] + 1;
            char b = ";;;====~$::199"[i * 2 & 8 | i / 64];
            if ((i & 2) == 0)
            {
                b /= 8;
            }
            b %= 8;
            char c = a >> b;
            if (c % 2)
            {
                putchar('!');
            }
            else
            {
                putchar(' ');
            }
        }
        else
        {
            putchar('\n');
        }
    }

    return 0;
}
