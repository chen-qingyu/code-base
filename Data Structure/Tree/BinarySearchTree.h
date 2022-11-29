/*
二叉搜索树(Binary Search Tree)
对象集：一个有穷的结点集合。若不为空，则由根结点和其左、右二叉子树组成。
操作集：二叉树 tree 属于 tree_t，结点数据 data 属于 tree_data_t
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER
} traverse_t;

typedef int tree_data_t;

typedef struct node tree_node_t;

typedef struct tree tree_t;

#define TREE_NOT_FOUND INT_MAX // a value of tree_data_t that indicates not found

/*************************************************
  Description:    创建一个空二叉搜索树
  Parameter:      空
  Return:         一个指向空二叉搜索树的指针
*************************************************/
tree_t *Tree_Create(void);

/*************************************************
  Description:    销毁一个二叉搜索树 tree
  Parameter:      一个指向待销毁二叉搜索树的指针 tree
  Return:         空
*************************************************/
void Tree_Destroy(tree_t *tree);

/*************************************************
  Description:    求二叉搜索树 tree 的元素个数
  Parameter:      一个指向二叉搜索树的指针 tree
  Return:         二叉搜索树的元素个数
*************************************************/
int Tree_Size(const tree_t *tree);

/*************************************************
  Description:    判断二叉搜索树 tree 是否为空
  Parameter:      一个指向二叉搜索树的指针 tree
  Return:         如果二叉搜索树为空则返回 true ，否则返回 false
*************************************************/
bool Tree_IsEmpty(const tree_t *tree);

/*************************************************
  Description:    遍历一个二叉搜索树 tree
  Parameter:      一个指向二叉搜索树的指针 tree
                  一个枚举遍历类型 type
                    - PRE_ORDER   先序遍历
                    - IN_ORDER    中序遍历
                    - POST_ORDER  后序遍历
                    - LEVEL_ORDER 层次遍历
                  一个对遍历到的每个元素进行操作的函数的指针 pTrav
  Return:         空
*************************************************/
void Tree_Traverse(tree_t *tree, traverse_t type, void (*pTrav)(tree_data_t data));

/*************************************************
  Description:    在一个二叉搜索树 tree 中寻找元素 data
  Parameter:      一个指向二叉搜索树的指针 tree
                  一个待寻找元素 data
  Return:         元素 data 或者 TREE_NOT_FOUND
*************************************************/
tree_data_t Tree_Find(const tree_t *tree, tree_data_t data);

/*************************************************
  Description:    在一个二叉搜索树 tree 中寻找最小元素
  Parameter:      一个指向二叉搜索树的指针 tree
  Return:         最小的元素
*************************************************/
tree_data_t Tree_FindMin(const tree_t *tree);

/*************************************************
  Description:    在一个二叉搜索树 tree 中寻找最大元素
  Parameter:      一个指向二叉搜索树的指针 tree
  Return:         最大的元素
*************************************************/
tree_data_t Tree_FindMax(const tree_t *tree);

/*************************************************
  Description:    在一个二叉搜索树 tree 中插入元素 data
  Parameter:      一个指向二叉搜索树的指针 tree
                  一个待插入元素 data
  Return:         空
*************************************************/
void Tree_Insert(tree_t *tree, tree_data_t data);

/*************************************************
  Description:    在一个二叉搜索树 tree 中删除元素 data
  Parameter:      一个指向二叉搜索树的指针 tree
                  一个待删除元素 data
  Return:         空
*************************************************/
void Tree_Delete(tree_t *tree, tree_data_t data);

#endif
