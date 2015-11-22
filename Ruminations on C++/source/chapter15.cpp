
template <class T> class Seq;

template <class T>
class Seq_item
{
    friend class Seq<T>;

    int use;
    const T data;
    Seq_item* next;

    Seq_item(const T& t, Seq_item* s);
    Seq_item(const T& t) : use(1), data(t), next(0) {}
};

template <class T>
Seq_item<T>::Seq_item(const T& t, Seq_item<T>* s)
    : use(1), data(t), next(s)
{
    if (s)
        s->use++;
}


template <class T>
class Seq
{
public:
    Seq();
    Seq(const T&, const Seq&);
    Seq(const  Seq&);
    ~Seq();

    Seq& operator=(const Seq&);
    T hd() const;
    Seq tl() const;
    operator bool() const;
    Seq& insert(const T& t);

private:
    Seq(Seq_item<T>* s);
    void destory(Seq_item<T>*);

private:
    Seq_item<T>* item;
};

template <class T>
Seq<T>::Seq() : item(0) {}

template <class T>
Seq<T>::Seq(const T& t, const Seq<T>& s)
    : item(new Seq_item<T>(t, s.item))
{
}

template <class T>
Seq<T>::Seq(const Seq<T>& s) : item(s.item)
{
    if (item)
        item->use++;
}

template <class T>
Seq<T>::Seq(Seq_item<T>* s) : item(s)
{
    if (s)
        s->use++;
}

template <class T>
Seq<T>::~Seq()
{
    destory(item);
}

template <class T>
Seq<T>& Seq<T>::operator=(const Seq<T>& s)
{
    if (s.item)
        s.item->use++;
    destory(item);
    item = s.item;
    return *this;
}

template <class T>
void Seq<T>::destory(Seq_item<T>* item)
{
    while (item && --item->use == 0)
    {
        Seq_item<T>* next = item->next;
        delete item;
        item = next;
    }
}

template <class T>
Seq<T>::operator bool() const
{
    return item != 0;
}

template <class T>
T Seq<T>::hd() const
{
    if (item)
        return item->data;
    else
        throw "hd of an empty Seq";
}

template <class T>
Seq<T> Seq<T>::tl() const
{
    if (item)
        return Seq<T>(item->next);
    else
        throw "tl of an empty Seq";
}

template <class T>
Seq<T>& Seq<T>::insert(const T& t)
{
    Seq_item<T>* i = new Seq_item<T>(t, item);
    if (item)
        item->use--;
    item = i;
    return *this;
}

void func_chapter_15()
{
    Seq<int>* s = new Seq<int>();
    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    delete s;
}
