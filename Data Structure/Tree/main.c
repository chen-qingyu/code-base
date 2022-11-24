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

    assert(Tree_Size(tree) == 0);
    assert(Tree_IsEmpty(tree) == true);

    Tree_Insert(tree, 3);
    Tree_Insert(tree, 1);
    Tree_Insert(tree, 2);
    Tree_Insert(tree, 4);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 5);
    Tree_Insert(tree, 1);

    assert(Tree_Size(tree) == 5);
    assert(Tree_IsEmpty(tree) == false);

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

    tree_data_t value = Tree_Find(tree, 2);
    assert(value == 2);
    value = Tree_Find(tree, 0);
    assert(value == TREE_NOT_FOUND);

    value = Tree_FindMin(tree);
    assert(value == 1);
    value = Tree_FindMax(tree);
    assert(value == 5);

    Tree_Delete(tree, 5);
    value = Tree_FindMax(tree);
    assert(value == 4);

    assert(Tree_Size(tree) == 4);
    assert(Tree_IsEmpty(tree) == false);

    Tree_Destroy(tree);
    tree = NULL;

    printf("Binary Search Tree Test OK.\n");
}

int main(void)
{
    BinarySearchTreeTest();

    return 0;
}
