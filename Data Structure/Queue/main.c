#include "Queue.h"

#include <assert.h>
#include <stdio.h>

void QueueTest(void)
{
    queue_t *queue = Queue_Create();
    assert(Queue_Size(queue) == 0);
    assert(Queue_IsEmpty(queue) == true);

    queue_data_t arr[] = {1, 2, 3, 4};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arrSize; i++)
    {
        Queue_Enqueue(queue, arr[i]);
    }
    assert(Queue_Size(queue) == 4);
    assert(Queue_IsEmpty(queue) == false);

    for (int i = 0; i < arrSize; i++)
    {
        assert(Queue_Dequeue(queue) == i + 1);
    }
    assert(Queue_Size(queue) == 0);
    assert(Queue_IsEmpty(queue) == true);

    Queue_Destroy(queue);

    printf("Queue Test OK.\n");
}

int main(void)
{
    QueueTest();

    return 0;
}
