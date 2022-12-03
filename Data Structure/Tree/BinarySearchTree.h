/**
 * @file BinarySearchTree.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 二叉搜索树 (Binary Search Tree)
 * @version 0.1
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 二叉树 tree 是一个有穷的结点集合。若不为空，则由根结点和其左、右二叉子树组成。
 * 二叉树 tree 属于 tree_t，结点数据 data 属于 tree_data_t 。
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h> // bool

#define TREE_NOT_FOUND (-1) // a value of tree_data_t that indicates not found

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER
} traverse_t;

typedef int tree_data_t;

typedef struct tree tree_t;

/**
 * @brief 创建一个空二叉搜索树
 *
 * @return 一个指向空二叉搜索树的指针
 */
tree_t *Tree_Create(void);

/**
 * @brief 销毁一个二叉搜索树 tree
 *
 * @param tree 一个指向待销毁二叉搜索树的指针
 */
void Tree_Destroy(tree_t *tree);

/**
 * @brief 求二叉搜索树 tree 的元素个数
 *
 * @param tree 一个指向二叉搜索树的指针
 * @return 二叉搜索树的元素个数
 */
int Tree_Size(const tree_t *tree);

/**
 * @brief 判断二叉搜索树 tree 是否为空
 *
 * @param tree 一个指向二叉搜索树的指针
 * @return 如果二叉搜索树为空则返回 true ，否则返回 false
 */
bool Tree_IsEmpty(const tree_t *tree);

/**
 * @brief 遍历一个二叉搜索树 tree
 *
 * @param tree 一个指向二叉搜索树的指针
 * @param type 一个枚举遍历类型
 *              - PRE_ORDER   先序遍历
 *              - IN_ORDER    中序遍历
 *              - POST_ORDER  后序遍历
 *              - LEVEL_ORDER 层次遍历
 * @param p_trav 一个对遍历到的每个元素进行操作的函数的指针
 */
void Tree_Traverse(tree_t *tree, traverse_t type, void (*p_trav)(tree_data_t data));

/**
 * @brief 在一个二叉搜索树 tree 中寻找元素 data
 *
 * @param tree 一个指向二叉搜索树的指针
 * @param data 一个待寻找元素
 * @return 元素 data 或者 TREE_NOT_FOUND
 */
tree_data_t Tree_Find(const tree_t *tree, tree_data_t data);

/**
 * @brief 在一个二叉搜索树 tree 中寻找最小元素
 *
 * @param tree 一个指向二叉搜索树的指针
 * @return 最小的元素或者 TREE_NOT_FOUND
 */
tree_data_t Tree_FindMin(const tree_t *tree);

/**
 * @brief 在一个二叉搜索树 tree 中寻找最大元素
 *
 * @param tree 一个指向二叉搜索树的指针
 * @return 最大的元素或者 TREE_NOT_FOUND
 */
tree_data_t Tree_FindMax(const tree_t *tree);

/**
 * @brief 在一个二叉搜索树 tree 中插入元素 data
 *
 * @param tree 一个指向二叉搜索树的指针
 * @param data 一个待插入元素
 */
void Tree_Insert(tree_t *tree, tree_data_t data);

/**
 * @brief 在一个二叉搜索树 tree 中删除元素 data
 *
 * @param tree 一个指向二叉搜索树的指针
 * @param data 一个待删除元素
 */
void Tree_Delete(tree_t *tree, tree_data_t data);

#endif
