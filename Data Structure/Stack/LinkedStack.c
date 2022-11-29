#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

struct node
{
    stack_data_t data;
    struct node *next;
};

struct stack
{
    int count;
    struct node *top;
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

    stack->top = NULL;
    stack->count = 0;

    return stack;
}

void Stack_Destroy(stack_t *stack)
{
    while (stack->top)
    {
        struct node *current = stack->top->next;
        free(stack->top);
        stack->top = current;
    }
    free(stack);
}

int Stack_Size(const stack_t *stack)
{
    return stack->count;
}

bool Stack_IsEmpty(const stack_t *stack)
{
    return stack->count == 0;
}

void Stack_Push(stack_t *stack, stack_data_t data)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    check_pointer(node);

    node->data = data;
    node->next = stack->top;
    stack->top = node;

    stack->count++;
}

stack_data_t Stack_Pop(stack_t *stack)
{
    if (Stack_IsEmpty(stack))
    {
        fprintf(stderr, "The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *node = stack->top;
    stack->top = node->next;
    stack_data_t data = node->data;
    free(node);

    stack->count--;

    return data;
}

stack_data_t Stack_Top(const stack_t *stack)
{
    if (Stack_IsEmpty(stack))
    {
        fprintf(stderr, "The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->top->data;
}
