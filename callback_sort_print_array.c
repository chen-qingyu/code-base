#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
custom struct
*/

struct Person
{
    char* name;
    int age;
};

/*
callback print funtions
*/

void print_array(void* arr, int ele_size, int len, void (*print)(const void*))
{
    char* p = arr;
    for (int i = 0; i < len; i++)
    {
        char* ele_addr = p + ele_size * i;
        print(ele_addr);
    }
}

void print_int(const void* data)
{
    const int* p = data;
    printf("Int: %d\n", *p);
}

void print_double(const void* data)
{
    const double* p = data;
    printf("Double: %.2lf\n", *p);
}

void print_person(const void* data)
{
    const struct Person* p = data;
    printf("Person(name: %s\tage: %d)\n", p->name, p->age);
}

/*
callback sort funtions
*/

void sort_array(void* arr, int ele_size, int len, int (*cmp)(const void*, const void*))
{
    char* temp = malloc(ele_size);
    for (int i = 0; i < len - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < len - i - 1; j++)
        {
            char* ele_addr = (char*)arr + ele_size * j;
            char* next_ele_addr = (char*)arr + ele_size * (j + 1);
            if (cmp(ele_addr, next_ele_addr))
            {
                memcpy(temp, next_ele_addr, ele_size);
                memcpy(next_ele_addr, ele_addr, ele_size);
                memcpy(ele_addr, temp, ele_size);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
    free(temp);
}

int cmp_int(const void* a, const void* b)
{
    return *(int*)a < *(int*)b; // 降序排列
}

int cmp_double(const void* a, const void* b)
{
    return *(double*)a < *(double*)b; // 降序排列
}

int cmp_person_age(const void* a, const void* b)
{
    const struct Person* p1 = a;
    const struct Person* p2 = b;
    return p1->age > p2->age; // 升序排列
}

int cmp_person_name(const void* a, const void* b)
{
    const struct Person* p1 = a;
    const struct Person* p2 = b;
    return strcmp(p1->name, p2->name) > 0; // 升序排列
}

/*
test
*/

int main(void)
{
    int arr_int[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 0, 1, 2, 3, 4, 5};
    int len_arr_int = sizeof(arr_int) / sizeof(int);

    double arr_double[] = {1.1, 1.2, 1.3, 0.1, 0.2, 0.3};
    int len_arr_double = sizeof(arr_double) / sizeof(double);

    struct Person arr_person[] = {
        {"Alice", 18},
        {"Sakura", 19},
        {"Homura", 20},
        {"Mei", 17},
        {"Yuzu", 18},
    };
    int len_arr_person = sizeof(arr_person) / sizeof(struct Person);

    printf("\nSort integers in descending order:\n");
    sort_array(arr_int, sizeof(int), len_arr_int, cmp_int);
    print_array(arr_int, sizeof(int), len_arr_int, print_int);

    printf("\nSort doubles in descending order:\n");
    sort_array(arr_double, sizeof(double), len_arr_double, cmp_double);
    print_array(arr_double, sizeof(double), len_arr_double, print_double);

    printf("\nSort persons by name in ascending order:\n");
    sort_array(arr_person, sizeof(struct Person), len_arr_person, cmp_person_name);
    print_array(arr_person, sizeof(struct Person), len_arr_person, print_person);

    printf("\nSort persons by age in ascending order:\n");
    sort_array(arr_person, sizeof(struct Person), len_arr_person, cmp_person_age);
    print_array(arr_person, sizeof(struct Person), len_arr_person, print_person);

    return 0;
}
