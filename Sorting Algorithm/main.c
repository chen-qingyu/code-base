#include "Sort.h"

#define DATA_SIZE 32768

typedef void (*sortFunc_t)(item_t *arr, int n);

int orderCmp(const void *a, const void *b)
{
    return (*(item_t *)a) - (*(item_t *)b);
}

int reverseCmp(const void *a, const void *b)
{
    return (*(item_t *)b) - (*(item_t *)a);
}

struct timeResult
{
    double randomTime;
    double orderTime;
    double reverseTime;
};

struct timeResult time_test(sortFunc_t method)
{
    // 生成数据
    item_t random[DATA_SIZE], order[DATA_SIZE], reverse[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        random[i] = order[i] = reverse[i] = rand();
    }

    qsort(order, DATA_SIZE, sizeof(item_t), orderCmp);
    qsort(reverse, DATA_SIZE, sizeof(item_t), reverseCmp);
    clock_t start, end;
    struct timeResult tr;

    // 随机数据排序
    start = clock();
    method(random, DATA_SIZE);
    end = clock();
    tr.randomTime = (double)(end - start) / CLOCKS_PER_SEC;

    // 顺序数据排序
    start = clock();
    method(order, DATA_SIZE);
    end = clock();
    tr.orderTime = (double)(end - start) / CLOCKS_PER_SEC;

    // 逆序数据排序
    start = clock();
    method(reverse, DATA_SIZE);
    end = clock();
    tr.reverseTime = (double)(end - start) / CLOCKS_PER_SEC;

    return tr;
}

sortFunc_t functions[] = {
    heapSort, insertionSort, mergeSort, quickSort, radixSort, selectionSort, shellSort, bubbleSort
};

const char * funcNames[] = {
    "heap sort", "insertion sort", "merge sort", "quick sort", "radix sort", "selection sort", "shell sort", "bubble sort"
};

void user(void)
{
    printf("Please select a sort algorithm:\n");
    for (int i = 0; i < sizeof(functions) / sizeof(sortFunc_t); ++i)
    {
        printf("  %d: %s\n", i + 1, funcNames[i]);
    }
    int ch;
    scanf("%d", &ch);
    sortFunc_t func = functions[ch - 1];

    item_t arr[SIZE];
    int n = 0;
    printf("Please input the integers and hit `Enter`:\n");
    while (n < SIZE && scanf("%d", &arr[n]))
    {
        n++;
        if (getchar() == '\n')
        {
            break;
        }
    }

    func(arr, n);

    printf("\n");
    printf("The data after %sing is as follows:\n", funcNames[ch - 1]);
    for (int i = 0; i < n; i++)
    {
        printf("%d : %d\n", i + 1, arr[i]);
    }
}

void sort_time_test(void)
{
    printf("SIZE: %d\trandomTime\torderTime\treverseTime (seconds)\n", DATA_SIZE);
    struct timeResult tr;

    for (int i = 0; i < sizeof(functions) / sizeof(sortFunc_t); ++i)
    {
        tr = time_test(functions[i]);
        printf("%s:\t%lf\t%lf\t%lf\n", funcNames[i], tr.randomTime, tr.orderTime, tr.reverseTime);
    }
}

int main(void)
{
    printf("Please select:\n");
    printf("  1. Test mode. (default)\n");
    printf("  2. User mode.\n");

    int ch;
    scanf("%c", &ch);
    switch (ch)
    {
        case '1':
        case '\n':
            sort_time_test();
            break;
        case '2':
            user();
            break;
        default:
            printf("Invalid option.\n");
            break;
    }

    return 0;
}
