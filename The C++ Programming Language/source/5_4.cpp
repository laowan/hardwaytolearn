#include <iostream>
using namespace std;


void swap_ptr(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_ref(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void f_5_4()
{
    int a = 1, b = 2;
    cout << "a=" << a <<",b=" << b << endl;
    swap_ptr(&a, &b);
    cout << "a=" << a <<",b=" << b << endl;
    swap_ref(a, b);
    cout << "a=" << a <<",b=" << b << endl;
}