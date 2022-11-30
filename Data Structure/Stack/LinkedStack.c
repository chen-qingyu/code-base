#include "LinkedStack.h"

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

stack_t *LinkedStack_Create(void)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    check_pointer(stack);

    stack->top = NULL;
    stack->count = 0;

    return stack;
}

void LinkedStack_Destroy(stack_t *stack)
{
    while (stack->top)
    {
        struct node *current = stack->top->next;
        free(stack->top);
        stack->top = current;
    }
    free(stack);
}

int LinkedStack_Size(const stack_t *stack)
{
    return stack->count;
}

bool LinkedStack_IsEmpty(const stack_t *stack)
{
    return stack->count == 0;
}

void LinkedStack_Push(stack_t *stack, stack_data_t data)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    check_pointer(node);

    node->data = data;
    node->next = stack->top;
    stack->top = node;

    stack->count++;
}

stack_data_t LinkedStack_Pop(stack_t *stack)
{
    if (LinkedStack_IsEmpty(stack))
    {
        fprintf(stderr, "ERROR: The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *node = stack->top;
    stack->top = node->next;
    stack_data_t data = node->data;
    free(node);

    stack->count--;

    return data;
}

stack_data_t LinkedStack_Top(const stack_t *stack)
{
    if (LinkedStack_IsEmpty(stack))
    {
        fprintf(stderr, "ERROR: The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->top->data;
}
