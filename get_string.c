#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define STEP 10

char *getstr(void);

int main(void)
{
    while (1)
    {
        char *str = NULL;
        str = getstr();
        printf("str=%s\n\n", str);
        free(str);
    }
    return 0;
}

char *getstr(void)
{
    char *tmp, *str = (char *)malloc(STEP);
    int c = 0, len = 0, times = 1, number = 0;
    if (!str)
    {
        printf("鍐呭瓨涓嶈冻!\n");
        return (char *)NULL;
    }

    number += times * STEP;
    while ((c = getchar()) != '\n')
    {
        if (len == number)
        {
            times++;
            number = times * STEP;
            tmp = str;
            str = (char *)realloc(str, number);
            if (str == NULL)
            {
                puts("鍐呭瓨涓嶈冻!\n");
                str = tmp;
                break;
            }
        }
        *(str + len) = c;
        len++;
    }
    str = (char *)realloc(str, len + 1);
    *(str + len) = '\0';

    return str;
}
