#include "HashTable.h"

#include <assert.h>
#include <stdio.h>

void TestHashTable()
{
    table_t *table = HashTable_Create();

    HashTable_Insert(table, "aaa", 1);
    HashTable_Insert(table, "bbb", 2);
    HashTable_Insert(table, "ccc", 3);
    HashTable_Insert(table, "ddd", 4);

    assert(HashTable_Get(table, "aaa") == 1);
    assert(HashTable_Get(table, "bbb") == 2);
    assert(HashTable_Get(table, "ccc") == 3);
    assert(HashTable_Get(table, "ddd") == 4);

    HashTable_Modify(table, "aaa", 233);
    assert(HashTable_Get(table, "aaa") == 233);

    HashTable_Delete(table, "aaa");
    assert(HashTable_Get(table, "aaa") == HASHTABLE_NOT_FOUND);

    HashTable_Destroy(table);

    printf("Hash Table Test OK.\n");
}

int main(void)
{
    TestHashTable();

    return 0;
}
