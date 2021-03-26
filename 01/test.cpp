#include <iostream>
#include "Allocator.h"
#include "test.h"


int allocTest() 
{
    Allocator a;
    char *b, *c, *d;
    a.makeAllocator(10);
    b = a.alloc(7);
    c = a.alloc(3);
    if (b == nullptr) return 1;
    if (c == nullptr) return 1;
    d = a.alloc(4);
    if (d != nullptr) return 1;
    return 0;
}
int resetTest()
{
    Allocator a;
    char *b, *c, *d;
    a.makeAllocator(10);
    b = a.alloc(7);
    c = a.alloc(3);
    if (b == nullptr) return 1;
    if (c == nullptr) return 1;
    a.reset();
    d = a.alloc(4);
    if (d == nullptr) return 1;
    return 0;
}

int main()
{
    if (allocTest() != 0) 
    {
        std::cout << "allocTest failed\n";
        return 1;
    }
    if (resetTest() != 0)
    {
        std::cout << "resetTest failed\n";
        return 1;
    }
    std::cout << "Success\n";
    return 0;
}