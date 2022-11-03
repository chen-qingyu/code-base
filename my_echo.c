#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    printf("\n");
    return 0;
}
