#include <iostream>
#include <string>
using namespace std;

void print(string *month, int size)
{
    for (int i = 0; i < size; i++)
        cout << month[i] << endl;
}

void f_5_10()
{
    string month[12] = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    for (int i = 0; i < 12; i++)
        cout << month[i] << endl;
    
    print(month, 12);
}