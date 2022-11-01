#include "MaxHeap.h"
#include <assert.h>

void MaxHeapTest(void)
{
    heap_t *heap = MaxHeap_Create();
    assert(MaxHeap_IsFull(heap) == false);
    assert(MaxHeap_IsEmpty(heap) == true);

    MaxHeap_Insert(heap, 1);
    MaxHeap_Insert(heap, 2);
    MaxHeap_Insert(heap, 4);
    MaxHeap_Insert(heap, 3);
    MaxHeap_Insert(heap, 9);
    MaxHeap_Insert(heap, 0);
    assert(MaxHeap_IsFull(heap) == false);
    assert(MaxHeap_IsEmpty(heap) == false);

    assert(MaxHeap_Delete(heap) == 9);
    assert(MaxHeap_Delete(heap) == 4);
    assert(MaxHeap_Delete(heap) == 3);
    assert(MaxHeap_Delete(heap) == 2);
    assert(MaxHeap_Delete(heap) == 1);
    assert(MaxHeap_Delete(heap) == 0);
    assert(MaxHeap_IsFull(heap) == false);
    assert(MaxHeap_IsEmpty(heap) == true);

    MaxHeap_Destroy(heap);
    heap = NULL;

    printf("Max Heap Test OK.\n");
}
int main(void)
{
    MaxHeapTest();

    return 0;
}
