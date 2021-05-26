#include <iostream>

void printIntArray(int a[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        std::cout << a[i];
        if (i != sz - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void swapInt(int a[], int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}