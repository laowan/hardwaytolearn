#include <iostream>

#include <Array.h>

void func_chapter_13()
{
    Array<int>* ap = new Array<int>(10);
    Pointer<int> p(*ap, 5);
    delete ap;
    *p = 42;
}
