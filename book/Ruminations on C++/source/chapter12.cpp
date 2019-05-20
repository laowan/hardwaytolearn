#include <iostream>

template<class T>
class Array12
{
public:
    Array12() : data(0), sz(0) {}
    Array12(unsigned int size) : sz(size), data(new T[size]) {}
    ~Array12() { delete[] data; }

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
    Array12(const Array12&);
    Array12& operator=(const Array12&);
};

void func_chapter_12()
{
    unsigned int N = 10;
    Array12<int> x(N);
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