#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    char input[64] = {0};
    while (true)
    {
        printf("C-SQL> ");
        gets(input);

        if (strcmp(input, ".exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Unrecognized command '%s'.\n", input);
        }
    }

    return 0;
}
