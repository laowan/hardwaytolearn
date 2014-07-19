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

int main()
{
    int a = 1, b = 2;
    cout << "a=" << a <<",b=" << b << endl;
    swap_ptr(&a, &b);
    cout << "a=" << a <<",b=" << b << endl;
    swap_ref(a, b);
    cout << "a=" << a <<",b=" << b << endl;
}