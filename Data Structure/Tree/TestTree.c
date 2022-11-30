#include "BinarySearchTree.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

char str[64] = {0};

void Visit(tree_data_t n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

void TestBinarySearchTree()
{
    tree_t *tree = Tree_Create();

    assert(Tree_Size(tree) == 0);
    assert(Tree_IsEmpty(tree) == true);
    assert(Tree_Find(tree, 0) == TREE_NOT_FOUND);
    assert(Tree_FindMax(tree) == TREE_NOT_FOUND);
    assert(Tree_FindMin(tree) == TREE_NOT_FOUND);

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

    assert(Tree_Find(tree, 2) == 2);
    assert(Tree_Find(tree, 0) == TREE_NOT_FOUND);

    assert(Tree_FindMin(tree) == 1);
    assert(Tree_FindMax(tree) == 5);

    Tree_Delete(tree, 1);
    assert(Tree_FindMin(tree) == 2);

    Tree_Delete(tree, 5);
    assert(Tree_FindMax(tree) == 4);

    assert(Tree_Size(tree) == 3);
    assert(Tree_IsEmpty(tree) == false);

    Tree_Insert(tree, -1);
    assert(Tree_Size(tree) == 4);
    assert(Tree_Find(tree, -1) == -1);
    Tree_Delete(tree, -1);
    assert(Tree_Size(tree) == 3);
    assert(Tree_Find(tree, -1) == TREE_NOT_FOUND);

    Tree_Destroy(tree);

    printf("Binary Search Tree Test OK.\n");
}

int main(void)
{
    TestBinarySearchTree();

    return 0;
}
