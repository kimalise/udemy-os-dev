#include "memory.h"
#include <stdint.h>

void* memset(void* addr, int v, size_t size)
{
    char* p = (char* ) addr;
    for (size_t i = 0; i < size; i++)
    {
        p[i] = (char) v;
    }
    return addr;
}