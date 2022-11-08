/******************************************
 * FileName: my_string.c
 * Brief: My simple C string library implementation.
 *        Because the <string.h> is too difficult to use, so I wrote one myself.
 *        Only for C language, so it is named `string`.
 * Author: 青羽
 * Blog: https://chen-qingyu.github.io/
 * CreateDate: 2022.11.03
 ******************************************/

#include "my_string.h"

#include <stdio.h>
#include <stdlib.h>

/*******************************
 * Type definition.
 *******************************/

// String structure definition.
struct st_string
{
    // Number of chars.
    int size;

    // Available capacity.
    int capacity;

    // Pointer to the data.
    char *data;
};

// String initial capacity.
#define INIT_CAPACITY 8

/*******************************
 * Helper function declaration.
 *******************************/

// Check whether the index is valid (begin <= pos < end).
static inline void _check_bounds(int pos, int begin, int end);

// Check whether the pointer is a non-null pointer.
static inline void _check_pointer(void *pointer);

// Use the KMP algorithm to find the position of the pattern.
static inline int _find_pattern(const char *str, const char *pattern, int n, int m);

// Calculate the length of null-terminated byte string (exclude '\0').
static inline int _length(const char *chars);

// Copy a string range.
static inline void _copy_range(string *dst, const string *src, int begin, int end);

/*******************************
 * Interface functions definition.
 *******************************/

string *str_create(void)
{
    string *str = (string *)malloc(sizeof(string));
    _check_pointer(str);
    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    _check_pointer(str->data);
    str->data[0] = '\0';

    return str;
}

string *str_init(const char *chars)
{
    string *str = (string *)malloc(sizeof(string));
    _check_pointer(str);
    str->size = _length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    _check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';

    return str;
}

string *str_copy(const string *str)
{
    string *copy = (string *)malloc(sizeof(string));
    _check_pointer(copy);
    copy->size = str->size;
    copy->capacity = str->capacity;
    copy->data = (char *)malloc(sizeof(char) * copy->capacity);
    _check_pointer(copy->data);
    for (int i = 0; i < copy->size; i++)
    {
        copy->data[i] = str->data[i];
    }
    copy->data[copy->size] = '\0';

    return copy;
}

string *str_move(string *str)
{
    string *move = (string *)malloc(sizeof(string));
    _check_pointer(move);
    move->size = str->size;
    move->capacity = str->capacity;
    move->data = str->data;

    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    _check_pointer(str->data);
    str->data[0] = '\0';

    return move;
}

void str_destroy(string *str)
{
    if (str != NULL)
    {
        free(str->data);
        free(str);
    }
}

void str_copy_assign(string *lhs, const string *rhs)
{
    free(lhs->data);

    lhs->size = rhs->size;
    lhs->capacity = rhs->capacity;
    lhs->data = (char *)malloc(sizeof(char) * lhs->capacity);
    _check_pointer(lhs->data);
    for (int i = 0; i < lhs->size; i++)
    {
        lhs->data[i] = rhs->data[i];
    }
    lhs->data[lhs->size] = '\0';
}

void str_move_assign(string *lhs, string *rhs)
{
    free(lhs->data);

    lhs->size = rhs->size;
    lhs->capacity = rhs->capacity;
    lhs->data = rhs->data;

    rhs->size = 0;
    rhs->capacity = INIT_CAPACITY;
    rhs->data = (char *)malloc(sizeof(char) * rhs->capacity);
    _check_pointer(rhs->data);
    rhs->data[0] = '\0';
}

char *str_get(const string *str)
{
    char *chars = (char *)malloc(sizeof(str->size) + 1);
    _check_pointer(chars);
    for (int i = 0; i < str->size; ++i)
    {
        chars[i] = str->data[i];
    }
    chars[str->size] = '\0';
    return chars;
}

void str_set(string *str, const char *chars)
{
    free(str->data);

    str->size = _length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    _check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';
}

void str_print(const string *str)
{
    printf("%s\n", str->data);
}

int str_size(const string *str)
{
    return str->size;
}

bool str_is_empty(const string *str)
{
    return str->size == 0;
}

char str_at(const string *str, int i)
{
    _check_bounds(i, 0, str->size);

    return str->data[i];
}

bool str_equal(const string *str1, const string *str2)
{
    if (str1->size != str2->size)
    {
        return false;
    }

    for (int i = 0; i < str1->size; ++i)
    {
        if (str1->data[i] != str2->data[i])
        {
            return false;
        }
    }

    return true;
}

enum order str_compare(const string *str1, const string *str2)
{
    int diff = 0;
    for (int i = 0; i < str1->size && i < str2->size && diff == 0; i++)
    {
        diff = str1->data[i] - str2->data[i];
    }

    if (diff > 0)
    {
        return GT;
    }
    else if (diff < 0)
    {
        return LT;
    }
    else // diff == 0
    {
        if (str1->size > str2->size)
        {
            return GT;
        }
        else if (str1->size < str2->size)
        {
            return LT;
        }
        else // str1->size == str2->size
        {
            return EQ;
        }
    }
}

int str_find(const string *str, const string *pattern)
{
    const char *_str = str->data;
    const char *_pattern = pattern->data;
    int n = str_size(str);
    int m = str_size(pattern);

    return _find_pattern(_str, _pattern, n, m);
}

string **str_split(const string *str, const string *sep)
{
    if (sep->size == 0)
    {
        fprintf(stderr, "ERROR: Empty separator.\n");
        exit(EXIT_FAILURE);
    }

    string **str_arr = (string **)malloc(sizeof(string *) * (str->size + 1));
    _check_pointer(str_arr);
    int count = 0;

    int pos_begin = 0;
    int pos_sep = 0;
    while ((pos_sep = _find_pattern(str->data + pos_begin, sep->data, str->size - pos_begin, sep->size)) != STR_NOT_FOUND)
    {
        string *tmp = str_create();
        _copy_range(tmp, str, pos_begin, pos_begin + pos_sep);
        str_arr[count++] = tmp;
        pos_begin += pos_sep + sep->size;
    }
    if (pos_begin != str->size)
    {
        string *tmp = str_create();
        _copy_range(tmp, str, pos_begin, str->size);
        str_arr[count++] = tmp;
    }
    str_arr[count] = NULL;

    // shrink to fit
    str_arr = (string **)realloc(str_arr, sizeof(string *) * (count + 1)); // count + 1 <= str->size + 1, safe

    return str_arr;
}

void str_destroy_array(string **str_arr)
{
    if (str_arr)
    {
        for (int i = 0; str_arr[i] != NULL; ++i)
        {
            str_destroy(str_arr[i]);
        }
        free(str_arr);
    }
}

double str_to_decimal(const string *str)
{
    // TODO
    return 0;
}

long long str_to_integer(const string *str, int base)
{
    // TODO
    return 0;
}

void str_lower(string *str)
{
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = (str->data[i] >= 'A' && str->data[i] <= 'Z' ? str->data[i] + ('a' - 'A') : str->data[i]);
    }
}

void str_upper(string *str)
{
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = (str->data[i] >= 'a' && str->data[i] <= 'z' ? str->data[i] - ('a' - 'A') : str->data[i]);
    }
}

void str_append(string *str, const string *new_str)
{
    if (str->size + new_str->size >= str->capacity) // need to expand capacity
    {
        while (str->size + new_str->size >= str->capacity)
        {
            str->capacity *= 2;
        }
        char *tmp = (char *)malloc(sizeof(char) * str->capacity);
        _check_pointer(tmp);
        for (int i = 0; i < str->size; i++)
        {
            tmp[i] = str->data[i];
        }
        free(str->data);
        str->data = tmp;
    }

    for (int i = 0; i < new_str->size; i++)
    {
        str->data[str->size + i] = new_str->data[i];
    }
    str->size += new_str->size;
    str->data[str->size] = '\0';
}

void str_erase(string *str, int begin, int end)
{
    begin = (begin < 0 ? 0 : begin);
    end = (end > str->size ? str->size : end);

    for (int i = end; i < str->size; i++)
    {
        str->data[i - (end - begin)] = str->data[i];
    }
    str->size -= (end - begin);
    str->data[str->size] = '\0';
}

void str_reverse(string *str)
{
    for (int i = 0, j = str->size - 1; i < j; ++i, --j)
    {
        char tmp = str->data[i];
        str->data[i] = str->data[j];
        str->data[j] = tmp;
    }
}

void str_replace_char(string *str, const char old_char, const char new_char)
{
    for (int i = 0; i < str->size; ++i)
    {
        if (str->data[i] == old_char)
        {
            str->data[i] = new_char;
        }
    }
}

void str_replace(string *str, const string *old_str, const string *new_str)
{
    string *buffer = str_create();
    string *tmp = str_create();

    int offset = 0;
    int index = 0;
    while ((index = _find_pattern(str->data + offset, old_str->data, str->size - offset, old_str->size)) != STR_NOT_FOUND)
    {
        index += offset;
        _copy_range(tmp, str, offset, index);
        str_append(buffer, tmp);
        str_append(buffer, new_str);
        offset = index + old_str->size;
    }
    if (offset != str->size)
    {
        _copy_range(tmp, str, offset, str->size);
        str_append(buffer, tmp);
    }
    str_destroy(tmp);

    free(str->data);
    str->data = buffer->data;
    str->size = buffer->size;
    str->capacity = buffer->capacity;
    free(buffer);
}

void str_strip(string *str)
{
    int i = 0;
    while (i < str->size && str->data[i] <= 0x20)
    {
        ++i;
    }
    str_erase(str, 0, i);
    i = str->size - 1;
    while (i >= 0 && str->data[i] <= 0x20)
    {
        --i;
    }
    str_erase(str, i + 1, str->size);
}

void str_swap(string *str1, string *str2)
{
    int tmp_size = str1->size;
    str1->size = str2->size;
    str2->size = tmp_size;

    int tmp_capa = str1->capacity;
    str1->capacity = str2->capacity;
    str2->capacity = tmp_capa;

    char *tmp_data = str1->data;
    str1->data = str2->data;
    str2->data = tmp_data;
}

void str_clear(string *str)
{
    str_set(str, "");
}

/*******************************
 * Helper function definition.
 *******************************/

static inline void _check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out of range.\n");
        exit(EXIT_FAILURE);
    }
}

static inline void _check_pointer(void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static inline int _find_pattern(const char *str, const char *pattern, int n, int m)
{
    if (n < m)
    {
        return STR_NOT_FOUND;
    }

    if (m == 0) // "" is in any string at index 0.
    {
        return 0;
    }

    int *match = (int *)malloc(sizeof(int) * m);
    _check_pointer(match);
    match[0] = STR_NOT_FOUND;

    for (int j = 1; j < m; j++)
    {
        int i = match[j - 1];
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
            match[j] = STR_NOT_FOUND;
        }
    }

    int s = 0;
    int p = 0;
    while (s < n && p < m)
    {
        if (str[s] == pattern[p])
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

    return (p == m) ? (s - m) : STR_NOT_FOUND;
}

static inline int _length(const char *chars)
{
    int len = 0;
    while (*chars != '\0')
    {
        chars++;
        len++;
    }
    return len;
}

static inline void _copy_range(string *dst, const string *src, int begin, int end)
{
    _check_bounds(begin, 0, src->size);
    _check_bounds(end, 0, src->size + 1);

    free(dst->data);

    dst->size = end - begin;
    dst->capacity = dst->size + 1; // '\0'
    dst->data = (char *)malloc(sizeof(char) * dst->capacity);
    _check_pointer(dst->data);
    for (int i = 0; i < dst->size; i++)
    {
        dst->data[i] = src->data[begin + i];
    }
    dst->data[dst->size] = '\0';
}
