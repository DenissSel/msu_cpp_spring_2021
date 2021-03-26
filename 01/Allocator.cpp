#include "Allocator.h"
#include <cassert>

void Allocator::makeAllocator(size_t maxSize)
{
    if (flag == 1)
    {
        delete[] buf;
        offset = 0;
    }
    buf = new char [maxSize];
    rest_size = maxSize;
    whole_size = maxSize;
    flag = 1;
}
char*  Allocator::alloc(size_t size)
{
    if (rest_size < size)
    {
        return nullptr;
    }
    rest_size -= size;
    offset += size;
    return (buf+offset-size);
            
}
void Allocator::reset()
{
    offset = 0;
    rest_size = whole_size;
}
Allocator::~Allocator()
{
    delete[] buf;
}
