#include <iostream>
using namespace std;

class Picture
{
public:
    Picture();
    Picture(const char* const*, int);
    ~Picture();

    Picture(const Picture&);
    Picture& operator=(const Picture&);

    char& position(int row, int col)
    {
        return data[row * width + col];
    }

    char position(int row, int col) const
    {
        return data[row * width + col];
    }

    int max(int m, int n);
    void init(int h, int w);
    void copyblock(int row, int col, const Picture& p);

private:
    char* data;
    int height, width;

    friend ostream& operator<<(ostream& o, const Picture& p);
    friend Picture frame(const Picture& p);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);
};

Picture::Picture() : height(0), width(0), data(0)
{}

Picture::Picture(const char* const* a, int n)
{
    int w = 0;
    
    for (int i = 0; i < n; i++)
        w = max(w, strlen(a[i]));

    init(n, w);

    for (int i = 0; i < n; i++)
    {
        const char* line = a[i];
        int len = strlen(line);
        int j = 0;
        while (j < len)
        {
            position(i, j) = line[j];
            j++;
        }

        while (j < width)
        {
            position(i, j) = ' ';
            j++;
        }
    }
}

Picture::~Picture()
{
    if (data) delete[] data;
}

Picture::Picture(const Picture& pic)
{
    height = pic.height;
    width = pic.width;
    data = new char[height * width];

    for (int i = 0; i < height*width; i++)
        data[i] = pic.data[i];
}

Picture& Picture::operator=(const Picture& pic)
{
    if (this != &pic)
    {
        if (data) delete[] data;

        init(pic.height, pic.width);

        for (int i = 0; i < height*width; i++)
            data[i] = pic.data[i];
    }
    return *this;
}

int Picture::max(int m, int n)
{
    return m > n ? m : n;
}

void Picture::init(int h, int w)
{
    height = h;
    width = w;
    data = new char[height * width];

    for (int i = 0; i < height*width; i++)
        data[i] = ' ';
}

void Picture::copyblock(int row, int col, const Picture& p)
{
    for (int i = 0; i < p.height; i++)
        for (int j = 0; j < p.width; j++)
            position(i + row, j + col) = p.position(i, j);
}


ostream& operator<<(ostream& o, const Picture& p)
{
    for (int i = 0; i < p.height; i++)
    {
        for (int j = 0; j < p.width; j++)
            o << p.position(i, j);
        o << endl;
    }
    return o;
}

Picture frame(const Picture& p)
{
    Picture r;
    r.init(p.height + 2, p.width + 2);

    for (int i = 1; i < r.height; i++)
    {
        r.position(i, 0) = '|';
        r.position(i, r.width - 1) = '|';
    }

    for (int i = 1; i < r.width; i++)
    {
        r.position(0, i) = '-';
        r.position(r.height - 1, i) = '-';
    }

    r.position(0, 0) = '+';
    r.position(0, r.width - 1) = '+';
    r.position(r.height - 1, 0) = '+';
    r.position(r.height - 1, r.width - 1) = '+';

    r.copyblock(1, 1, p);

    return r;
}

Picture operator&(const Picture& p, const Picture& q)
{
    Picture r;
    r.init(p.height + q.height, r.max(p.width, q.width));

    r.copyblock(0, 0, p);
    r.copyblock(p.height, 0, q);

    return r;
}

Picture operator|(const Picture& p, const Picture& q)
{
    Picture r;
    r.init(r.max(p.height, q.height), p.width + q.width);

    r.copyblock(0, 0, p);
    r.copyblock(0, p.width, q);

    return r;
}

void func_chapter_9()
{
    char* init[] = { "Paris", "in the", "Spring" };
    Picture p(init, 3);
    cout << p << endl;

    Picture q = p;
    cout << q << endl;
    
    p = frame(q);
    cout << p << endl;

    Picture r = q & p;
    cout << r << endl;

    Picture s = p | r;
    cout << s << endl;

}