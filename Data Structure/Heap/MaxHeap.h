/**
 * @file MaxHeap.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 最大堆 (Max Heap)
 * @version 0.1
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 最大堆 heap 是一棵完全二叉树，每个结点的元素值不小于其子结点的元素值。
 * 最大堆 heap 属于 heap_t ，元素 data 属于 heap_data_t 。
 */

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdbool.h> // bool

typedef int heap_data_t;

typedef struct heap heap_t;

/**
 * @brief 创建一个空堆
 *
 * @return heap_t* 一个指向空堆的指针
 */
heap_t *MaxHeap_Create(void);

/**
 * @brief 销毁一个堆 heap
 *
 * @param heap 一个指向待销毁堆的指针
 */
void MaxHeap_Destroy(heap_t *heap);

/**
 * @brief 求堆 heap 的元素个数
 *
 * @param heap 一个指向堆的指针
 * @return 堆的元素个数
 */
int MaxHeap_Size(const heap_t *heap);

/**
 * @brief 判断堆 heap 是否已空
 *
 * @param heap 一个指向堆的指针
 * @return 如果堆已空则返回 true ，否则返回 false
 */
bool MaxHeap_IsEmpty(const heap_t *heap);

/**
 * @brief 在堆 heap 中插入一个元素 data
 *
 * @param heap 一个指向堆的指针
 * @param data 一个待插入元素
 */
void MaxHeap_Push(heap_t *heap, heap_data_t data);

/**
 * @brief  在堆 heap 中删除堆顶元素
 *
 * @param heap 一个指向堆的指针
 * @return 堆顶元素
 */
heap_data_t MaxHeap_Pop(heap_t *heap);

/**
 * @brief 查看堆 heap 的堆顶元素
 *
 * @param heap 一个指向堆的指针
 * @return 堆顶元素
 */
heap_data_t MaxHeap_Top(heap_t *heap);

#endif
