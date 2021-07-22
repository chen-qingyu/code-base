#include <stdio.h>
#include <stdlib.h>

struct stack
{
    char data[256];
    int top;
};

void Push(struct stack *stack, char data)
{
    stack->data[++(stack->top)] = data;
}

char Pop(struct stack *stack)
{
    return stack->data[(stack->top)--];
}

char Top(const struct stack *stack)
{
    return stack->data[stack->top];
}

int GetLength(const struct stack *stack)
{
    return stack->top + 1;
}

int IsEmpty(const struct stack *stack)
{
    return GetLength(stack) == 0;
}

int main(void)
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->top = -1;

    char s[256] = {0};
    scanf("%s", s);

    int flag = 1;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '(' || s[i] == '[')
        {
            Push(stack, s[i]);
        }
        else if (s[i] == ')' || s[i] == ']')
        {
            if (!IsEmpty(stack) && ((Top(stack) == '(' && s[i] == ')') || (Top(stack) == '[' && s[i] == ']')))
            {
                Pop(stack);
            }
            else
            {
                flag = 0;
            }
        }
    }

    if (flag == 0 || !IsEmpty(stack))
    {
        printf("Wrong\n");
    }
    else
    {
        printf("OK\n");
    }

    free(stack);

    return 0;
}
