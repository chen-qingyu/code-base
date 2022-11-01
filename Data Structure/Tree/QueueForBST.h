/*
队列(Queue)
对象集：有n(n>=0)个元素的有穷线性表
操作集：队列 queue 属于 queue_t ，元素 data 属于 queue_data_t
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node queue_data_t;

typedef struct queue queue_t;

/*************************************************
  Description:    创建一个空队列
  Parameter:      空
  Return:         一个指向空队列的指针
*************************************************/
queue_t *Queue_Create(void);

/*************************************************
  Description:    销毁一个队列 queue
  Parameter:      一个指向待销毁队列的指针 queue
  Return:         空
*************************************************/
void Queue_Destroy(queue_t *queue);

/*************************************************
  Description:    求队列 queue 的长度
  Parameter:      一个指向队列的指针 queue
  Return:         队列长度
*************************************************/
int Queue_Size(const queue_t *queue);

/*************************************************
  Description:    判断队列 queue 是否已空
  Parameter:      一个指向队列的指针 queue
  Return:         如果队列已空则返回 true ，否则返回 false
*************************************************/
bool Queue_IsEmpty(const queue_t *queue);

/*************************************************
  Description:    入队，将元素 data 插入到队列 queue 的尾部
  Parameter:      一个指向队列的指针 queue
                  一个待入队的元素 data
  Return:         空
*************************************************/
void Queue_Enqueue(queue_t *queue, queue_data_t data);

/*************************************************
  Description:    出队，将队列 queue 的队首元素出队
  Parameter:      一个指向队列的指针 queue
  Return:         队首元素
*************************************************/
queue_data_t Queue_Dequeue(queue_t *queue);

#endif
