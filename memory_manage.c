#include <stdio.h>
#include <stdlib.h>

#define HEAD_SIZE (sizeof(block_t))

char buf[1024]; //模拟内存堆

typedef struct block *block_t;

struct block //堆中块的结构体
{
    size_t size;       //块的大小
    void *buf;         //有效的载荷
    block_t pre, next; //前驱和后继，用双向链表实现堆
    int used;          //表明此块空闲与否
};

void InitMemory()
{
    block_t p = (block_t)buf;
    p->size = sizeof(buf) - HEAD_SIZE;
    p->buf = (char *)p + HEAD_SIZE; //p should be cast to char*
    p->pre = p->next = NULL;
    p->used = 0;
}

void PirntMemory()
{
    block_t p = (block_t)buf;
    while (p)
    {
        printf("addr: %x, size: %d, used: %s\n", (char *)(p->buf) - buf, p->size, p->used ? "yes" : "no");
        p = p->next;
    }
    printf("\n");
}

void *MemAlloc(size_t size)
{
    block_t p = (block_t)buf;
    while (!((p != NULL) && (p->size - size > HEAD_SIZE) && (p->used == 0)))
    {
        p = p->next;
    }
    if (p == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        return NULL;
    }
    else
    {
        block_t rest = (block_t)((char *)(p->buf) + size);
        rest->buf = (char *)rest + HEAD_SIZE;
        rest->size = p->size - size - HEAD_SIZE;
        rest->next = p->next;
        if (p->next)
        {
            p->next->pre = rest;
        }
        p->next = rest;
        rest->pre = p;
        rest->used = 0;
        p->size = size;
    }
    p->used = 1;
    return p->buf;
}

void MemFree(void *mem)
{
    block_t actual = (block_t)((char *)mem - HEAD_SIZE);
    //堆增长的方式是向高地址增长，要找到块的首地址就的减去块头的大小
    if (!mem || 0 == actual->used)
    {
        fprintf(stderr, "ERROR: Memory free failed.\n");
        return;
    }
    actual->used = 0;
    block_t tmp;
    if (actual->next && actual->next->used == 0)
    { //合并
        actual->size += actual->next->size + HEAD_SIZE;
        tmp = actual->next->next;
        actual->next = tmp;
        if (tmp)
        {
            tmp->pre = actual;
        }
    }
    if (actual->pre && actual->pre->used == 0)
    {
        actual->pre->size += actual->size + HEAD_SIZE;
        actual->pre->next = actual->next;
        if (actual->next)
        {
            actual->next->pre = actual->pre;
        }
    }
    return;
}

int main()
{
    InitMemory();
    PirntMemory();

    int *a = (int *)MemAlloc(sizeof(int) * 100);
    PirntMemory();

    char *b = (char *)MemAlloc(sizeof(char) * 100);
    PirntMemory();

    MemFree(a);
    MemFree(b);
    PirntMemory();

    return 0;
}