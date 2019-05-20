#include <iostream>
using namespace std;

struct Date{
    int day;
    int month;
    int year;
};

std::istream& operator>>(std::istream &input, Date &d)
{
    const int bufsize = 6;
    char buffer[bufsize];
    input.getline(buffer, bufsize, '/');
    d.month = atoi(buffer);
    input.getline(buffer, bufsize, '/');
    d.day = atoi(buffer);
    input >> d.year;
    return input;
}

std::ostream& operator<<(std::ostream &output, Date &d)
{
    output << d.month << '/' << d.day << '/' << d.year;
    return output;
}

Date& init(Date &d, int day, int month, int year)
{
    d.day = day;
    d.month = month;
    d.year = year;
    return d;
}

void f_5_13()
{
    Date d;
    init(d, 1, 11, 1988);
    cout << d;

    cin >> d;
    cout << d;
}