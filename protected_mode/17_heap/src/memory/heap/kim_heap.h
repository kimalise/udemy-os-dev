#ifndef KIM_HEAP_H
#define KIM_HEAP_H
#include <stdint.h>
#include <stddef.h>

// 已分配的内存块
struct header_t {
    int size;
    int magic;
};

// 空闲块节点
struct node_t {
    int size;
    struct node_t* next;
};

void kim_heap_init();
void * kim_malloc(size_t size);
void kim_free(void* ptr);

#endif