#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 100

struct stack
{
    stack_data_t data[STACK_CAPACITY];
    int top;
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

/*******************************
Interface functions implementation.
*******************************/

stack_t *Stack_Create(void)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    check_pointer(stack);

    stack->top = -1;

    return stack;
}

void Stack_Destroy(stack_t *stack)
{
    free(stack);
}

int Stack_Size(const stack_t *stack)
{
    return stack->top + 1;
}

bool Stack_IsEmpty(const stack_t *stack)
{
    return stack->top + 1 == 0;
}

void Stack_Push(stack_t *stack, stack_data_t data)
{
    if (Stack_Size(stack) == STACK_CAPACITY)
    {
        fprintf(stderr, "The stack is full.\n");
        return;
    }

    stack->data[++(stack->top)] = data;
}

stack_data_t Stack_Pop(stack_t *stack)
{
    if (Stack_IsEmpty(stack))
    {
        fprintf(stderr, "The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->data[(stack->top)--];
}

stack_data_t Stack_Top(const stack_t *stack)
{
    if (Stack_IsEmpty(stack))
    {
        fprintf(stderr, "The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->data[stack->top];
}
