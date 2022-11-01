/*
列表(List)
对象集：n (n >= 0) 个元素构成的有序序列： a_1, a_2, a_3 ... a_n.
操作集：列表 list 属于 list_t ，整数 i 表示元素下标(从0开始)，元素 data 属于 list_data_t
*/

#ifndef LIST_H
#define LIST_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int list_data_t;

typedef struct list list_t;

/*************************************************
  Description:    创建一个空列表
  Parameter:      空
  Return:         一个指向空列表的指针
*************************************************/
list_t *List_Create(void);

/*************************************************
  Description:    销毁一个列表 list
  Parameter:      一个指向待销毁列表的指针 list
  Return:         空
*************************************************/
void List_Destroy(list_t *list);

/*************************************************
  Description:    求列表 list 的长度
  Parameter:      一个指向列表的指针 list
  Return:         列表长度
*************************************************/
int List_Size(const list_t *list);

/*************************************************
  Description:    判断列表 list 是否为空
  Parameter:      一个指向列表的指针 list
  Return:         如果列表为空则返回 true ，否则返回 false
*************************************************/
bool List_IsEmpty(const list_t *list);

/*************************************************
  Description:    取列表 list 的第 i 个元素
  Parameter:      一个指向列表的指针 list
                  下标 i (0 <= i < Size(list))
  Return:         第 i 个元素
*************************************************/
list_data_t List_At(const list_t *list, int i);

/*************************************************
  Description:    求元素 data 在列表 list 中的下标
  Parameter:      一个指向列表的指针 list
                  一个待寻找元素 data
  Return:         待寻找元素 data 的下标 i 或者 -1 代表没找到
*************************************************/
int List_Find(const list_t *list, list_data_t data);

/*************************************************
  Description:    在列表 list 的下标为 i 的位置上插入一个元素 data
  Parameter:      一个指向列表的指针 list
                  下标 i (0 <= i <= Size(list))
                  待插入元素 data
  Return:         空
*************************************************/
void List_Insert(list_t *list, int i, list_data_t data);

/*************************************************
  Description:    从列表 list 当中删除下标为 i 的元素
  Parameter:      一个指向列表的指针 list
                  下标 i (0 <= i < Size(list))
  Return:         空
*************************************************/
void List_Delete(list_t *list, int i);

/*************************************************
  Description:    遍历 list
  Parameter:      一个指向列表的指针 list
                  一个指向用以操作列表元素的函数的指针 pTrav
  Return:         空
*************************************************/
void List_Traverse(list_t *list, void (*pTrav)(list_data_t data));

/*************************************************
  Description:    就地逆置列表 list
  Parameter:      一个指向列表的指针 list
  Return:         空
*************************************************/
void List_Reverse(list_t *list);

#endif
