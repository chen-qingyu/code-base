#include <stdio.h>

int main(int argc, char const *argv[])
{
    short x = -4321;
    printf("x=-4321, unsigned short=%hu, short=%hd\n", x, x);

    unsigned short y = 65535;
    printf("y=65535, unsigned short=%hu, short=%hd\n", y, y);

    return 0;
}
