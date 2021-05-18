#include <iostream>
#include "Allocator.h"
#include "test.h"
#include <cassert>

void allocTest() 
{
    Allocator a;
    char *b, *c, *d;
    a.makeAllocator(10);
    b = a.alloc(7);
    c = a.alloc(3);
    assert(b != nullptr);
    assert(c != nullptr);
    d = a.alloc(4);
    assert(d == nullptr);
}
void resetTest()
{
    Allocator a;
    char *b, *c, *d;
    a.makeAllocator(10);
    b = a.alloc(7);
    c = a.alloc(3);
    assert(b != nullptr);
    assert(c != nullptr);
    a.reset();
    d = a.alloc(4);
    assert(d != nullptr);
}
void doubleMakeAllocTest()
{
    Allocator a;
    char *b, *c, *d;
    a.makeAllocator(10);
    b = a.alloc(7);
    c = a.alloc(3);
    assert(b != nullptr);
    assert(c != nullptr);
    a.makeAllocator(15);
    d = a.alloc(15);
    assert(d != nullptr);
}
void allocBeforeMakeAllocator()
{
    Allocator a;
    char *b;
    b = a.alloc(15);
    assert(b == nullptr);
}
int main()
{
    Allocator *a;
    a = new Allocator[5];

    a[2].alloc(15);
    allocTest();
    resetTest();
    doubleMakeAllocTest();
    allocBeforeMakeAllocator();
    std::cout << "Success\n";
    return 0;
}