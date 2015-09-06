#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void print(string str)
{
    cout << str << endl;
}

void f_5_11()
{
    vector<string> words;
    string word;
    while(1)
    {
        cin >> word;
        if (word == "Quit")
            break;
        if (words.end() == find(words.begin(), words.end(), word))
            words.push_back(word);
    }

    for_each(words.begin(), words.end(), print);

    sort(words.begin(), words.end());

    for_each(words.begin(), words.end(), print);

    cin >> word;
}