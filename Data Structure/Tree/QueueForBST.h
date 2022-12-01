/**
 * @file QueueForBST.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 队列 数组实现 (Array Queue)
 * @version 0.1
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * C语言不支持泛型，这里需要用到以树节点作为元素的队列。
 * 只是改了一下 typedef 。
 */

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <stdbool.h> // bool

typedef struct node *queue_data_t;

typedef struct queue queue_t;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
queue_t *ArrayQueue_Create(void);

/**
 * @brief 销毁一个队列 queue
 *
 * @param queue 一个指向待销毁队列的指针
 */
void ArrayQueue_Destroy(queue_t *queue);

/**
 * @brief 求队列 queue 的长度
 *
 * @param queue 一个指向队列的指针
 * @return 队列长度
 */
int ArrayQueue_Size(const queue_t *queue);

/**
 * @brief 判断队列 queue 是否已空
 *
 * @param queue 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool ArrayQueue_IsEmpty(const queue_t *queue);

/**
 * @brief 入队，将元素 data 插入到队列 queue 的尾部
 *
 * @param queue 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void ArrayQueue_Enqueue(queue_t *queue, queue_data_t data);

/**
 * @brief 出队，将队列 queue 的队首元素出队
 *
 * @param queue 一个指向队列的指针
 * @return 队首元素
 */
queue_data_t ArrayQueue_Dequeue(queue_t *queue);

#endif
