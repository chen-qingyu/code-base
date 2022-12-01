/**
 * @file LinkedQueue.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 队列 链表实现 (Linked Queue)
 * @version 0.1
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 队列 queue 是一个有 n(n>=0) 个元素的有穷线性表。
 * 队列 queue 属于 queue_t ，元素 data 属于 queue_data_t 。
 */

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdbool.h> // bool

typedef int queue_data_t;

typedef struct queue queue_t;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
queue_t *LinkedQueue_Create(void);

/**
 * @brief 销毁一个队列 queue
 *
 * @param queue 一个指向待销毁队列的指针
 */
void LinkedQueue_Destroy(queue_t *queue);

/**
 * @brief 求队列 queue 的长度
 *
 * @param queue 一个指向队列的指针
 * @return 队列长度
 */
int LinkedQueue_Size(const queue_t *queue);

/**
 * @brief 判断队列 queue 是否已空
 *
 * @param queue 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool LinkedQueue_IsEmpty(const queue_t *queue);

/**
 * @brief 入队，将元素 data 插入到队列 queue 的尾部
 *
 * @param queue 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedQueue_Enqueue(queue_t *queue, queue_data_t data);

/**
 * @brief 出队，将队列 queue 的队首元素出队
 *
 * @param queue 一个指向队列的指针
 * @return 队首元素
 */
queue_data_t LinkedQueue_Dequeue(queue_t *queue);

#endif
