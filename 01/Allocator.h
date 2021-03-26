#pragma once

#include <iostream>
class Allocator
{
    private:
        int offset = 0, flag = 0;
        char *buf;
        size_t rest_size, whole_size;
    
    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        ~Allocator();
};

