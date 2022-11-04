/******************************************
 * FileName: my_string.h
 * Brief: My simple C string library.
 *        Because the <string.h> is too difficult to use, so I wrote one myself.
 *        Only for C language, so it is named `string`.
 * Author: 青羽
 * Blog: https://chen-qingyu.github.io/
 * CreateDate: 2022.11.03
 ******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*******************************
 * Type definition.
 *******************************/

// Used for string find.
#define STR_NOT_FOUND (-1)

// String structure definition.
typedef struct
{
    // Number of chars.
    int size;

    // Available capacity.
    int capacity;

    // Pointer to the data.
    char *data;
} string;

// Used for string comparison.
typedef enum
{
    // Less Than.
    LT = -1,

    // Equal.
    EQ = 0,

    // Grater Than.
    GT = 1
} order;

/*******************************
 * Interface function declaration.
 *******************************/

/**
 * @brief Creates an empty string. O(1)
 * @param void
 * @return A pointer to the empty string.
*/
string *str_create(void);

/**
 * @brief Destroy a string. O(1)
 * @param str: A pointer to the string to be destroyed.
*/
void str_destroy(string *str);

/**
 * @brief Find the size of the string. O(1)
 * @param str: A pointer to the string.
 * @return The size of the string.
*/
int str_size(const string *str);

/**
 * @brief Determine whether the string is empty. O(1)
 * @param str: A pointer to the string.
 * @return Returns true if the string is empty, false otherwise.
*/
bool str_is_empty(const string *str);

/**
 * @brief Set the contents of the string using null-terminated byte string. O(N)
 * @param str: A pointer to the string to be set.
 * @param chars: A pointer to a null-terminated byte string.
*/
void str_set(string *str, const char *chars);

/**
 * @brief Determines whether the two strings have the same content. O(N)
 * @param str1: A pointer to the first string.
 * @param str2: A pointer to the second string.
 * @return Returns true if the contents of the two strings are the same, false otherwise.
*/
bool str_equal(const string *str1, const string *str2);

/**
 * @brief Take the i-th character of the string. O(1)
 * @param str: A pointer to the string.
 * @param i: Index (0 <= i < str_size(str)).
 * @return The i-th character.
*/
char str_at(const string *str, int i);

/**
 * @brief Inverts the string in place. O(N)
 * @param str: A pointer to the string.
*/
void str_reverse(string *str);

/**
 * @brief Replaces character in the string. O(N)
 * @param str: A pointer to the string.
 * @param old_char: The old character to be replaced.
 * @param new_char: The new character to replace.
*/
void str_replace_char(string *str, const char old_char, const char new_char);

/**
 * @brief Converts the string to lowercase. O(N)
 * @param str: A pointer to the string.
*/
void str_lower(string *str);

/**
 * @brief Converts the string to uppercase. O(N)
 * @param str: A pointer to the string.
*/
void str_upper(string *str);

/**
 * @brief Copy the string. O(N)
 * @param str: A pointer to the string.
 * @return A pointer to the copied string.
*/
string *str_copy(const string *str);

/**
 * @brief Compares two strings lexicographically. O(N)
 * @param str1: A pointer to the first string.
 * @param str2: A pointer to the second string.
 * @return An enumeration value: order{LT, EQ, GT}.
*/
order str_compare(const string *str1, const string *str2);

/**
 * @brief Use the KMP algorithm to find the position of the pattern. O(M + N)
 * @param str: A pointer to the string.
 * @param pattern: A pointer to the pattern string.
 * @return Returns the starting substring index or STR_NOT_FOUND.
*/
int str_find(const string *str, const string *pattern);

/**
 * @brief Append new string to the tail. O(M)
 * @param str: A pointer to the string.
 * @param new_str: A pointer to the new string.
*/
void str_append(string *str, const string *new_str);

/**
 * @brief Erases the contents of a range of string. O(N)
 * @param str: A pointer to the string to be erased.
 * @param begin: Begin range subscript (included).
 * @param end: End range subscript (not included).
*/
void str_erase(string *str, int begin, int end);

/**
 * @brief Replace the string. O(N)
 * @param str: A pointer to the string to be replaced.
 * @param old_str: Old substring.
 * @param new_str: New substring.
*/
void str_replace(string *str, const string *old_str, const string *new_str);

/**
 * @brief Split string with separator. O(N)
 *        Example: str_split("one, two", ", ") => ["one", "two"].
 *        Don't forget use str_destroy_array(return-value).
 * @param str: String to be split.
 * @param sep: Separator string.
 * @return Array of split string pointers.
*/
string **str_split(const string *str, const string *sep);

/**
 * @brief Destroy a string array. For str_split(). O(N)
 * @param str_arr: A pointer to the string array to be destroyed.
*/
void str_destroy_array(string **str_arr);

/**
 * @brief Print the contents of the string. O(N)
 * @param str: A pointer to the string to be printed.
*/
void str_print(const string *str);

/*******************************
 * Helper function declaration.
 *******************************/

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end);

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(void *pointer);

// Use the KMP algorithm to find the position of the pattern.
static inline int find_pattern(const char *str, const char *pattern, int n, int m);

// Calculate the length of null-terminated byte string (exclude '\0').
static inline int length(const char *chars);

// Copy a string range.
static inline void copy_range(string *dst, const string *src, int begin, int end);

/*******************************
 * Interface functions definition.
 *******************************/

string *str_create(void)
{
    string *str = (string *)malloc(sizeof(string));
    check_pointer(str);
    str->size = 0;
    str->capacity = 8;
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    str->data[0] = '\0';

    return str;
}

void str_destroy(string *str)
{
    if (str != NULL)
    {
        free(str->data);
        free(str);
    }
}

int str_size(const string *str)
{
    return str->size;
}

bool str_is_empty(const string *str)
{
    return str->size == 0;
}

void str_set(string *str, const char *chars)
{
    free(str->data);

    str->size = length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char *)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';
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

char str_at(const string *str, int i)
{
    check_bounds(i, 0, str->size);

    return str->data[i];
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

string *str_copy(const string *str)
{
    string *copy = (string *)malloc(sizeof(string));
    check_pointer(copy);
    copy->size = str->size;
    copy->capacity = str->capacity;
    copy->data = (char *)malloc(sizeof(char) * copy->capacity);
    check_pointer(copy->data);
    for (int i = 0; i < copy->size; i++)
    {
        copy->data[i] = str->data[i];
    }
    copy->data[copy->size] = '\0';

    return copy;
}

order str_compare(const string *str1, const string *str2)
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

    return find_pattern(_str, _pattern, n, m);
}

void str_append(string *str, const string *new_str)
{
    if (str->size + new_str->size >= str->capacity)
    {
        while (str->size + new_str->size >= str->capacity)
        {
            str->capacity *= 2;
        }
        char *tmp = (char *)malloc(sizeof(char) * str->capacity);
        check_pointer(tmp);
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

void str_replace(string *str, const string *old_str, const string *new_str)
{
    string *buffer = str_create();
    string *tmp = str_create();

    int offset = 0;
    int index = 0;
    while ((index = find_pattern(str->data + offset, old_str->data, str->size - offset, old_str->size)) != STR_NOT_FOUND)
    {
        index += offset;
        copy_range(tmp, str, offset, index);
        str_append(buffer, tmp);
        str_append(buffer, new_str);
        offset = index + old_str->size;
    }
    if (offset != str->size)
    {
        copy_range(tmp, str, offset, str->size);
        str_append(buffer, tmp);
    }
    str_destroy(tmp);

    free(str->data);
    str->data = buffer->data;
    str->size = buffer->size;
    str->capacity = buffer->capacity;
    free(buffer);
}

string **str_split(const string *str, const string *sep)
{
    if (sep->size == 0)
    {
        fprintf(stderr, "ERROR: Empty separator.\n");
        exit(EXIT_FAILURE);
    }

    string **str_arr = (string **)malloc(sizeof(string *) * (str->size + 1));
    check_pointer(str_arr);
    int count = 0;

    int pos_begin = 0;
    int pos_sep = 0;
    while ((pos_sep = find_pattern(str->data + pos_begin, sep->data, str->size - pos_begin, sep->size)) != STR_NOT_FOUND)
    {
        string *tmp = str_create();
        copy_range(tmp, str, pos_begin, pos_begin + pos_sep);
        str_arr[count++] = tmp;
        pos_begin += pos_sep + sep->size;
    }
    if (pos_begin != str->size)
    {
        string *tmp = str_create();
        copy_range(tmp, str, pos_begin, str->size);
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

void str_print(const string *str)
{
    printf("%s\n", str->data);
}

/*******************************
 * Helper function definition.
 *******************************/

static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out of range.\n");
        exit(EXIT_FAILURE);
    }
}

static inline void check_pointer(void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static inline int find_pattern(const char *str, const char *pattern, int n, int m)
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
    check_pointer(match);
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

static inline int length(const char *chars)
{
    int len = 0;
    while (*chars != '\0')
    {
        chars++;
        len++;
    }
    return len;
}

static inline void copy_range(string *dst, const string *src, int begin, int end)
{
    check_bounds(begin, 0, src->size);
    check_bounds(end, 0, src->size + 1);

    free(dst->data);

    dst->size = end - begin;
    dst->capacity = dst->size + 1; // '\0'
    dst->data = (char *)malloc(sizeof(char) * dst->capacity);
    check_pointer(dst->data);
    for (int i = 0; i < dst->size; i++)
    {
        dst->data[i] = src->data[begin + i];
    }
    dst->data[dst->size] = '\0';
}
