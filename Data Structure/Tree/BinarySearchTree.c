#include "BinarySearchTree.h"
#include "QueueForBST.h"

#include <stdio.h>
#include <stdlib.h>

struct node
{
    // The data stored in this node.
    tree_data_t data;

    // A pointer to the left child of the node.
    struct node *left;

    // A pointer to the right child of the node.
    struct node *right;
};

struct tree
{
    // Number of elements.
    int count;

    // A pointer to the root node.
    struct node *root;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static void destroy_node(struct node *node)
{
    if (node)
    {
        destroy_node(node->left);
        destroy_node(node->right);
        free(node);
    }
}

static void traverse_node(struct node *node, traverse_t type, void (*p_trav)(tree_data_t data))
{
    if (node)
    {
        switch (type)
        {
            case PRE_ORDER:
            {
                p_trav(node->data);
                traverse_node(node->left, PRE_ORDER, p_trav);
                traverse_node(node->right, PRE_ORDER, p_trav);
                break;
            }

            case IN_ORDER:
            {
                traverse_node(node->left, IN_ORDER, p_trav);
                p_trav(node->data);
                traverse_node(node->right, IN_ORDER, p_trav);
                break;
            }

            case POST_ORDER:
            {
                traverse_node(node->left, POST_ORDER, p_trav);
                traverse_node(node->right, POST_ORDER, p_trav);
                p_trav(node->data);
                break;
            }

            case LEVEL_ORDER:
            {
                queue_t *queue = ArrayQueue_Create();
                ArrayQueue_Enqueue(queue, node);
                while (!ArrayQueue_IsEmpty(queue))
                {
                    node = ArrayQueue_Dequeue(queue);
                    p_trav(node->data);
                    if (node->left)
                    {
                        ArrayQueue_Enqueue(queue, node->left);
                    }
                    if (node->right)
                    {
                        ArrayQueue_Enqueue(queue, node->right);
                    }
                }
                ArrayQueue_Destroy(queue);
                break;
            }

            default:
            {
                fprintf(stderr, "ERROR: Invalid type for traverse.\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }
}

static struct node *insert_node(tree_t *tree, struct node *node, tree_data_t data)
{
    if (node == NULL)
    {
        node = (struct node *)malloc(sizeof(struct node));
        check_pointer(node);

        node->data = data;
        node->left = NULL;
        node->right = NULL;
        tree->count++;
    }
    else
    {
        if (data < node->data)
        {
            node->left = insert_node(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = insert_node(tree, node->right, data);
        }
    }

    return node;
}

static struct node *find_min_node(struct node *node)
{
    while (node->left) // node is not NULL
    {
        node = node->left;
    }

    return node;
}

static struct node *delete_node(tree_t *tree, struct node *node, tree_data_t data)
{
    if (node)
    {
        if (data < node->data)
        {
            node->left = delete_node(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = delete_node(tree, node->right, data);
        }
        else // data == node->data
        {
            if (node->left && node->right)
            {
                struct node *tmp = find_min_node(node->right); // node->right is not NULL
                node->data = tmp->data;
                node->right = delete_node(tree, node->right, tmp->data);
            }
            else
            {
                struct node *tmp = node;
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
    check_pointer(tree);

    tree->root = NULL;
    tree->count = 0;

    return tree;
}

void Tree_Destroy(tree_t *tree)
{
    destroy_node(tree->root);
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

void Tree_Traverse(tree_t *tree, traverse_t type, void (*p_trav)(tree_data_t data))
{
    traverse_node(tree->root, type, p_trav);
}

tree_data_t Tree_Find(const tree_t *tree, tree_data_t data)
{
    struct node *current = tree->root;

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
    struct node *current = tree->root;

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
    struct node *current = tree->root;

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
    tree->root = insert_node(tree, tree->root, data);
}

void Tree_Delete(tree_t *tree, tree_data_t data)
{
    tree->root = delete_node(tree, tree->root, data);
}
