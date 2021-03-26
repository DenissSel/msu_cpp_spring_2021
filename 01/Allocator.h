#pragma once

#include <iostream>
class Allocator
{
    private:
        int offset = 0, flag = 0;
        char *buf = nullptr;
        size_t rest_size = 0, whole_size = 0;
    
    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        ~Allocator();
};

