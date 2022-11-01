#include "Sort.h"

struct node
{
    item_t key;
    struct node *next;
};
typedef struct node *node_t;

struct headNode
{
    node_t head;
    node_t tail;
};
typedef struct headNode bucket_t[RADIX];

int getDigit(item_t item, int D)
{
    int digit;

    for (int i = 1; i <= D; i++)
    {
        digit = (int)item % RADIX;
        item /= RADIX;
    }
    return digit;
}

void radixSort(item_t arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            fprintf(stderr, "Radix sort can't handle negative numbers yet.\n");
            return;
        }
        if (sizeof(arr[i]) == sizeof(double))
        {
            fprintf(stderr, "Radix sort can't handle float numbers yet.\n");
            return;
        }
    }

    int D, digit;
    bucket_t bucket;
    node_t tmp, p, list = NULL;

    for (int i = 0; i < RADIX; i++)
    {
        bucket[i].head = NULL;
        bucket[i].tail = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        tmp = (node_t)malloc(sizeof(struct node));
        if (tmp == NULL)
        {
            fprintf(stderr, "ERROR: file %s, function %s, line %d : There was not enough memory.\n", __FILE__, __FUNCTION__, __LINE__);
            exit(-2);
        }
        tmp->key = arr[i];
        tmp->next = list;
        list = tmp;
    }

    for (D = 1; D <= MAX_DIGIT; D++)
    {
        p = list;
        while (p)
        {
            digit = getDigit(p->key, D);

            tmp = p;
            p = p->next;
            tmp->next = NULL;

            if (bucket[digit].head == NULL)
            {
                bucket[digit].head = tmp;
                bucket[digit].tail = tmp;
            }
            else
            {
                bucket[digit].tail->next = tmp;
                bucket[digit].tail = tmp;
            }
        }

        list = NULL;

        for (digit = RADIX - 1; digit >= 0; digit--)
        {
            if (bucket[digit].head)
            {
                bucket[digit].tail->next = list;
                list = bucket[digit].head;
                bucket[digit].head = NULL;
                bucket[digit].tail = NULL;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        tmp = list;
        list = list->next;
        arr[i] = tmp->key;
        free(tmp);
    }
}
