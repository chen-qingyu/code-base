#include "my_string.h"

#include <assert.h>
#include <math.h>

int main()
{
    // str_create() str_size() str_is_empty() str_set()

    string *s1 = str_create();
    assert(str_size(s1) == 0);
    assert(str_is_empty(s1) == true);

    str_set(s1, "Hello");
    assert(str_size(s1) == 5);
    assert(str_is_empty(s1) == false);

    str_set(s1, "Hello World!");
    assert(str_size(s1) == 12);
    assert(str_is_empty(s1) == false);

    // str_equal() str_at()

    string *s2 = str_create();
    assert(str_equal(s1, s2) == false);
    str_set(s2, "Hello World!");
    assert(str_equal(s1, s2) == true);

    assert(str_at(s2, 0) == 'H');
    assert(str_at(s2, 5) == ' ');
    assert(str_at(s2, 11) == '!');

    // str_reverse()

    string *s3 = str_create();
    string *s4 = str_create();
    str_reverse(s3);
    assert(str_equal(s3, s4) == true);

    str_set(s3, "12345");
    str_set(s4, "54321");
    str_reverse(s3);
    assert(str_equal(s3, s4) == true);

    // str_replace_char()

    str_set(s3, "hahaha");
    str_set(s4, "lalala");
    str_replace_char(s3, 'h', 'l');
    assert(str_equal(s3, s4) == true);

    // str_lower() str_upper()

    str_set(s3, "hahaha");
    str_set(s4, "HAHAHA");
    str_lower(s4);
    assert(str_equal(s3, s4) == true);
    str_upper(s3);
    assert(str_equal(s3, s4) == false);
    str_upper(s4);
    assert(str_equal(s3, s4) == true);

    // str_copy()

    string *s5 = str_copy(s4);
    assert(str_equal(s4, s5) == true);

    // str_compare()

    str_set(s2, "ab");
    str_set(s3, "abc");
    str_set(s4, "abc");
    str_set(s5, "abcd");
    assert(str_compare(s2, s3) == LT);
    assert(str_compare(s3, s4) == EQ);
    assert(str_compare(s4, s5) == LT);
    assert(str_compare(s5, s2) == GT);
    str_set(s4, "abd");
    assert(str_compare(s3, s4) == LT);
    str_set(s3, "cbc");
    assert(str_compare(s3, s4) == GT);

    // str_find()

    str_set(s1, "");
    str_set(s2, "a");
    str_set(s3, "g");
    str_set(s4, "cde");
    str_set(s5, "abcdefg");
    assert(str_find(s1, s1) == 0);
    assert(str_find(s5, s1) == 0);
    assert(str_find(s5, s2) == 0);
    assert(str_find(s5, s3) == 6);
    assert(str_find(s5, s4) == 2);
    assert(str_find(s5, s5) == 0);
    str_set(s1, " ");
    assert(str_find(s5, s1) == STR_NOT_FOUND);
    str_set(s1, "ac");
    assert(str_find(s5, s1) == STR_NOT_FOUND);

    // str_append()

    str_set(s1, "");
    str_set(s5, "");
    str_append(s1, s5);
    assert(str_equal(s1, s5) == true);
    str_append(s1, s2);
    assert(str_equal(s1, s2) == true);
    str_append(s1, s3);
    str_append(s1, s4);
    str_set(s5, "agcde");
    assert(str_equal(s1, s5) == true);

    // str_erase()

    str_set(s1, "abcdefg");
    str_erase(s1, 0, 1);
    str_set(s2, "bcdefg");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "abcdefg");
    str_erase(s1, 1, 2);
    str_set(s2, "acdefg");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "abcdefg");
    str_erase(s1, 1, 6);
    str_set(s2, "ag");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "abcdefg");
    str_erase(s1, 0, 7);
    str_set(s2, "");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "abcdefg");
    str_erase(s1, -1, 99);
    str_set(s2, "");
    assert(str_equal(s1, s2) == true);

    // str_replace()

    str_set(s1, "abcdefg");
    str_set(s2, "a");
    str_set(s3, "g");
    str_replace(s1, s2, s3);
    str_set(s4, "gbcdefg");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "abcdefg");
    str_set(s2, "g");
    str_set(s3, "a");
    str_replace(s1, s2, s3);
    str_set(s4, "abcdefa");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "abcdefg");
    str_set(s2, "cde");
    str_set(s3, "~~~");
    str_replace(s1, s2, s3);
    str_set(s4, "ab~~~fg");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "abcdefg");
    str_set(s2, "abcdefg");
    str_set(s3, "");
    str_replace(s1, s2, s3);
    str_set(s4, "");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "abcdefg");
    str_set(s2, "abcdefg");
    str_set(s3, "");
    str_replace(s1, s2, s3);
    str_set(s4, "");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "");
    str_set(s2, "abc");
    str_set(s3, "~~~");
    str_replace(s1, s2, s3);
    str_set(s4, "");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "hahaha");
    str_set(s2, "h");
    str_set(s3, "l");
    str_replace(s1, s2, s3);
    str_set(s4, "lalala");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "hahaha");
    str_set(s2, "a");
    str_set(s3, "ooow~ ");
    str_replace(s1, s2, s3);
    str_set(s4, "hooow~ hooow~ hooow~ ");
    assert(str_equal(s1, s4) == true);

    str_set(s1, "hooow~ hooow~ hooow~ ");
    str_set(s2, "ooo");
    str_set(s3, "o");
    str_replace(s1, s2, s3);
    str_set(s4, "how~ how~ how~ ");
    assert(str_equal(s1, s4) == true);

    // str_split() str_destroy_array()

    string **str_arr = NULL;

    str_set(s1, "this is my code!");
    str_set(s2, " ");
    str_arr = str_split(s1, s2);

    str_set(s3, "this");
    assert(str_equal(str_arr[0], s3) == true);
    str_set(s3, "is");
    assert(str_equal(str_arr[1], s3) == true);
    str_set(s3, "my");
    assert(str_equal(str_arr[2], s3) == true);
    str_set(s3, "code!");
    assert(str_equal(str_arr[3], s3) == true);
    assert(str_arr[4] == NULL);
    str_destroy_array(str_arr);

    str_set(s1, " this is my code! ");
    str_set(s2, " ");
    str_arr = str_split(s1, s2);

    str_set(s3, "");
    assert(str_equal(str_arr[0], s3) == true);
    str_set(s3, "this");
    assert(str_equal(str_arr[1], s3) == true);
    str_set(s3, "is");
    assert(str_equal(str_arr[2], s3) == true);
    str_set(s3, "my");
    assert(str_equal(str_arr[3], s3) == true);
    str_set(s3, "code!");
    assert(str_equal(str_arr[4], s3) == true);
    assert(str_arr[5] == NULL);
    str_destroy_array(str_arr);

    str_set(s1, "aaa");
    str_set(s2, "a");
    str_arr = str_split(s1, s2);

    str_set(s3, "");
    assert(str_arr[3] == NULL);
    for (int i = 0; i < 3; i++)
    {
        assert(str_equal(str_arr[i], s3) == true);
    }
    str_destroy_array(str_arr);

    str_set(s1, "this is my code!");
    str_set(s2, "this is my code!");
    str_arr = str_split(s1, s2);

    str_set(s3, "");
    assert(str_equal(str_arr[0], s3) == true);
    assert(str_arr[1] == NULL);
    str_destroy_array(str_arr);

    str_set(s1, "one, two, three");
    str_set(s2, ", ");
    str_arr = str_split(s1, s2);

    str_set(s3, "one");
    assert(str_equal(str_arr[0], s3) == true);
    str_set(s3, "two");
    assert(str_equal(str_arr[1], s3) == true);
    str_set(s3, "three");
    assert(str_equal(str_arr[2], s3) == true);
    assert(str_arr[3] == NULL);
    str_destroy_array(str_arr);

    // str_strip()

    str_set(s1, "\t\nhello\t\n");
    str_strip(s1);
    str_set(s2, "hello");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "           hello           ");
    str_strip(s1);
    str_set(s2, "hello");
    assert(str_equal(s1, s2) == true);

    str_set(s1, "\n\n\n\n \t\n\b\n   hello  \n\n\t\n \r\b\n\r");
    str_strip(s1);
    str_set(s2, "hello");
    assert(str_equal(s1, s2) == true);

    // str_destroy()

    str_destroy(s1);
    str_destroy(s2);
    str_destroy(s3);
    str_destroy(s4);
    str_destroy(s5);

    printf("Test OK\n");

    return 0;
}

/*
2022.11.04
Test OK, and there is no memory leak:
~~Dr.M~~
~~Dr.M~~ NO ERRORS FOUND:
~~Dr.M~~       0 unique,     0 total unaddressable access(es)
~~Dr.M~~       0 unique,     0 total uninitialized access(es)
~~Dr.M~~       0 unique,     0 total invalid heap argument(s)
~~Dr.M~~       0 unique,     0 total GDI usage error(s)
~~Dr.M~~       0 unique,     0 total handle leak(s)
~~Dr.M~~       0 unique,     0 total warning(s)
~~Dr.M~~       0 unique,     0 total,      0 byte(s) of leak(s)
~~Dr.M~~       0 unique,     0 total,      0 byte(s) of possible leak(s)
*/
