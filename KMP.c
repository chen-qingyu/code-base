#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int pos_t;
#define NOT_FOUND -1

void BuildMatch(char *pattern, int *match)
{
    pos_t i, j;
    int m = strlen(pattern);
    match[0] = -1;

    for (j = 1; j < m; j++)
    {
        i = match[j - 1];
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
        {
            i = match[i];
        }
        if (pattern[i + 1] == pattern[j])
        {
            match[j] = i + 1;
        }
        else
        {
            match[j] = -1;
        }
    }
}

pos_t KMP(char *string, char *pattern)
{
    int n = strlen(string);
    int m = strlen(pattern);
    pos_t s, p, *match;

    if (n < m)
    {
        return NOT_FOUND;
    }

    match = (pos_t *)malloc(sizeof(pos_t) * m);
    BuildMatch(pattern, match);
    s = 0;
    p = 0;

    while (s < n && p < m)
    {
        if (string[s] == pattern[p])
        {
            s++;
            p++;
        }
        else if (p > 0)
        {
            p = match[p - 1] + 1;
        }
        else
        {
            s++;
        }
    }
    return (p == m) ? (s - m) : NOT_FOUND;
}

int main()
{
    char string[] = "This is a simple example.";
    char pattern[] = "simple";

    pos_t p = KMP(string, pattern);

    if (p == NOT_FOUND)
    {
        printf("Not Found.\n");
    }
    else
    {
        printf("%s\n", string + p);
    }

    return 0;
}
