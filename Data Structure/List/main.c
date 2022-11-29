#include "List.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

char str[64] = {0};

void Visit(list_data_t n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

void ListTest(void)
{
    list_t *list1 = List_Create();
    assert(List_Size(list1) == 0);
    assert(List_IsEmpty(list1) == true);

    list_data_t arr[] = {1, 2, 3, 4};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arrSize; i++)
    {
        List_Insert(list1, i, arr[i]);
        assert(List_At(list1, i) == i + 1);
    }
    assert(List_Size(list1) == 4);
    assert(List_IsEmpty(list1) == false);

    List_Traverse(list1, Visit);
    assert(strcmp(str, "1 2 3 4 ") == 0);
    memset(str, 0, sizeof(str));

    List_Reverse(list1);
    List_Traverse(list1, Visit);
    assert(strcmp(str, "4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    list_t *list2 = List_Create();
    list_data_t arr2[] = {233, 666, 888, 999};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < arr2Size; i++)
    {
        List_Insert(list2, i, arr2[i]);
    }

    for (int i = 0; i < arr2Size; ++i)
    {
        List_Insert(list1, i, List_At(list2, i));
    }
    List_Traverse(list1, Visit);
    assert(strcmp(str, "233 666 888 999 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    assert(List_Size(list1) == 8);
    assert(List_IsEmpty(list1) == false);

    assert(List_Find(list1, 233) == 0);
    assert(List_Find(list1, 999) == 3);
    assert(List_Find(list1, 1) == 7);
    assert(List_Find(list1, 0) == -1);

    int length = List_Size(list1);
    for (int i = 0; i < length; i++)
    {
        List_Delete(list1, 0);
    }
    assert(List_Size(list1) == 0);
    assert(List_IsEmpty(list1) == true);

    List_Destroy(list1);
    List_Destroy(list2);

    printf("List Test OK.\n");
}

int main(void)
{
    ListTest();

    return 0;
}
