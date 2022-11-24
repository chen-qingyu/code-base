#include "Stack.h"
#include <assert.h>

void StackTest(void)
{
    stack_t *stack = Stack_Create();
    assert(Stack_Size(stack) == 0);
    assert(Stack_IsEmpty(stack) == true);

    stack_data_t arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arrSize; i++)
    {
        Stack_Push(stack, arr[i]);
    }
    assert(Stack_Size(stack) == 5);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_Top(stack) == 5);

    for (int i = 0; i < arrSize; i++)
    {
        assert(Stack_Pop(stack) == arr[arrSize - i - 1]);
    }
    assert(Stack_IsEmpty(stack) == true);

    Stack_Push(stack, 233);
    assert(Stack_Size(stack) == 1);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_Top(stack) == 233);

    Stack_Destroy(stack);
    stack = NULL;

    printf("Stack Test OK.\n");
}

int main(void)
{
    StackTest();

    return 0;
}
