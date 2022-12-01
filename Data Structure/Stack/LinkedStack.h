/**
 * @file LinkedStack.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 栈 链表实现 (Linked Stack)
 * @version 0.1
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 栈 stack 是一个有 n(n>=0) 个元素的有穷线性表。
 * 栈 stack 属于 stack_t ，元素 data 属于 stack_data_t 。
 */

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdbool.h> // bool

typedef int stack_data_t;

typedef struct stack stack_t;

/**
 * @brief 创建一个空栈
 *
 * @return 一个指向空栈的指针
 */
stack_t *LinkedStack_Create(void);

/**
 * @brief 销毁一个栈 stack
 *
 * @param stack 一个指向待销毁栈的指针
 */
void LinkedStack_Destroy(stack_t *stack);

/**
 * @brief 求栈 stack 的长度
 *
 * @param stack 一个指向栈的指针
 * @return 栈长度
 */
int LinkedStack_Size(const stack_t *stack);

/**
 * @brief 判断栈 stack 是否已空
 *
 * @param stack 一个指向栈的指针
 * @return 如果栈已空则返回 true ，否则返回 false
 */
bool LinkedStack_IsEmpty(const stack_t *stack);

/**
 * @brief 入栈，将元素 data 压入到栈 stack 的顶部
 *
 * @param stack 一个指向栈的指针
 * @param data 一个待入栈的元素
 */
void LinkedStack_Push(stack_t *stack, stack_data_t data);

/**
 * @brief 出栈，将栈 stack 的顶部的元素弹出来
 *
 * @param stack 一个指向栈的指针
 * @return 栈顶元素
 */
stack_data_t LinkedStack_Pop(stack_t *stack);

/**
 * @brief 检查栈 stack 的顶部元素，不改变栈
 *
 * @param stack 一个指向栈的指针
 * @return 栈顶元素
 */
stack_data_t LinkedStack_Top(const stack_t *stack);

#endif
