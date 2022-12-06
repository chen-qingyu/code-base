/**
 * @file String.c
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief My simple C string library implementation.
 *        Because the <string.h> is too crude to use, so I wrote one myself.
 * @version 1.0
 * @date 2022.11.03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "String.h"

#include <math.h>   // pow
#include <stdio.h>  // fprintf
#include <stdlib.h> // malloc realloc free exit

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
    char* data;
};

// String initial capacity.
#define INIT_CAPACITY 8

// Used for FSM
enum state
{
    S_BEGIN_BLANK = 1 << 0,        // begin blank character
    S_SIGN = 1 << 1,               // positive or negative sign
    S_INT_PART = 1 << 2,           // integer part
    S_DEC_POINT_HAS_LEFT = 1 << 3, // decimal point has left digit
    S_DEC_POINT_NOT_LEFT = 1 << 4, // decimal point doesn't have left digit
    S_DEC_PART = 1 << 5,           // decimal part
    S_EXP = 1 << 6,                // scientific notation identifier
    S_EXP_SIGN = 1 << 7,           // positive or negative sign of exponent part
    S_EXP_PART = 1 << 8,           // exponent part
    S_END_BLANK = 1 << 9,          // end blank character
    S_OTHER = 1 << 10,             // other
};

// Used for FSM
enum event
{
    E_BLANK = 1 << 11,     // blank character: '\n', '\r', '\t', ' '
    E_SIGN = 1 << 12,      // positive or negative sign: '+', '-'
    E_NUMBER = 1 << 13,    // number: '[0-9a-zA-Z]'
    E_DEC_POINT = 1 << 14, // decimal point: '.'
    E_EXP = 1 << 15,       // scientific notation identifier: 'e', 'E'
    E_OTHER = 1 << 16,     // other
};

/*******************************
 * Helper function declaration.
 *******************************/

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end);

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer);

// Use the KMP algorithm to find the position of the pattern.
static inline int find_pattern(const char* str, const char* pattern, int n, int m);

// Calculate the length of null-terminated byte string (exclude '\0').
static inline int length(const char* chars);

// Copy a string range.
static inline void copy_range(string_t* dst, const string_t* src, int begin, int end);

// Check if the string represents infinity or nan. Return [+-]INFINITY or NAN if the string represents infinity or nan, zero otherwise.
static inline double check_infinity_nan(const string_t* str);

// Try to transform a character to an integer based on 2-36 base.
static inline int char_to_integer(char digit, int base);

// Try to transform a character to an event.
static inline enum event get_event(char ch, int base);

/*******************************
 * Interface functions definition.
 *******************************/

string_t* String_Create(void)
{
    string_t* str = (string_t*)malloc(sizeof(string_t));
    check_pointer(str);
    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    str->data[0] = '\0';

    return str;
}

string_t* String_From(const char* chars)
{
    string_t* str = (string_t*)malloc(sizeof(string_t));
    check_pointer(str);
    str->size = length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';

    return str;
}

string_t* String_Copy(const string_t* str)
{
    string_t* copy = (string_t*)malloc(sizeof(string_t));
    check_pointer(copy);
    copy->size = str->size;
    copy->capacity = str->capacity;
    copy->data = (char*)malloc(sizeof(char) * copy->capacity);
    check_pointer(copy->data);
    for (int i = 0; i < copy->size; i++)
    {
        copy->data[i] = str->data[i];
    }
    copy->data[copy->size] = '\0';

    return copy;
}

string_t* String_Move(string_t* str)
{
    string_t* move = (string_t*)malloc(sizeof(string_t));
    check_pointer(move);
    move->size = str->size;
    move->capacity = str->capacity;
    move->data = str->data;

    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    str->data[0] = '\0';

    return move;
}

void String_Destroy(string_t* str)
{
    if (str != NULL)
    {
        free(str->data);
        free(str);
    }
}

void String_CopyAssign(string_t* lhs, const string_t* rhs)
{
    free(lhs->data);

    lhs->size = rhs->size;
    lhs->capacity = rhs->capacity;
    lhs->data = (char*)malloc(sizeof(char) * lhs->capacity);
    check_pointer(lhs->data);
    for (int i = 0; i < lhs->size; i++)
    {
        lhs->data[i] = rhs->data[i];
    }
    lhs->data[lhs->size] = '\0';
}

void String_MoveAssign(string_t* lhs, string_t* rhs)
{
    free(lhs->data);

    lhs->size = rhs->size;
    lhs->capacity = rhs->capacity;
    lhs->data = rhs->data;

    rhs->size = 0;
    rhs->capacity = INIT_CAPACITY;
    rhs->data = (char*)malloc(sizeof(char) * rhs->capacity);
    check_pointer(rhs->data);
    rhs->data[0] = '\0';
}

char* String_Get(const string_t* str)
{
    char* chars = (char*)malloc(sizeof(str->size) + 1);
    check_pointer(chars);
    for (int i = 0; i < str->size; ++i)
    {
        chars[i] = str->data[i];
    }
    chars[str->size] = '\0';
    return chars;
}

void String_Set(string_t* str, const char* chars)
{
    free(str->data);

    str->size = length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';
}

void String_Print(const string_t* str)
{
    printf("%s\n", str->data);
}

int String_Size(const string_t* str)
{
    return str->size;
}

bool String_IsEmpty(const string_t* str)
{
    return str->size == 0;
}

char String_At(const string_t* str, int i)
{
    check_bounds(i, 0, str->size);

    return str->data[i];
}

bool String_Equal(const string_t* str1, const string_t* str2)
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

enum order String_Compare(const string_t* str1, const string_t* str2)
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

int String_Find(const string_t* str, const string_t* pattern)
{
    const char* _str = str->data;
    const char* _pattern = pattern->data;
    int n = String_Size(str);
    int m = String_Size(pattern);

    return find_pattern(_str, _pattern, n, m);
}

string_t** String_Split(const string_t* str, const string_t* sep)
{
    if (sep->size == 0)
    {
        fprintf(stderr, "ERROR: Empty separator.\n");
        exit(EXIT_FAILURE);
    }

    string_t** str_arr = (string_t**)malloc(sizeof(string_t*) * (str->size + 1));
    check_pointer(str_arr);
    int count = 0;

    int pos_begin = 0;
    int pos_sep = 0;
    while ((pos_sep = find_pattern(str->data + pos_begin, sep->data, str->size - pos_begin, sep->size)) != STR_NOT_FOUND)
    {
        string_t* tmp = String_Create();
        copy_range(tmp, str, pos_begin, pos_begin + pos_sep);
        str_arr[count++] = tmp;
        pos_begin += pos_sep + sep->size;
    }
    if (pos_begin != str->size)
    {
        string_t* tmp = String_Create();
        copy_range(tmp, str, pos_begin, str->size);
        str_arr[count++] = tmp;
    }
    str_arr[count] = NULL;

    // shrink to fit
    str_arr = (string_t**)realloc(str_arr, sizeof(string_t*) * (count + 1)); // count + 1 <= str->size + 1, safe

    return str_arr;
}

void String_DestroyArray(string_t** str_arr)
{
    if (str_arr)
    {
        for (int i = 0; str_arr[i] != NULL; ++i)
        {
            String_Destroy(str_arr[i]);
        }
        free(str_arr);
    }
}

double String_ToDecimal(const string_t* str)
{
    // check infinity or nan
    double inf_nan = check_infinity_nan(str);
    if (inf_nan != 0)
    {
        return inf_nan;
    }

    double sign = 1; // default '+'
    double decimal_part = 0;
    int decimal_cnt = 0;
    double exp_sign = 1; // default '+'
    int exp_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < str->size; ++i)
    {
        enum event ev = get_event(str->data[i], 10);
        switch (st | ev)
        {
            case S_BEGIN_BLANK | E_BLANK:
                st = S_BEGIN_BLANK;
                break;

            case S_BEGIN_BLANK | E_SIGN:
                sign = (str->data[i] == '+') ? 1 : -1;
                st = S_SIGN;
                break;

            case S_BEGIN_BLANK | E_DEC_POINT:
            case S_SIGN | E_DEC_POINT:
                st = S_DEC_POINT_NOT_LEFT;
                break;

            case S_BEGIN_BLANK | E_NUMBER:
            case S_SIGN | E_NUMBER:
            case S_INT_PART | E_NUMBER:
                decimal_part = decimal_part * 10 + char_to_integer(str->data[i], 10);
                st = S_INT_PART;
                break;

            case S_INT_PART | E_DEC_POINT:
                st = S_DEC_POINT_HAS_LEFT;
                break;

            case S_DEC_POINT_NOT_LEFT | E_NUMBER:
            case S_DEC_PART | E_NUMBER:
            case S_DEC_POINT_HAS_LEFT | E_NUMBER:
                decimal_part = decimal_part * 10 + char_to_integer(str->data[i], 10);
                decimal_cnt++;
                st = S_DEC_PART;
                break;

            case S_INT_PART | E_EXP:
            case S_DEC_POINT_HAS_LEFT | E_EXP:
            case S_DEC_PART | E_EXP:
                st = S_EXP;
                break;

            case S_EXP | E_SIGN:
                exp_sign = (str->data[i] == '+') ? 1 : -1;
                st = S_EXP_SIGN;
                break;

            case S_EXP | E_NUMBER:
            case S_EXP_SIGN | E_NUMBER:
            case S_EXP_PART | E_NUMBER:
                exp_part = exp_part * 10 + char_to_integer(str->data[i], 10);
                st = S_EXP_PART;
                break;

            case S_INT_PART | E_BLANK:
            case S_DEC_POINT_HAS_LEFT | E_BLANK:
            case S_DEC_PART | E_BLANK:
            case S_EXP_PART | E_BLANK:
            case S_END_BLANK | E_BLANK:
                st = S_END_BLANK;
                break;

            default:
                st = S_OTHER;
                i = str->size; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_DEC_POINT_HAS_LEFT && st != S_DEC_PART && st != S_EXP_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for str_to_decimal(): '%s'\n", str->data);
        exit(EXIT_FAILURE);
    }

    return sign * ((decimal_part / pow(10, decimal_cnt)) * pow(10, exp_sign * exp_part));
}

long long String_ToInteger(const string_t* str, int base)
{
    // check base
    if (base < 2 || base > 36)
    {
        fprintf(stderr, "ERROR: Invalid base for str_to_integer(): %d\n", base);
        exit(EXIT_FAILURE);
    }

    long long sign = 1; // default '+'
    long long integer_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < str->size; ++i)
    {
        enum event ev = get_event(str->data[i], base);
        switch (st | ev)
        {
            case S_BEGIN_BLANK | E_BLANK:
                st = S_BEGIN_BLANK;
                break;

            case S_BEGIN_BLANK | E_SIGN:
                sign = (str->data[i] == '+') ? 1 : -1;
                st = S_SIGN;
                break;

            case S_BEGIN_BLANK | E_NUMBER:
            case S_SIGN | E_NUMBER:
            case S_INT_PART | E_NUMBER:
                integer_part = integer_part * base + char_to_integer(str->data[i], base);
                st = S_INT_PART;
                break;

            case S_INT_PART | E_BLANK:
            case S_END_BLANK | E_BLANK:
                st = S_END_BLANK;
                break;

            default:
                st = S_OTHER;
                i = str->size; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for str_to_integer() with base %d: '%s'\n", base, str->data);
        exit(EXIT_FAILURE);
    }

    return sign * integer_part;
}

void String_Lower(string_t* str)
{
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = (str->data[i] >= 'A' && str->data[i] <= 'Z' ? str->data[i] + ('a' - 'A') : str->data[i]);
    }
}

void String_Upper(string_t* str)
{
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = (str->data[i] >= 'a' && str->data[i] <= 'z' ? str->data[i] - ('a' - 'A') : str->data[i]);
    }
}

void String_Append(string_t* str, const string_t* new_str)
{
    if (str->size + new_str->size >= str->capacity) // need to expand capacity
    {
        while (str->size + new_str->size >= str->capacity)
        {
            str->capacity *= 2;
        }
        char* tmp = (char*)malloc(sizeof(char) * str->capacity);
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

void String_Erase(string_t* str, int begin, int end)
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

void String_Reverse(string_t* str)
{
    for (int i = 0, j = str->size - 1; i < j; ++i, --j)
    {
        char tmp = str->data[i];
        str->data[i] = str->data[j];
        str->data[j] = tmp;
    }
}

void String_ReplaceChar(string_t* str, const char old_char, const char new_char)
{
    for (int i = 0; i < str->size; ++i)
    {
        if (str->data[i] == old_char)
        {
            str->data[i] = new_char;
        }
    }
}

void String_Replace(string_t* str, const string_t* old_str, const string_t* new_str)
{
    string_t* buffer = String_Create();
    string_t* tmp = String_Create();

    int offset = 0;
    int index = 0;
    while ((index = find_pattern(str->data + offset, old_str->data, str->size - offset, old_str->size)) != STR_NOT_FOUND)
    {
        index += offset;
        copy_range(tmp, str, offset, index);
        String_Append(buffer, tmp);
        String_Append(buffer, new_str);
        offset = index + old_str->size;
    }
    if (offset != str->size)
    {
        copy_range(tmp, str, offset, str->size);
        String_Append(buffer, tmp);
    }
    String_Destroy(tmp);

    free(str->data);
    str->data = buffer->data;
    str->size = buffer->size;
    str->capacity = buffer->capacity;
    free(buffer);
}

void String_Strip(string_t* str)
{
    int i = 0;
    while (i < str->size && str->data[i] <= 0x20)
    {
        ++i;
    }
    String_Erase(str, 0, i);
    i = str->size - 1;
    while (i >= 0 && str->data[i] <= 0x20)
    {
        --i;
    }
    String_Erase(str, i + 1, str->size);
}

void String_Swap(string_t* str1, string_t* str2)
{
    int tmp_size = str1->size;
    str1->size = str2->size;
    str2->size = tmp_size;

    int tmp_capa = str1->capacity;
    str1->capacity = str2->capacity;
    str2->capacity = tmp_capa;

    char* tmp_data = str1->data;
    str1->data = str2->data;
    str2->data = tmp_data;
}

void String_Clear(string_t* str)
{
    String_Set(str, "");
}

/*******************************
 * Helper function definition.
 *******************************/

static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out of range: %d not in [%d, %d)\n", pos, begin, end);
        exit(EXIT_FAILURE);
    }
}

static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static inline int find_pattern(const char* str, const char* pattern, int n, int m)
{
    if (n < m)
    {
        return STR_NOT_FOUND;
    }

    if (m == 0) // "" is in any string at index 0.
    {
        return 0;
    }

    int* match = (int*)malloc(sizeof(int) * m);
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

static inline int length(const char* chars)
{
    int len = 0;
    while (*chars != '\0')
    {
        chars++;
        len++;
    }
    return len;
}

static inline void copy_range(string_t* dst, const string_t* src, int begin, int end)
{
    check_bounds(begin, 0, src->size);
    check_bounds(end, 0, src->size + 1);

    free(dst->data);

    dst->size = end - begin;
    dst->capacity = dst->size + 1; // '\0'
    dst->data = (char*)malloc(sizeof(char) * dst->capacity);
    check_pointer(dst->data);
    for (int i = 0; i < dst->size; i++)
    {
        dst->data[i] = src->data[begin + i];
    }
    dst->data[dst->size] = '\0';
}

static inline double check_infinity_nan(const string_t* str)
{
    string_t* inf_nan = String_Create();
    static const char* pos_infs[12] = {"inf", "INF", "Inf", "+inf", "+INF", "+Inf", "infinity", "INFINITY", "Infinity", "+infinity", "+INFINITY", "+Infinity"};
    static const char* neg_infs[6] = {"-inf", "-INF", "-Inf", "-infinity", "-INFINITY", "-Infinity"};
    static const char* nans[9] = {"nan", "NaN", "NAN", "+nan", "+NaN", "+NAN", "-nan", "-NaN", "-NAN"};
    for (int i = 0; i < 12; ++i)
    {
        String_Set(inf_nan, pos_infs[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return INFINITY;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        String_Set(inf_nan, neg_infs[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return -INFINITY;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        String_Set(inf_nan, nans[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return NAN;
        }
    }
    String_Destroy(inf_nan);
    return 0; // not infinity or nan
}

static inline int char_to_integer(char digit, int base) // 2 <= base <= 36
{
    static const char* upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char* lower_digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < base; ++i)
    {
        if (digit == upper_digits[i] || digit == lower_digits[i])
        {
            return i;
        }
    }
    return -1; // not an integer
}

static inline enum event get_event(char ch, int base)
{
    if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
    {
        return E_BLANK;
    }
    else if (char_to_integer(ch, base) != -1)
    {
        return E_NUMBER;
    }
    else if (ch == '-' || ch == '+')
    {
        return E_SIGN;
    }
    else if (ch == '.')
    {
        return E_DEC_POINT;
    }
    else if (ch == 'e' || ch == 'E')
    {
        return E_EXP;
    }
    return E_OTHER;
}
