#include <iostream>
using namespace std;

class Obj_trace
{
public:
    Obj_trace() : ct(++count)
    {
        cout << "object " << ct << " constructed" << endl;
    }
    ~Obj_trace()
    {
        cout << "object " << ct << " destroyed" << endl;
    }
    Obj_trace(const Obj_trace&) : ct(++count)
    {
        cout << "object " << ct << " constructed" << endl;
    }

    Obj_trace& operator=(const Obj_trace&)
    {
        return *this;
    }

private:
    static int count;
    int ct;
};

int Obj_trace::count = 0;

template<class T>
class Arr
{
public:
    Arr(int n = 0) : data(new T[n]), sz(n) {}
    ~Arr() { delete[] data; }
    Arr(const Arr&);
    Arr& operator=(const Arr& a);
    T& operator[](unsigned n) { return data[n]; }
private:
    T* data;
    int sz;
};

template<class T>
Arr<T>::Arr(const Arr<T>& a) : data(new T[a.sz]), sz(a.sz)
{
    for (int i = 0; i < sz; i++)
        data[i] = a.data[i];
}

template<class T>
Arr<T>& Arr<T>::operator=(const Arr<T>& a)
{
    delete[] data;
    sz = a.sz;
    data = new T[sz];
    for (int i = 0; i < sz; i++)
        data[i] = a.data[i];
    return *this;
}

void func_chapter_28()
{
    {
        Arr<Obj_trace> x(3);
        Arr<Obj_trace> y = x;
        x = y;
    }
}
