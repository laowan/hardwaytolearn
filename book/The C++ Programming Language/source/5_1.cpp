#include <iostream>

void f_5_1()
{
    char ch = 'a';
    char *pch = &ch;
    
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    
    int (&pa)[10] = a;

    char str[10] = "hello";
    char *pstr = str;

    char **ppch = &pch;

    const int cint = 2;
    
    const int *pi = &cint;

    int i = 3;
    int *const p = &i;
}