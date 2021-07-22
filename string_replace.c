#include <stdio.h>

void replace(char *, char, char);

int main(void)
{
    char str[99], ch1, ch2;

    while (1)
    {
        printf("Please enter a character string and two chars:\n");
        scanf("%s %c %c", str, &ch1, &ch2);
        printf("Original string: %s\n", str);
        replace(str, ch1, ch2);
        printf("Replaced string: %s\n\n", str);
    }

    return 0;
}

void replace(char *s, char ch1, char ch2)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ch1)
        {
            s[i] = ch2;
        }
    }
}
