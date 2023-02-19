#include "kim_heap.h"
// #include "config.h"

#define KimOS_HEAP_SIZE_BYTES 4096 // for test
#define KimOS_HEAP_ADDRESS 0x01000000

struct node_t* head;

void kim_heap_init()
{
    // head = (node_t*) KimOS_HEAP_ADDRESS;
    head = (struct node_t* ) KimOS_HEAP_ADDRESS;
    head->size = KimOS_HEAP_SIZE_BYTES - sizeof(struct node_t);
    head->next = 0x00;
}

void* kim_malloc(size_t size)
{
    struct node_t* prev = 0; // previous node
    struct node_t* p = head; // current node
    void* ptr = 0;

    while (p)
    {
        if (p->size >= size)
        {
            if (p->size == size)
            {
                if (prev)
                {
                    prev->next = p->next;
                }

                if (p == head)
                {
                    head = p->next;
                }
                
            }
            else // 分割
            {
                struct node_t* new_node = (struct node_t*)(((void*)(p + 1)) + size);
                new_node->size = p->size - size - sizeof(struct node_t);
                new_node->next = p->next;

                if (prev)
                {
                    prev->next = new_node;
                }

                if (p == head)
                {
                    head = new_node;
                }
            }

            // 不管当前node是否需要分割，均需要执行以下代码
            struct header_t* h = (struct header_t*) p;
            h->size = size;
            h->magic = 1234567;
            ptr = h + 1;
           
            break;
        }

        prev = p;
        p = p->next;
        
    }
    
    return ptr;
}

void kim_free(void* ptr)
{
    struct node_t* p = ((struct node_t*) ptr) - 1; // p指向待释放空间的头部
    p->next = head;
    head = p;
    return;
}

