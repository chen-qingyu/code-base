#include "BinarySearchTree.h"
#include "QueueForBST.h"

struct node
{
    tree_data_t data;
    struct node *left;
    struct node *right;
};

struct tree
{
    struct node *root;
    int count;
};

/*******************************
Helper functions implementation.
*******************************/

static void DestroyNode(tree_node_t *node)
{
    if (node)
    {
        DestroyNode(node->left);
        DestroyNode(node->right);
        free(node);
    }
}

static void TraverseNode(tree_node_t *node, traverse_t type, void (*pTrav)(tree_data_t data))
{
    if (node)
    {
        switch (type)
        {
            // 先序遍历
            case PRE_ORDER:
            {
                pTrav(node->data);
                TraverseNode(node->left, PRE_ORDER, pTrav);
                TraverseNode(node->right, PRE_ORDER, pTrav);
                break;
            }
            // 中序遍历
            case IN_ORDER:
            {
                TraverseNode(node->left, IN_ORDER, pTrav);
                pTrav(node->data);
                TraverseNode(node->right, IN_ORDER, pTrav);
                break;
            }
            // 后序遍历
            case POST_ORDER:
            {
                TraverseNode(node->left, POST_ORDER, pTrav);
                TraverseNode(node->right, POST_ORDER, pTrav);
                pTrav(node->data);
                break;
            }
            // 层次遍历
            case LEVEL_ORDER:
            {
                queue_t *queue = Queue_Create();
                Queue_Enqueue(queue, node);
                while (!Queue_IsEmpty(queue))
                {
                    node = Queue_Dequeue(queue);
                    pTrav(node->data);
                    if (node->left)
                    {
                        Queue_Enqueue(queue, node->left);
                    }
                    if (node->right)
                    {
                        Queue_Enqueue(queue, node->right);
                    }
                }
                Queue_Destroy(queue);
                break;
            }
            default:
            {
                fprintf(stderr, "Error type!\n");
                break;
            }
        }
    }
}

static tree_node_t *InsertNode(tree_t *tree, tree_node_t *node, tree_data_t data)
{
    if (node == NULL)
    {
        node = (tree_node_t *)malloc(sizeof(struct node));
        if (node == NULL)
        {
            fprintf(stderr, "ERROR: There was not enough memory.\n");
            exit(-2);
        }
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        tree->count++;
    }
    else
    {
        if (data < node->data)
        {
            node->left = InsertNode(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = InsertNode(tree, node->right, data);
        }
    }

    return node;
}

static tree_node_t *FindMinNode(tree_node_t *node)
{
    tree_node_t *current = node;

    if (current)
    {
        while (current->left)
        {
            current = current->left;
        }
    }

    return current;
}

static tree_node_t *DeleteNode(tree_t *tree, tree_node_t *node, tree_data_t data)
{
    if (node == NULL)
    {
        fprintf(stderr, "Error: There was no item %d.\n", data);
    }
    else
    {
        if (data < node->data)
        {
            node->left = DeleteNode(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = DeleteNode(tree, node->right, data);
        }
        else
        {
            if (node->left && node->right)
            {
                tree_node_t *tmp = FindMinNode(node->right);
                node->data = tmp->data;
                node->right = DeleteNode(tree, node->right, tmp->data);
            }
            else
            {
                tree_node_t *tmp = node;
                node = node->left ? node->left : node->right;
                free(tmp);
                tree->count--;
            }
        }
    }

    return node;
}

/*******************************
Interface functions implementation.
*******************************/

tree_t *Tree_Create(void)
{
    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    if (tree == NULL)
    {
        fprintf(stderr, "ERROR: There was not enough memory.\n");
        exit(-2);
    }

    tree->root = NULL;
    tree->count = 0;

    return tree;
}

void Tree_Destroy(tree_t *tree)
{
    DestroyNode(tree->root);
    free(tree);
}

int Tree_Size(const tree_t *tree)
{
    return tree->count;
}

bool Tree_IsEmpty(const tree_t *tree)
{
    return tree->count == 0;
}

void Tree_Traverse(tree_t *tree, traverse_t type, void (*pTrav)(tree_data_t data))
{
    TraverseNode(tree->root, type, pTrav);
}

tree_data_t Tree_Find(const tree_t *tree, tree_data_t data)
{
    tree_node_t *current = tree->root;

    while (current)
    {
        if (data > current->data)
        {
            current = current->right;
        }
        else if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            return current->data;
        }
    }

    return TREE_NOT_FOUND;
}

tree_data_t Tree_FindMin(const tree_t *tree)
{
    tree_node_t *current = tree->root;

    if (current)
    {
        while (current->left)
        {
            current = current->left;
        }
    }

    return current ? current->data : TREE_NOT_FOUND;
}

tree_data_t Tree_FindMax(const tree_t *tree)
{
    tree_node_t *current = tree->root;

    if (current)
    {
        while (current->right)
        {
            current = current->right;
        }
    }

    return current ? current->data : TREE_NOT_FOUND;
}

void Tree_Insert(tree_t *tree, tree_data_t data)
{
    tree->root = InsertNode(tree, tree->root, data);
}

void Tree_Delete(tree_t *tree, tree_data_t data)
{
    tree->root = DeleteNode(tree, tree->root, data);
}
