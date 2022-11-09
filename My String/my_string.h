/******************************************
 * FileName: my_string.h
 * Brief: My simple C string library.
 *        Because the <string.h> is too difficult to use, so I wrote one myself.
 *        Only for C language, so it is named `string`.
 * Author: 青羽
 * Blog: https://chen-qingyu.github.io/
 * CreateDate: 2022.11.03
 * Functions:
 * - String construction/deconstruction:
 *   - str_create        Create an empty string.
 *   - str_init          Create a string using null-terminated byte string.
 *   - str_copy          Copy constructor.
 *   - str_move          Move constructor.
 *   - str_destroy       Destroy a string.
 * - String assignment:
 *   - str_copy_assign   Copy assignment operation.
 *   - str_move_assign   Move assignment operation.
 * - String getter/setter:
 *   - str_get           Get the copy of the contents of the string.
 *   - str_set           Set the contents of the string using null-terminated byte string.
 * - String examination (will not change the string itself):
 *   - str_print         Print the contents of the string.
 *   - str_size          Find the size of the string.
 *   - str_is_empty      Determine whether the string is empty.
 *   - str_at            Take the i-th character of the string.
 *   - str_equal         Determine whether the two strings have the same contents.
 *   - str_compare       Compare two strings lexicographically.
 *   - str_find          Find the position of the pattern.
 *   - str_split         Split string with separator.
 *   - str_destroy_array Destroy a string array. For str_split().
 *   - str_to_decimal    Convert the string to a double-precision floating-point decimal number.
 *   - str_to_integer    Convert the string to an integer number based on 2-36 base.
 * - String manipulation (will change the string itself):
 *   - str_lower         Convert the string to lowercase.
 *   - str_upper         Convert the string to uppercase.
 *   - str_append        Append new string to the tail.
 *   - str_erase         Erase the contents of a range of string.
 *   - str_reverse       Reverse the string in place.
 *   - str_replace_char  Replace character in the string.
 *   - str_replace       Replace the string.
 *   - str_strip         Remove leading and trailing blank characters of the string.
 *   - str_swap          Swap the contents of two strings.
 *   - str_clear         Clear the contents of the string.
 ******************************************/

#ifndef MY_STRING_H
#define MY_STRING_H

/*******************************
 * Type declaration.
 *******************************/

// For `true` and `false`.
#include <stdbool.h>

// For `HUGE_VAL`, `NAN` and `INFINITY`.
// HUGE_VAL: Indicate the value is too big to be representable.
// NAN: Not a number.
// INFINITY: Positive infinity.
#include <math.h>

// Used for string find.
#define STR_NOT_FOUND (-1)

// String structure declaration.
typedef struct st_string string;

// Used for string comparison.
enum order
{
    // Less Than.
    LT = -1,

    // Equal.
    EQ = 0,

    // Grater Than.
    GT = 1,
};

/*******************************
 * Interface function declaration.
 *******************************/

/**
 * @brief Create an empty string. Constructor. O(1)
 *        Like `string new_str();` in C++.
 *        Example: string *new_str = str_create();
 * @return A pointer to the empty string.
 */
string *str_create(void);

/**
 * @brief Create a string using null-terminated byte string. O(N)
 *        Like `string new_str("hello");` in C++.
 *        Example: string *new_str = str_init("hello");
 * @param chars: A pointer to a null-terminated byte string.
 * @return A pointer to the new string.
 */
string *str_init(const char *chars);

/**
 * @brief Copy constructor. O(N)
 *        Like `string new_str(str);` in C++.
 *        Example: string *new_str = str_copy(str);
 * @param str: A pointer to the string.
 * @return A pointer to the copied string.
 */
string *str_copy(const string *str);

/**
 * @brief Move constructor. O(1)
 *        Like `string new_str(std::move(str));` in C++.
 *        Example: string *new_str = str_move(str); // after moved, `str` is an empty string
 * @param str: A pointer to the string to be moved.
 * @return A pointer to the moved string.
 */
string *str_move(string *str);

/**
 * @brief Destroy a string. O(1)
 *        Like `str.~string();` in C++.
 *        Example: str_destroy(str);
 * @param str: A pointer to the string to be destroyed.
 */
void str_destroy(string *str);

/**
 * @brief Copy assignment operation. O(N)
 *        Like `lhs = rhs;` in C++.
 *        Example: str_copy_assign(lhs, rhs);
 * @param lhs: A pointer to the left hand side string.
 * @param rhs: A pointer to the right hand side string.
 */
void str_copy_assign(string *lhs, const string *rhs);

/**
 * @brief Move assignment operation. O(1)
 *        Like `lhs = std::move(rhs);` in C++.
 *        Example: str_move_assign(lhs, rhs);
 * @param lhs: A pointer to the left hand side string.
 * @param rhs: A pointer to the right hand side string.
 */
void str_move_assign(string *lhs, string *rhs);

/**
 * @brief Get the copy of the contents of the string. O(N)
 *        Example: char *chars = str_get(str);
 * @param str: A pointer to the string.
 * @param chars: A null-terminated byte string.
 */
char *str_get(const string *str);

/**
 * @brief Set the contents of the string using null-terminated byte string. O(N)
 *        Example: str_set(str, "hello");
 * @param str: A pointer to the string to be set.
 * @param chars: A pointer to a null-terminated byte string.
 */
void str_set(string *str, const char *chars);

/**
 * @brief Print the contents of the string. O(N)
 * @param str: A pointer to the string to be printed.
 */
void str_print(const string *str);

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
 * @brief Take the i-th character of the string. O(1)
 * @param str: A pointer to the string.
 * @param i: Index (0 <= i < str_size(str)).
 * @return The i-th character.
 */
char str_at(const string *str, int i);

/**
 * @brief Determine whether the two strings have the same contents. O(N)
 * @param str1: A pointer to the first string.
 * @param str2: A pointer to the second string.
 * @return Returns true if the contents of the two strings are the same, false otherwise.
 */
bool str_equal(const string *str1, const string *str2);

/**
 * @brief Compare two strings lexicographically. O(N)
 * @param str1: A pointer to the first string.
 * @param str2: A pointer to the second string.
 * @return An enumeration value: order{LT, EQ, GT}.
 */
enum order str_compare(const string *str1, const string *str2);

/**
 * @brief Find the position of the pattern. O(N + M)
 * @param str: A pointer to the string.
 * @param pattern: A pointer to the pattern string.
 * @return Returns the starting substring index or STR_NOT_FOUND.
 */
int str_find(const string *str, const string *pattern);

/**
 * @brief Split string with separator. O(N)
 *        Example: string *str = str_init("one, two, three");
 *                 string *sep = str_init(", ");
 *                 string **str_arr = str_split(str, sep); // => ["one", "two", "three", NULL]
 *        Don't forget use str_destroy_array(return-value).
 * @param str: String to be split.
 * @param sep: Separator string.
 * @return A null-terminated array of split string pointers.
 */
string **str_split(const string *str, const string *sep);

/**
 * @brief Destroy a string array. For str_split(). O(N)
 * @param str_arr: A pointer to the string array to be destroyed.
 */
void str_destroy_array(string **str_arr);

/**
 * @brief Convert the string to a double-precision floating-point decimal number. O(N)
 *        If the string is too big to be representable will return `HUGE_VAL`.
 *        If the string represents nan ("[+-]?(nan, NaN, NAN)") will return `NAN`.
 *        If the string represents infinity ("[+-]?(inf, Inf, INF, infinity, Infinity, INFINITY)") will return `INFINITY`.
 *        Example: string *str1 = str_init("233.33");
 *                 double number = str_to_decimal(str1); // => 233.33
 *                 string *str2 = str_init("1e+600");
 *                 double number = str_to_decimal(str2); // => HUGE_VAL
 *                 string *str3 = str_init("nan");
 *                 double number = str_to_decimal(str3); // => NAN
 *                 string *str4 = str_init("inf");
 *                 double number = str_to_decimal(str4); // => INFINITY
 * @param str: String to be parsed.
 * @return A number that can represent the string or HUGE_VAL or NAN or [+-]INFINITY.
 */
double str_to_decimal(const string *str);

/**
 * @brief Convert the string to an integer number based on 2-36 base. O(N)
 *        Numeric character in 36 base: 0, 1, ..., 9, A(10), ..., F(15), G(16), ..., Y(34), Z(35).
 *        Example: string *str1 = str_init("233");
 *                 long long number = str_to_integer(str1, 10); // => 233
 *                 string *str2 = str_init("cafebabe");
 *                 long long number = str_to_integer(str2, 16); // => 3405691582
 *                 string *str3 = str_init("z");
 *                 long long number = str_to_integer(str3, 36); // => 35
 * @param str: String to be parsed.
 * @param base: The base of an integer (2 <= base <= 36).
 * @return An integer number that can represent the string.
 */
long long str_to_integer(const string *str, int base);

/**
 * @brief Convert the string to lowercase. O(N)
 * @param str: A pointer to the string.
 */
void str_lower(string *str);

/**
 * @brief Convert the string to uppercase. O(N)
 * @param str: A pointer to the string.
 */
void str_upper(string *str);

/**
 * @brief Append new string to the tail. O(N)
 * @param str: A pointer to the string.
 * @param new_str: A pointer to the new string.
 */
void str_append(string *str, const string *new_str);

/**
 * @brief Erase the contents of a range of string. O(N)
 * @param str: A pointer to the string to be erased.
 * @param begin: Begin range subscript (included).
 * @param end: End range subscript (not included).
 */
void str_erase(string *str, int begin, int end);

/**
 * @brief Reverse the string in place. O(N)
 * @param str: A pointer to the string.
 */
void str_reverse(string *str);

/**
 * @brief Replace character in the string. O(N)
 * @param str: A pointer to the string.
 * @param old_char: The old character to be replaced.
 * @param new_char: The new character to replace.
 */
void str_replace_char(string *str, const char old_char, const char new_char);

/**
 * @brief Replace the string. O(N)
 * @param str: A pointer to the string to be replaced.
 * @param old_str: Old substring.
 * @param new_str: New substring.
 */
void str_replace(string *str, const string *old_str, const string *new_str);

/**
 * @brief Remove leading and trailing blank characters of the string. O(N)
 * @param str: A pointer to the string.
 */
void str_strip(string *str);

/**
 * @brief Swap the contents of two strings. O(1)
 * @param str1: A pointer to the first string.
 * @param str2: A pointer to the second string.
 */
void str_swap(string *str1, string *str2);

/**
 * @brief Clear the contents of the string. O(1)
 * @param str: A pointer to the string.
 */
void str_clear(string *str);

#endif // MY_STRING_H
