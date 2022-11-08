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
 *   - str_copy          Copy a string.
 *   - str_destroy       Destroy a string.
 * - String getter/setter:
 *   - str_get           Get the copy of the content of the string.
 *   - str_set           Set the content of the string using null-terminated byte string.
 * - String examination (will not change the string itself):
 *   - str_print         Print the contents of the string.
 *   - str_size          Find the size of the string.
 *   - str_is_empty      Determine whether the string is empty.
 *   - str_at            Take the i-th character of the string.
 *   - str_equal         Determine whether the two strings have the same content.
 *   - str_compare       Compare two strings lexicographically.
 *   - str_find          Find the position of the pattern.
 *   - str_split         Split string with separator.
 *   - str_destroy_array Destroy a string array. For str_split().
 * - String manipulation (will change the string itself):
 *   - str_lower         Convert the string to lowercase.
 *   - str_upper         Convert the string to uppercase.
 *   - str_append        Append new string to the tail.
 *   - str_erase         Erase the contents of a range of string.
 *   - str_reverse       Reverse the string in place.
 *   - str_replace_char  Replace character in the string.
 *   - str_replace       Replace the string.
 *   - str_strip         Remove leading and trailing blank characters of the string.
 ******************************************/

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************
 * Type declaration.
 *******************************/

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
    GT = 1
};

/*******************************
 * Interface function declaration.
 *******************************/

/**
 * @brief Create an empty string. O(1)
 * @param void
 * @return A pointer to the empty string.
 */
string *str_create(void);

/**
 * @brief Copy a string. O(N)
 * @param str: A pointer to the string.
 * @return A pointer to the copied string.
 */
string *str_copy(const string *str);

/**
 * @brief Destroy a string. O(1)
 * @param str: A pointer to the string to be destroyed.
 */
void str_destroy(string *str);

/**
 * @brief Get the copy of the content of the string. O(N)
 * @param str: A pointer to the string.
 * @param chars: A null-terminated byte string.
 */
char *str_get(const string *str);

/**
 * @brief Set the content of the string using null-terminated byte string. O(N)
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
 * @brief Determine whether the two strings have the same content. O(N)
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
 *        Example: str_split("one, two, three", ", ") => ["one", "two", "three", NULL].
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

#endif // MY_STRING_H
