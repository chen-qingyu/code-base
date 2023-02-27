#include <stdio.h>
#include <stdlib.h>

char* get_string(void)
{
    static const int init_capacity = 10;
    char* str = (char*)malloc(init_capacity);
    if (str == NULL)
    {
        fprintf(stderr, "malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    int size = 0;
    int capacity = init_capacity;
    int ch;
    while ((ch = getchar()) != '\n')
    {
        if (size + 1 == capacity) // need to expand capacity, be careful '\0'
        {
            capacity *= 2;
            str = (char*)realloc(str, capacity);
            if (str == NULL)
            {
                fprintf(stderr, "malloc failed!\n");
                exit(EXIT_FAILURE);
            }
        }
        str[size++] = ch; // append a char
    }
    str[size] = '\0';

    return str;
}

int main(void)
{
    printf("Arbitrary length string input function.\n");
    while (1)
    {
        printf(">>> ");
        char* str = get_string();
        printf("input=\"%s\"\n\n", str);
        free(str);
    }
    return 0;
}
