#include <iostream>

template<class T>
class Array
{
public:
    Array() : data(0), sz(0) {}
    Array(unsigned int size) : sz(size), data(new T[size]) {}
    ~Array() { delete[] data; }

    const T& operator[] (unsigned int n) const
    {
        if (n >= sz || !data)
            throw "out of range";
        return data[n];
    }

    T& operator[] (unsigned int n)
    {
        if (n >= sz || !data)
            throw "out of range";
        return data[n];
    }

    operator const T* () const
    {
        return data;
    }

    operator T*()
    {
        return data;
    }

private:
    T* data;
    unsigned int sz;
    Array(const Array&);
    Array& operator=(const Array&);
};

void func_chapter_12()
{
    unsigned int N = 10;
    Array<int> x(N);
    for (unsigned int i = 0; i < N; i++)
    {
        x[i] = 5;
    }

    for (unsigned int i = 0; i < N; i++)
    {
        std::cout << x[i] << std::endl;
    }

    int *p = x;
    int *q = x + N;
    while (p != q)
    {
        std::cout << *p++ << " ";
    }

    p = x;
}