class ClusterItem;
class Cluster
{
    friend class ClusterItem;
public:
    Cluster();
    ~Cluster();
private:
    ClusterItem* head;
    Cluster(const Cluster&);
    Cluster& operator=(const Cluster&);
};

static Cluster* cp = 0;
//-------------------------------------------------------------
class ClusterItem
{
    friend class Cluster;
public:
    void* operator new(size_t, Cluster&);
    ClusterItem();;
protected:
    virtual ~ClusterItem() {}
private:
    ClusterItem* next;
    void* operator new(size_t);
    ClusterItem(const ClusterItem&);
    ClusterItem& operator=(const ClusterItem&);
};

//-------------------------------------------------------------
Cluster::Cluster() : head(0)
{

}

Cluster::~Cluster()
{
    while (head)
    {
        ClusterItem* next = head->next;
        delete head;
        head = next;
    }
}

//--------------------------------------------------------------
ClusterItem::ClusterItem()
{
    next = cp->head;
    cp->head = this;
}

void* ClusterItem::operator new(size_t n, Cluster& c)
{
    cp = &c;
    return ::operator new(n);
}


void func_chapter_29()
{

}
