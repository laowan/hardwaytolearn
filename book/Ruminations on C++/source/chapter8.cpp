#include <iostream>
#include <string>
using namespace std;

class Expr_node
{
    friend ostream& operator<< (ostream&, const Expr_node&);
protected:
    virtual void print(ostream&) const = 0;
    virtual ~Expr_node() {}
};

ostream& operator<<(ostream& o, const Expr_node& e)
{
    e.print(o);
    return o;
}

class Int_node : public Expr_node
{
    friend class Expr;
    int n;
    Int_node(int k) : n(k) {}
    void print(ostream& o) const { o << n; }
};

class Unary_node : public Expr_node
{
    friend class Expr;
    string op;
    Expr_node* opnd;
    Unary_node(const string& a, Expr_node* b) : op(a), opnd(b) {}
    void print(ostream& o) const { o << "(" << op << *opnd << ")"; }
};

class Binary_node : public Expr_node
{
    friend class Expr;
    string op;
    Expr_node* left;
    Expr_node* right;
    Binary_node(const string& a, Expr_node* b, Expr_node* c)
        : op(a), left(b), right(c) {}
    void print(ostream& o) const
    {
        o << "(" << *left << op << *right << ")";
    }
};

class Expr
{
    friend ostream& operator<<(ostream&, const Expr&);
    Expr_node* p;
public:
    Expr(int n) { p = new Int_node(n); }
    Expr(const string& op, Expr t) { p = new Unary_node(op, t.p); }
    Expr(const string& op, Expr left, Expr right) { p = new Binary_node(op, left.p, right.p); }
};

ostream& operator<<(ostream& o, const Expr& e)
{
    o << *(e.p);
    return o;
}

void func_chapter_8()
{
    Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    cout << t;
}