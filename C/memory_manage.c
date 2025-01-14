#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024       // 内存堆大小
static char heap[HEAP_SIZE]; // 内存堆空间

struct block // 堆中块的结构体
{
    unsigned int size;        // 块的大小
    void* buf;                // 有效载荷
    struct block *pre, *next; // 前驱和后继，用双向链表实现堆
    int used;                 // 表明此块使用与否
};

#define HEAD_SIZE (sizeof(struct block*))

void memory_init()
{
    struct block* p = (struct block*)heap;
    p->size = sizeof(heap) - HEAD_SIZE;
    p->buf = (char*)p + HEAD_SIZE; // p should be cast to char*
    p->pre = NULL;
    p->next = NULL;
    p->used = 0;
}

void memory_pirnt()
{
    struct block* p = (struct block*)heap;
    while (p != NULL)
    {
        printf("addr: 0x%08X, size: %u, used: %s\n", (unsigned int)((char*)(p->buf) - heap), p->size, p->used ? "yes" : "no");
        p = p->next;
    }
    printf("\n");
}

void* memory_alloc(unsigned int size)
{
    struct block* p = (struct block*)heap;
    while (!((p != NULL) && (p->size - size > HEAD_SIZE) && (p->used == 0)))
    {
        p = p->next;
    }

    if (p == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        return NULL;
    }

    struct block* rest = (struct block*)((char*)(p->buf) + size);
    rest->buf = (char*)rest + HEAD_SIZE;
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
    p->used = 1;

    return p->buf;
}

void memory_free(void* mem)
{
    // 堆增长的方式是向高地址增长，要找到块的首地址就的减去块头的大小
    struct block* actual = (struct block*)((char*)mem - HEAD_SIZE);
    if (mem == NULL || 0 == actual->used)
    {
        fprintf(stderr, "ERROR: Memory free failed.\n");
        return;
    }

    // 合并
    actual->used = 0;
    struct block* tmp;
    if (actual->next && actual->next->used == 0)
    {
        actual->size += actual->next->size + HEAD_SIZE;
        tmp = actual->next->next;
        actual->next = tmp;
        if (tmp != NULL)
        {
            tmp->pre = actual;
        }
    }
    if (actual->pre && actual->pre->used == 0)
    {
        actual->pre->size += actual->size + HEAD_SIZE;
        actual->pre->next = actual->next;
        if (actual->next != NULL)
        {
            actual->next->pre = actual->pre;
        }
    }
}

int main()
{
    memory_init();
    memory_pirnt();

    int* a = (int*)memory_alloc(sizeof(int) * 100);
    memory_pirnt();

    char* b = (char*)memory_alloc(sizeof(char) * 100);
    memory_pirnt();

    memory_free(a);
    memory_free(b);

    memory_pirnt();

    return 0;
}
