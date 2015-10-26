template<class T> class Array;
template<class T> class Ptr_to_const;
template<class T> class Pointer;

template<class T>
class Array_data
{
    friend class Array<T>;
    friend class Ptr_to_const<T>;
    friend class Pointer<T>;

    Array_data(unsigned int size = 0) :
        data(new T[size]), sz(size), use(1) {}
    ~Array_data() { delete[]data; }

    const T& operator[](unsigned int n) const
    {
        if (n >= sz)
            throw "out of range";
        return data[n];
    }

    T& operator[](unsigned int n)
    {
        if (n >= sz)
            throw "out of range";
        return data[n];
    }

    Array_data(const Array_data&);
    Array_data& operator=(const Array_data&);

    T* data;
    unsigned int sz;
    int use;
};

template<class T>
class Array
{
    friend class Pointer<T>;
    friend class Ptr_to_const<T>;
public:
    Array(unsigned int size) :
        data(new Array_data<T>(size)) {}

    ~Array()
    {
        if (--data->use == 0)
            delete data;
    }

    const T& operator[](unsigned int n) const
    {
        return (*data)[n];
    }

    T& operator[](unsigned int n)
    {
        return (*data)[n];
    }

private:
    Array(const Array&);
    Array& operator=(const Array&);
    Array_data<T>* data;
};

template<class T>
class Ptr_to_const
{
public:
    Ptr_to_const(const Array<T>& a, unsigned int n = 0) :
        ap(a.data), sub(n)
    {
        ++ap->use;
    }

    Ptr_to_const() : ap(0), sub(0) {}

    Ptr_to_const(const Ptr_to_const<T>& p) :
        ap(p.ap), sub(p.sub)
    {
        if (ap)
            ++ap->use;
    }

    ~Ptr_to_const()
    {
        if (ap && --ap->use == 0)
            delete ap;
    }

    Ptr_to_const& operator=(const Ptr_to_const<T>& p)
    {
        if (p.ap)
            ++p.ap->use;

        if (ap && --ap->use == 0)
            delete ap;

        ap = p.ap;
        sub = p.sub;
        return *this;
    }

    const T& operator*() const
    {
        if (ap == 0)
            throw "unbound";
        return (*ap)[sub];
    }

    //private:
    Array_data<T>* ap;
    unsigned int sub;
};

template<class T>
class Pointer : public Ptr_to_const<T>
{
public:
    Pointer(Array<T>& a, unsigned int n = 0) :
        Ptr_to_const<T>(a, n)
    {
        }

    Pointer() {}

    T& operator*() const
    {
        if (ap == 0)
            throw "unbound";
        return (*ap)[sub];
    }
};
