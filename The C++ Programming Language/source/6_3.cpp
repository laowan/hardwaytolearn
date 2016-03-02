#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Stat
{
    Stat() : sum(0.0), count(0) {}
    double sum;
    int count;
};

typedef std::map<std::string, Stat> Data;

void collect_data(Data& stats)
{
    string name;
    while (cin >> name)
    {
        double value;
        cin >> value;
        stats[name].sum += value;
        stats[name].count += 1;
    }
}

void print_stats(Data& stats)
{
    double global_sum = 0.0;
    int global_count = 0;

    for (Data::iterator p = stats.begin(); p != stats.end(); p++)
    {
        cout << (*p).first
             << ": sum = " << (*p).second.sum
             << ", mean = " << (*p).second.sum / (*p).second.count
             << endl;
        global_sum += (*p).second.sum;
        global_count += (*p).second.count;
    }

    cout << "global sum: " << global_sum 
         << ", global mean: " << global_sum/global_count
         << endl;

}

void f_6_3()
{
    Data stats;
    collect_data(stats);
    print_stats(stats);
}