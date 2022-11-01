#include "BinarySearchTree.h"
#include <assert.h>
#include <string.h>

char str[64] = {0};

void Visit(tree_data_t n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

void BinarySearchTreeTest()
{
    tree_t *tree = Tree_Create();

    Tree_Insert(tree, 3);
    Tree_Insert(tree, 1);
    Tree_Insert(tree, 2);
    Tree_Insert(tree, 4);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 1);

    Tree_Traverse(tree, PRE_ORDER, Visit);
    assert(strcmp(str, "3 1 2 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    Tree_Traverse(tree, IN_ORDER, Visit);
    assert(strcmp(str, "1 2 3 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    Tree_Traverse(tree, POST_ORDER, Visit);
    assert(strcmp(str, "2 1 5 4 3 ") == 0);
    memset(str, 0, sizeof(str));

    Tree_Traverse(tree, LEVEL_ORDER, Visit);
    assert(strcmp(str, "3 1 4 2 5 ") == 0);
    memset(str, 0, sizeof(str));

    tree_node_t *t = Tree_Find(tree, 2);
    assert(t->data == 2);
    t = Tree_Find(tree, 0);
    assert(t == NULL);

    tree_node_t *min = Tree_FindMin(tree);
    assert(min->data == 1);
    tree_node_t *max = Tree_FindMax(tree);
    assert(max->data == 5);

    Tree_Delete(tree, 5);
    max = Tree_FindMax(tree);
    assert(max->data == 4);

    Tree_Destroy(tree);
    tree = NULL;

    printf("Binary Search Tree Test OK.\n");
}

int main(void)
{
    BinarySearchTreeTest();

    return 0;
}
