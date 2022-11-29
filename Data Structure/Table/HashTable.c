#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    EMPTY,
    FULL,
    DELETED
} table_state_t;

struct item
{
    table_key_t key;
    table_value_t value;
    table_state_t state;
};

#define HASHTABLE_CAPACITY 17

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static int hash(table_key_t key)
{
    unsigned int index = 0;

    while (*key != '\0')
    {
        index = (index << 5) + *key++;
    }

    return index % HASHTABLE_CAPACITY;
}

static int find_pos(const table_t *table, table_key_t key)
{
    int currentPos, newPos;
    int conflictCnt = 0;

    currentPos = hash(key);
    newPos = currentPos;

    while (table[newPos].state != EMPTY && strcmp(table[newPos].key, key) != 0)
    {
        if (++conflictCnt % 2)
        {
            newPos = currentPos + (conflictCnt + 1) * (conflictCnt + 1) / 4;
            if (newPos >= HASHTABLE_CAPACITY)
            {
                newPos = newPos % HASHTABLE_CAPACITY;
            }
        }
        else
        {
            newPos = currentPos - conflictCnt * conflictCnt / 4;
            while (newPos < 0)
            {
                newPos += HASHTABLE_CAPACITY;
            }
        }
    }

    return newPos;
}

/*******************************
Interface functions implementation.
*******************************/

table_t *HashTable_Create(void)
{
    table_t *table = (table_t *)malloc(sizeof(struct item) * HASHTABLE_CAPACITY);
    check_pointer(table);

    for (int i = 0; i < HASHTABLE_CAPACITY; i++)
    {
        table[i].key = NULL;
        table[i].state = EMPTY;
    }

    return table;
}

void HashTable_Destroy(table_t *table)
{
    for (int i = 0; i < HASHTABLE_CAPACITY; ++i)
    {
        if (table[i].key)
        {
            free(table[i].key);
        }
    }
    free(table);
}

table_value_t HashTable_Get(const table_t *table, table_key_t key)
{
    int pos = find_pos(table, key);

    return table[pos].state == FULL ? table[pos].value : NOT_FOUND;
}

void HashTable_Modify(table_t *table, table_key_t key, table_value_t value)
{
    int pos = find_pos(table, key);

    if (table[pos].state == FULL)
    {
        table[pos].value = value;
    }
    else
    {
        fprintf(stderr, "Key-value pair does not exist.\n");
    }
}

void HashTable_Insert(table_t *table, table_key_t key, table_value_t value)
{
    int pos = find_pos(table, key);

    if (table[pos].state != FULL)
    {
        if (table[pos].state == DELETED)
        {
            free(table[pos].key);
            table[pos].key = NULL;
        }
        table[pos].state = FULL;
        table[pos].key = (char *)malloc(strlen(key) * sizeof(char) + 1);
        check_pointer(table[pos].key);

        strcpy(table[pos].key, key);
        table[pos].value = value;
    }
    else
    {
        fprintf(stderr, "Key-value pair already exists.\n");
    }
}

void HashTable_Delete(table_t *table, table_key_t key)
{
    int pos = find_pos(table, key);

    if (table[pos].state == FULL)
    {
        table[pos].state = DELETED;
    }
    else
    {
        fprintf(stderr, "Key-value pair does not exist.\n");
    }
}
