/*
栈(Stack)
对象集：有n(n>=0)个元素的有穷线性表
操作集：栈 stack 属于 stack_t ，元素 data 属于 stack_data_t
*/

#ifndef STACK_H
#define STACK_H

#include <stdbool.h> // bool

typedef int stack_data_t;

typedef struct stack stack_t;

/*************************************************
  Description:    创建一个空栈
  Parameter:      空
  Return:         一个指向空栈的指针
*************************************************/
stack_t *Stack_Create(void);

/*************************************************
  Description:    销毁一个栈 stack
  Parameter:      一个指向待销毁栈的指针 stack
  Return:         空
*************************************************/
void Stack_Destroy(stack_t *stack);

/*************************************************
  Description:    求栈 stack 的长度
  Parameter:      一个指向栈的指针 stack
  Return:         栈长度
*************************************************/
int Stack_Size(const stack_t *stack);

/*************************************************
  Description:    判断栈 stack 是否已空
  Parameter:      一个指向栈的指针 stack
  Return:         如果栈已空则返回 true ，否则返回 false
*************************************************/
bool Stack_IsEmpty(const stack_t *stack);

/*************************************************
  Description:    入栈，将元素 data 压入到栈 stack 的顶部
  Parameter:      一个指向栈的指针 stack
                  一个待入栈的元素 data
  Return:         空
*************************************************/
void Stack_Push(stack_t *stack, stack_data_t data);

/*************************************************
  Description:    出栈，将栈 stack 的顶部的元素弹出来
  Parameter:      一个指向栈的指针 stack
  Return:         栈顶元素
*************************************************/
stack_data_t Stack_Pop(stack_t *stack);

/*************************************************
  Description:    检查栈 stack 的顶部元素，不改变栈
  Parameter:      一个指向栈的指针 stack
  Return:         栈顶元素
*************************************************/
stack_data_t Stack_Top(const stack_t *stack);

#endif
