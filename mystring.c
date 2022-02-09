#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    memset(buf, 0, strlen(_str) + 1);

    int k = 1;
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        if (!strncmp(_str + i, _old, strlen(_old)))
        {
            buf = (char *)realloc(buf, strlen(_str) + 1 + (strlen(_new) - strlen(_old)) * k);
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
    memset(buf, 0, strlen(_str) + 1);

    int k = 1;
    for (size_t i = 0; i < strlen(_str); ++i)
    {
        if (!str_n_cmp_i(_str + i, _old, strlen(_old)))
        {
            buf = (char *)realloc(buf, strlen(_str) + 1 + (strlen(_new) - strlen(_old)) * k);
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

    free(s);

    return 0;
}
