#include <iostream>
using namespace std;

struct Pair 
{
    char month;
    char days;
};

struct Month
{
    const char *name;
    int length;
};

void f_5_7()
{

char month[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
char days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

for (int i = 0; i < 12; i++)
    cout << (int)month[i] << "  " << (int)days[i] << endl;


struct Pair md[12];
for (int i = 0; i < 12; i++)
    {
    md[i].month = month[i];
    md[i].days = days[i];
    }

for (int i = 0; i < 12; i++)
    cout << (int)md[i].month << "  " << (int)md[i].days << endl;

const Month mh[12]
    ={{"January",31}, {"February",28}, {"March",31},
      {"April",30}, {"May",31}, {"June",30},
      {"July", 31}, {"August", 31}, {"September",30},
      {"October",31}, {"November",30}, {"December",31}};

for (int i = 0; i < 12; i++)
    cout << mh[i].name << "  " << mh[i].length << endl;

}