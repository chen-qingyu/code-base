/**
 * @file HashTable.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 散列表 (Hash Table)
 * @version 0.1
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 散列表 table 是由 n(n>=0) 个键值对(key-value pair)构成的集合。
 * 散列表 table 属于 table_t ，键 key 属于 table_key_t ，值 value 属于 table_value_t 。
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h> // bool

#define HASHTABLE_NOT_FOUND (-1) // a value of table_value_t that indicates not found

typedef char* table_key_t;

typedef int table_value_t;

typedef struct item table_t;

/**
 * @brief 创建一个空散列表
 *
 * @return 一个指向空散列表的指针
 */
table_t* HashTable_Create(void);

/**
 * @brief 销毁一个散列表
 *
 * @param self 一个指向待销毁散列表的指针
 */
void HashTable_Destroy(table_t* self);

/**
 * @brief 在散列表中取 key 对应的 value
 *
 * @param self 一个指向散列表的指针
 * @param key 一个 key
 * @return key 对应的 value 或者 HASHTABLE_NOT_FOUND
 */
table_value_t HashTable_Get(const table_t* self, table_key_t key);

/**
 * @brief 在散列表中修改 key 对应的 value
 *
 * @param self 一个指向散列表的指针
 * @param key 一个 key
 * @param value 一个新的 value
 */
void HashTable_Modify(table_t* self, table_key_t key, table_value_t value);

/**
 * @brief 在散列表中插入一个新的键值对
 *
 * @param self 一个指向散列表的指针
 * @param key 一个新的 key
 * @param value 一个新的 key 对应的 value
 */
void HashTable_Insert(table_t* self, table_key_t key, table_value_t value);

/**
 * @brief 在散列表中删除 key 对应的键值对
 *
 * @param self 一个指向散列表的指针
 * @param key 待删除键值对的 key
 */
void HashTable_Delete(table_t* self, table_key_t key);

#endif
