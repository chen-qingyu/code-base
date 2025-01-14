#include <stdio.h>

int main(void)
{
    int a = 0x01;
    char* p = (char*)&a;

    printf("The system is %s endian.\n", p[0] == 0x01 ? "little" : "big");

    return 0;
}
