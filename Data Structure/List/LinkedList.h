/**
 * @file LinkedList.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 列表 链表实现 (Linked List)
 * @version 0.1
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 列表 list 是由 n (n >= 0) 个元素构成的有序序列： a_1, a_2, a_3 ... a_n 。
 * 列表 list 属于 list_t ，整数 i 表示元素下标（从0开始），元素 data 属于 list_data_t 。
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h> // bool

#define LIST_NOT_FOUND (-1) // a value of list_data_t that indicates not found

typedef int list_data_t;

typedef struct list list_t;

/**
 * @brief 创建一个空列表
 *
 * @return 一个指向空列表的指针
 */
list_t *LinkedList_Create(void);

/**
 * @brief 销毁一个列表 list
 *
 * @param list 一个指向待销毁列表的指针
 */
void LinkedList_Destroy(list_t *list);

/**
 * @brief 求列表 list 的长度
 *
 * @param list 一个指向列表的指针
 * @return 列表长度
 */
int LinkedList_Size(const list_t *list);

/**
 * @brief 判断列表 list 是否为空
 *
 * @param list 一个指向列表的指针
 * @return 如果列表为空则返回 true ，否则返回 false
 */
bool LinkedList_IsEmpty(const list_t *list);

/**
 * @brief 取列表 list 的第 i 个元素
 *
 * @param list 一个指向列表的指针
 * @param i 下标 (0 <= i < Size(list))
 * @return 第 i 个元素
 */
list_data_t LinkedList_At(const list_t *list, int i);

/**
 * @brief 求元素 data 在列表 list 中的下标
 *
 * @param list 一个指向列表的指针
 * @param data 一个待寻找元素
 * @return 待寻找元素 data 的下标 i 或者 LIST_NOT_FOUND 代表没找到
 */
int LinkedList_Find(const list_t *list, list_data_t data);

/**
 * @brief 在列表 list 的下标为 i 的位置上插入一个元素 data
 *
 * @param list 一个指向列表的指针
 * @param i 下标 (0 <= i <= Size(list))
 * @param data 待插入元素
 */
void LinkedList_Insert(list_t *list, int i, list_data_t data);

/**
 * @brief 从列表 list 当中删除下标为 i 的元素
 *
 * @param list 一个指向列表的指针
 * @param i 下标 (0 <= i < Size(list))
 */
void LinkedList_Delete(list_t *list, int i);

/**
 * @brief 遍历 list
 *
 * @param list 一个指向列表的指针
 * @param p_trav 一个指向用以操作列表元素的函数的指针
 */
void LinkedList_Traverse(list_t *list, void (*p_trav)(list_data_t data));

/**
 * @brief 就地逆置列表 list
 *
 * @param list 一个指向列表的指针
 */
void LinkedList_Reverse(list_t *list);

#endif
