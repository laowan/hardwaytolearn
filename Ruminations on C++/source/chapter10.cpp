#include <iostream>
#include <string>

using namespace std;

static void pad(ostream& os, int x, int y)
{
    for (int i = x; i < y; i++)
        os << " ";
}

class P_Node;
class String_Pic;
class Picture1
{
    friend ostream& operator<<(ostream&, const Picture1&);
    friend Picture1 frame(const Picture1&);
    friend Picture1 operator&(const Picture1&, const Picture1&);
    friend Picture1 operator|(const Picture1&, const Picture1&);

    friend class P_Node;
    friend class String_Pic;
    friend class Frame_Pic;
    friend class VCat_Pic;
    friend class HCat_Pic;

public:
    Picture1(const char* const* str, int n);
    Picture1(const Picture1& orig);
    Picture1(P_Node* p_node) : p(p_node) {}
    ~Picture1();

    Picture1& operator=(const Picture1& orig);
private:
    int height() const;
    int width() const;
    void display(ostream& o, int x, int y) const;

private:
    P_Node* p;
};

class P_Node
{
    friend class Picture1;
protected:
    P_Node() : use(1) {}
    virtual ~P_Node() {}

    virtual int height() const = 0;
    virtual int width() const = 0;
    virtual void display(ostream &, int, int) const = 0;

    int max(int x, int y) const { return x > y ? x : y; }

protected:
    int use;
};

class String_Pic : public P_Node
{
    friend class Picture1;

    String_Pic(const char* const* p, int n)
    {
        data = new char*[n];
        size = n;
        for (int i = 0; i < n; i++)
        {
            data[i] = new char(strlen(p[i]) + 1);
            strcpy(data[i], p[i]);
        }
    }

    ~String_Pic()
    {
        for (int i = 0; i < size; i++)
            delete[] data[i];
        delete[] data;
    }

    int height() const
    {
        return size;
    }

    int width() const
    {
        int w = 0;
        for (int i = 0; i < size; i++)
        {
            w = max(w, strlen(data[i]));
        }
        return w;
    }

    void display(ostream& os, int row, int width) const
    {
        int start = 0;
        if (row >= 0 && row < height())
        {
            os << data[row];
            start = strlen(data[row]);
        }
        pad(os, start, width);
    }

private:
    char** data;
    int size;
};

class Frame_Pic : public P_Node
{
    friend class Picture1;
    friend Picture1 frame(const Picture1&);

    Frame_Pic(const Picture1& pic) : p(pic) {}
    int height() const
    {
        return p.height() + 2;
    }

    int width() const
    {
        return p.width() + 2;
    }

    void display(ostream& os, int row, int wd) const
    {
        if (row < 0 || row >= height())
        {
            pad(os, 0, wd);
        }
        else if (row == 0 || row == height() - 1)
        {
            os << "+";
            int i = p.width();
            while (--i >= 0) os << "-";
            os << "+";
        }
        else
        {
            os << "|";
            p.display(os, row - 1, p.width());
            os << "|";
        }

        pad(os, width(), wd);
    }

    Picture1 p;
};

class VCat_Pic : public P_Node
{
    friend class Picture1;
    friend Picture1 operator&(const Picture1&, const Picture1&);

    VCat_Pic(const Picture1& p, const Picture1& q) : top(p), bottom(q) {}

    int height() const
    {
        return top.height() + bottom.height();
    }

    int width() const
    {
        return max(top.width(), bottom.width());
    }

    void display(ostream& os, int row, int wd) const
    {
        if (row >= 0 && row < top.height())
            top.display(os, row, wd);
        else if (row < top.height() + bottom.height())
            bottom.display(os, row - top.height(), wd);
        else
            pad(os, 0, wd);
    }
    Picture1 top, bottom;
};

class HCat_Pic : public P_Node
{
    friend Picture1 operator|(const Picture1&, const Picture1&);
public:
    HCat_Pic(const Picture1& p, const Picture1& q) : left(p), right(q) {}

    int height() const
    {
        return max(left.height(), right.height());
    }

    int width() const
    {
        return left.width() + right.width();
    }

    void display(ostream& os, int row, int wd) const
    {
        left.display(os, row, left.width());
        right.display(os, row, right.width());
        pad(os, width(), wd);
    }

    Picture1 left, right;
};

Picture1::Picture1(const char* const* str, int n) : p(new String_Pic(str, n)) {}
Picture1::Picture1(const Picture1& orig) : p(orig.p) { orig.p->use++; }
Picture1::~Picture1()
{
    if (--p->use == 0)
        delete p;
}

Picture1& Picture1::operator=(const Picture1& orig)
{
    orig.p->use++;
    if (--p->use == 0)
        delete p;
    p = orig.p;
    return *this;
}

int Picture1::height() const { return p->height(); }
int Picture1::width() const { return p->width(); }
void Picture1::display(ostream& o, int x, int y) const { p->display(o, x, y); }

//----------------------------------------------------------------------------
Picture1 frame(const Picture1& pic)
{
    return new Frame_Pic(pic);
}

Picture1 operator&(const Picture1& p, const Picture1& q)
{
    return new VCat_Pic(p, q);
}

Picture1 operator|(const Picture1& p, const Picture1& q)
{
    return new HCat_Pic(p, q);
}

ostream& operator<<(ostream& os, const Picture1& pic)
{
    int ht = pic.height();
    for (int i = 0; i < ht; i++)
    {
        pic.display(os, i, 0);
        os << endl;
    }
    return os;
}

void func_chapter_10()
{
    char* init[] = { "Paris", "in the", "Spring" };
    Picture1 p(init, 3);
    cout << p << endl;

    Picture1 q = p;
    cout << q << endl;

    p = frame(q);
    cout << p << endl;

    Picture1 r = q & p;
    cout << r << endl;

    Picture1 s = p | r;
    cout << s << endl;

}
