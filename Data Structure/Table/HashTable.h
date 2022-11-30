/*
散列表 (Hash Table)
对象集：散列表是由n(n>=0)个键值对(key-value pair)构成的集合
操作集：散列表 table 属于 table_t ，键 key 属于 table_key_t ，值 value 属于 table_value_t
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h> // bool

#define HASHTABLE_NOT_FOUND (-1) // a value of table_value_t that indicates not found

typedef char *table_key_t;

typedef int table_value_t;

typedef struct item table_t;

/*************************************************
  Description:    创建一个空散列表
  Parameter:      空
  Return:         一个指向空散列表的指针
*************************************************/
table_t *HashTable_Create(void);

/*************************************************
  Description:    销毁一个散列表 table
  Parameter:      一个指向待销毁散列表的指针 table
  Return:         空
*************************************************/
void HashTable_Destroy(table_t *table);

/*************************************************
  Description:    在散列表 table 中取 key 对应的 value
  Parameter:      一个指向散列表的指针 table
                  一个 key
  Return:         key 对应的 value 或者 HASHTABLE_NOT_FOUND
*************************************************/
table_value_t HashTable_Get(const table_t *table, table_key_t key);

/*************************************************
  Description:    在散列表 table 中修改 key 对应的 value
  Parameter:      一个指向散列表的指针 table
                  一个 key
                  一个新的 value
  Return:         空
*************************************************/
void HashTable_Modify(table_t *table, table_key_t key, table_value_t value);

/*************************************************
  Description:    在散列表 table 中插入一个新的键值对
  Parameter:      一个指向散列表的指针 table
                  一对新的 key 和 value
  Return:         空
*************************************************/
void HashTable_Insert(table_t *table, table_key_t key, table_value_t value);

/*************************************************
  Description:    在散列表 table 中删除 key 对应的键值对
  Parameter:      一个指向散列表的指针 table
                  待删除键值对的 key
  Return:         空
*************************************************/
void HashTable_Delete(table_t *table, table_key_t key);

#endif
