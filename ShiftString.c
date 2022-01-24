#include <stdio.h>
#include <string.h>

void ShiftString(char *s, int n)
{
    char t;
    int len = strlen(s);
    for (int i = 0; i < n; ++i)
    {
        t = s[0];
        for (int j = 0; s[j] != '\0'; ++j)
        {
            s[j] = s[j + 1];
        }
        s[len - 1] = t;
    }
}

int main(int argc, char const *argv[])
{
    char s[] = "ABCDEFGHIJK";
    ShiftString(s, 3);
    printf("%s\n", s);

    return 0;
}
