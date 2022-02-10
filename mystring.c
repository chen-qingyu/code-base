/******************************************
 * FileName: mystring.c
 * Brief: 自己用的简单C字符串库
 * Author: 青羽
 * Blog: https://chen-qingyu.github.io/
 * CreateDate: 2022.02.09
 ******************************************/

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1
#define ERROR_MEM_ALLOC "ERROR: Memory allocation failed."

// Judge whether two strings are equal
// Because "!strcmp(s1, s2)" representing equality is not intuitive
bool str_eq(const char *_str1, const char *_str2)
{
    return strcmp(_str1, _str2) == 0;
}

// Convert string to lowercase
char *str_lower(char *_str)
{
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        _str[i] = tolower(_str[i]);
    }
    return _str;
}

// Convert string to uppercase
char *str_upper(char *_str)
{
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        _str[i] = toupper(_str[i]);
    }
    return _str;
}

// Dump string
char *str_dump(const char *_str)
{
    char *s = (char *)malloc(strlen(_str) + 1);
    if (s == NULL)
    {
        fprintf(stderr, ERROR_MEM_ALLOC);
        exit(EXIT_FAILURE);
    }

    strcpy(s, _str);
    return s;
}

// Ignore case version of strcmp
int str_cmp_i(const char *_str1, const char *_str2)
{
    char *s1 = str_dump(_str1);
    char *s2 = str_dump(_str2);
    int ret = strcmp(s1, s2);
    free(s1);
    free(s2);
    return ret;
}

// Ignore case version of strncmp
int str_n_cmp_i(const char *_str1, const char *_str2, size_t _maxCount)
{
    char *s1 = str_dump(_str1);
    char *s2 = str_dump(_str2);
    str_lower(s1);
    str_lower(s2);
    int ret = strncmp(s1, s2, _maxCount);
    free(s1);
    free(s2);
    return ret;
}

// String replace
// Will change the source string (because the size may change)
// Therefore, the return value must not be ignored
char *str_replace(char *_str, const char *_old, const char *_new)
{
    char *buf = (char *)malloc(strlen(_str) + 1);
    if (buf == NULL)
    {
        fprintf(stderr, ERROR_MEM_ALLOC);
        exit(EXIT_FAILURE);
    }
    memset(buf, 0, strlen(_str) + 1);

    int k = 1;
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        if (!strncmp(_str + i, _old, strlen(_old)))
        {
            buf = (char *)realloc(buf, strlen(_str) + 1 + (strlen(_new) - strlen(_old)) * k);
            if (buf == NULL)
            {
                fprintf(stderr, ERROR_MEM_ALLOC);
                exit(EXIT_FAILURE);
            }
            strcat(buf, _new);
            i += strlen(_old) - 1;
            ++k;
        }
        else
        {
            strncat(buf, _str + i, 1);
        }
    }
    free(_str);

    return buf;
}

// String replace ignores case
// Will change the source string (because the size may change)
// Therefore, the return value must not be ignored
char *str_replace_i(char *_str, const char *_old, const char *_new)
{
    char *buf = (char *)malloc(strlen(_str) + 1);
    if (buf == NULL)
    {
        fprintf(stderr, ERROR_MEM_ALLOC);
        exit(EXIT_FAILURE);
    }
    memset(buf, 0, strlen(_str) + 1);

    int k = 1;
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        if (!str_n_cmp_i(_str + i, _old, strlen(_old)))
        {
            buf = (char *)realloc(buf, strlen(_str) + 1 + (strlen(_new) - strlen(_old)) * k);
            if (buf == NULL)
            {
                fprintf(stderr, ERROR_MEM_ALLOC);
                exit(EXIT_FAILURE);
            }
            strcat(buf, _new);
            i += strlen(_old) - 1;
            ++k;
        }
        else
        {
            strncat(buf, _str + i, 1);
        }
    }
    free(_str);

    return buf;
}

// Use the KMP algorithm to find the substring
// Return the substring position or NOT_FOUND (-1)
int str_find(const char *_str, const char *_pattern)
{
    int n = strlen(_str);
    int m = strlen(_pattern);

    if (n < m)
    {
        return NOT_FOUND;
    }

    int *match = (int *)malloc(sizeof(int) * m);
    if (match == NULL)
    {
        fprintf(stderr, ERROR_MEM_ALLOC);
        exit(EXIT_FAILURE);
    }
    match[0] = NOT_FOUND;

    for (int j = 1; j < m; j++)
    {
        int i = match[j - 1];
        while ((i >= 0) && (_pattern[i + 1] != _pattern[j]))
        {
            i = match[i];
        }
        if (_pattern[i + 1] == _pattern[j])
        {
            match[j] = i + 1;
        }
        else
        {
            match[j] = NOT_FOUND;
        }
    }

    int s = 0;
    int p = 0;
    while (s < n && p < m)
    {
        if (_str[s] == _pattern[p])
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

    free(match);

    return (p == m) ? (s - m) : NOT_FOUND;
}

// TEST
int main(void)
{
    char *s = str_dump("Hello World!");

    assert(str_eq(s, "Hello World!"));
    assert(str_eq(str_lower(s), "hello world!"));
    assert(str_eq(str_upper(s), "HELLO WORLD!"));
    assert(str_eq(s = str_replace(s, "HELLO", "Hi"), "Hi WORLD!"));
    assert(str_eq(s = str_replace(s, "Hi", "Beautiful"), "Beautiful WORLD!"));
    assert(str_eq(s = str_replace_i(s, "world", "girl"), "Beautiful girl!"));
    assert(str_eq(s = str_replace_i(s, "i", "woooooooooow"), "Beautwoooooooooowful gwoooooooooowrl!"));
    assert(str_find(s, "ooooo") == 6);
    assert(str_find(s, "B") == 0);
    assert(str_find(s, "A") == NOT_FOUND);
    assert(str_find(s, "!") == 36);
    assert(str_find(s, "!!") == NOT_FOUND);
    assert(str_eq(s + str_find(s, "gw"), "gwoooooooooowrl!"));

    free(s);

    return 0;
}
