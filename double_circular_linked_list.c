#include <stdio.h>
#include <stdlib.h>

typedef struct double_list
{
    int data;
    struct double_list *pre;
    struct double_list *next;
} list;

typedef list *list_t;

list_t CreateList()
{
    list_t node = (list_t)malloc(sizeof(list));
    if (node == NULL)
    {
        fprintf(stderr, "ERROR: There was not enough memory.\n");
        exit(-2);
    }
    node->pre = node;
    node->next = node;
    return node;
}

void Insert(list_t head, int i, int data)
{
    list_t new = (list_t)malloc(sizeof(struct double_list));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: There was not enough memory.\n");
        exit(-2);
    }
    new->data = data;

    list_t tmp = head;
    for (int j = 0; j < i; j++)
    {
        tmp = tmp->next;
    }
    new->pre = tmp;
    new->next = tmp->next;
    tmp->next = new;
}

void Print(list_t head)
{
    printf("Now print the list elements:\n");
    list_t tmp = head->next;
    for (int i = 0; tmp != head; i++)
    {
        printf("%d: %d\n", i, tmp->data);
        tmp = tmp->next;
    }
    printf("That's all.\n");
}

void Delete(list_t head, int val)
{
    if (head == NULL)
    {
        fprintf(stderr, "The list is empty.\n");
        return;
    }
    list_t p = head;
    list_t q = head->next;
    while (p->next != head)
    {
        if (q->data == val)
        {
            if (q->next == head)
            {
                p->next = head;
                free(q);
            }
            q->next->pre = p;
            p->next = q->next;
        }
        p = p->next;
        q = q->next;
    }
    printf("Not found the data: %d\n", val);
}

int Find(list_t head, int val)
{
    if (head == NULL)
    {
        fprintf(stderr, "The list is empty.\n");
        return -1;
    }
    int index = 0;
    list_t p = head;
    while (p->next != head)
    {
        if (p->next->data == val)
        {
            return index;
        }
        index++;
        p = p->next;
    }
    return -1;
}

void Menu(void)
{
    printf("|=================1. Insert =================|\n");
    printf("|=================2. Print  =================|\n");
    printf("|=================3. Delete =================|\n");
    printf("|=================4. Find   =================|\n");
    printf("|=================0. Exit   =================|\n");
}

int main(void)
{
    list_t head = CreateList();
    int num;
    Menu();
    printf(">>> ");
    scanf("%d", &num);
    int val, idx;
    while (num)
    {
        switch (num)
        {
            case 1:
                printf("Please enter an index and an integer to insert:\n");
                scanf("%d %d", &idx, &val);
                Insert(head, idx, val);
                break;
            case 2:
                Print(head);
                break;
            case 3:
                printf("Please enter an integer to delete:\n");
                scanf("%d", &val);
                Delete(head, val);
                break;
            case 4:
                printf("Please enter an integer to find:\n");
                scanf("%d", &val);
                idx = Find(head, val);
                if (idx != -1)
                {
                    printf("%d at index %d\n", val, idx);
                }
                break;
        }
        printf(">>> ");
        scanf("%d", &num);
    }
    printf("Bye!\n");
    return 0;
}
