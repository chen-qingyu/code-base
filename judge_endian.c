#include <stdio.h>

int main(void)
{
    int a = 0x1;
    char *p = (char *)&a;
    if (p[0] == 0x1)
    {
        printf("little endian.\n");
    }
    else
    {
        printf("big endian.\n");
    }
    return 0;
}
