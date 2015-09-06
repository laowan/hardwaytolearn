#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

size_t substr_count(const string &str, char a, char b)
{
    size_t cnt = 0;
    string::const_iterator it = str.begin();
    while(it != str.end())
    {
        if (*it++ == a)
        {
            if (it != str.end() && *it == b)
                cnt++;
        }
    }
    return cnt;
}

void f_5_12()
{
    cout << substr_count("xabaacbaxabb", 'a', 'b');
}