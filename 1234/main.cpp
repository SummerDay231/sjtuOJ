#include <iostream>
using namespace std;

template<class T>
class MinHeap
{
private:
    int currentSize;
    T *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

public:
    MinHeap(int capacity=100);
    MinHeap(const T data[], int size);
    ~MinHeap();
    bool isEmpty() const;
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
    int find(T x) const;
    void decrease(int i, int v);
};

template<class T>
MinHeap<T>::MinHeap(int capacity)
{
    array = new T[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template<class T>
MinHeap<T>::~MinHeap()
{
    delete [] array;
}

template<class T>
bool MinHeap<T>::isEmpty() const
{
    return currentSize==0;
}

template<class T>
T MinHeap<T>::getHead() const
{
    return array[1];
}

template<class T>
void MinHeap<T>::enQueue(const T &x)
{
    if(currentSize==maxSize-1) doubleSpace();

    int hole = ++currentSize;
    for(; hole>1&&array[hole/2]>x; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template<class T>
T MinHeap<T>::deQueue()
{
    T minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template<class T>
void MinHeap<T>::percolateDown(int hole)
{
    int child;
    T tmp = array[hole];
    for(;hole*2<=currentSize; hole=child)
    {
        child = hole*2;
        if(child!=currentSize&&array[child+1]<array[child])
            child++;
        if(array[child]<tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template<class T>
void MinHeap<T>::doubleSpace()
{
    T *tmp = array;
    maxSize *= 2;
    array = new T[maxSize];
    for(int i=1; i<=currentSize; ++i)
        array[i] = tmp[i];
    delete [] tmp;
}

template<class T>
int MinHeap<T>::find(T x) const
{
    T minValue;
    int pos, i;
    for(i=1; i<=currentSize; ++i){
        if(array[i]>x){
            minValue = array[i];
            pos = i;
            break;
        }
    }
    for(; i<=currentSize; ++i){
        if(array[i]>x&&array[i]<minValue){
            minValue = array[i];
            pos = i;
        }
    }

    return pos;
}

template<class T>
void MinHeap<T>::decrease(int i, int v)
{
    T tmp = array[i]-v;
    int hole = i;
    for(; hole>1&&array[hole/2]>tmp; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = tmp;
}

class disjointSet
{
private:
    int size;
    int *parent;

public:
    disjointSet(int s);
    ~disjointSet(){delete [] parent;}
    void Union(int root1, int root2);
    int find(int x);
};

disjointSet::disjointSet(int s)
{
    size = s+1;
    parent = new int[size];
    for(int i=0; i<size; ++i) parent[i] = -1;
}

int disjointSet::find(int x)
{
    //if(parent[x]<0) return x;
    //return parent[x]=find(parent[x]);
    int start=x,tmp;
    while(!(parent[x]<0)) x = parent[x];
    while(start!=x){
        tmp = parent[start];
        parent[start] = x;
        start = tmp;
    }
    return x;
}

void disjointSet::Union(int root1, int root2)
{
    if(root1==root2) return;
    if(parent[root1]>parent[root2]){
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else{
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}

class adjListGraph
{
public:
    int Vers,Edges;
    adjListGraph(int vSize);
    int minWeight = 0;
    void insert(int x, int y, int w);
    void kruskal();
    ~adjListGraph(){};

private:
    struct edgeNode{
        int end;
        int weight;
        edgeNode *next;

        edgeNode(int e, int w, edgeNode *n=NULL){end = e; weight = w; next = n;}
    };

    struct verNode{
        int ver;
        edgeNode *head;

        verNode(edgeNode *h=NULL){head=h;}
    };

    struct edge{
        int beg,end;
        int w;
        bool operator<(const edge&rp) const{return w<rp.w;}
        bool operator>(const edge&rp) const{return w>rp.w;}
    };

    verNode *verList;
    int find(int v) const{
        for(int i=0; i<Vers; ++i)
            if(verList[i].ver==v) return i;
        return -1;
    }
};

adjListGraph::adjListGraph(int vSize)
{
    Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for(int i=0; i<Vers; ++i) verList[i].ver=i+1;
}

void adjListGraph::insert(int x, int y, int w)
{
    int u=find(x),v=find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    verList[v].head = new edgeNode(u, w, verList[v].head);
    ++Edges;
}

void adjListGraph::kruskal()
{
    int edgeAccepted=0,u,v;
    edgeNode *p;
    edge e;
    disjointSet ds(Vers);
    MinHeap<edge> pq;

    for(int i=0; i<Vers; ++i){
        for(p=verList[i].head; p!=NULL; p=p->next){
            if(i<p->end){
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.enQueue(e);
            }
        }
    }

    while(edgeAccepted < Vers-1){
        e = pq.deQueue();
        u = ds.find(e.beg);
        v = ds.find(e.end);
        if(u!=v){
            edgeAccepted++;
            ds.Union(u,v);
            //cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
            minWeight += e.w;
        }
    }
    cout << minWeight;
}
/*
class adjListGraph
{
public:
    adjListGraph(int vsize)
    {
        Vers=vsize;
        verList=new verNode[vsize];
        for(int i=0;i<Vers;++i) verList[i].ver=i+1;
    }
    void ins(int x,int y,int w)
    {
        verList[x-1].head=new edgeNode(y-1,w,verList[x-1].head);
        verList[y-1].head=new edgeNode(x-1,w,verList[y-1].head);
    }
    ~adjListGraph()
    {
        int i;
        edgeNode *p;
        for(i=0;i<Vers;++i)
            while((p=verList[i].head)!=NULL)
        {
            verList[i].head=p->next;
            delete p;
        }
        delete []verList;
    }
    void kruskal()const
    {
        int edgesaccepted=0,u,v,totalw=0;
        edgeNode *p;
        edge e;
        disjointSet ds(Vers);
        MinHeap<edge> pq;
        for(int i=0;i<Vers;++i)
        {
            for(p=verList[i].head;p!=NULL;p=p->next)
                if(i<p->End)
            {
                e.beg=i;
                e.fin=p->End;
                e.w=p->weight;
                pq.enQueue(e);
            }
        }
        while(edgesaccepted<Vers-1)
        {
            e=pq.deQueue();
            u=ds.find(e.beg);
            v=ds.find(e.fin);
            if(u!=v)
            {
                totalw+=e.w;
                edgesaccepted++;
                ds.Union(u,v);
            }
        }
        cout<<totalw;
    }
private:

    struct edge{
        int beg,fin;
        int w;
        bool operator<(const edge&rp) const {return w<rp.w;}
        bool operator>(const edge&rp) const {return w>rp.w;}
    };
    struct edgeNode
    {
       int End;
        edgeNode *next;
        int weight;
       edgeNode (int e,int w,edgeNode *n=NULL)
       {
            End=e;next=n;weight=w;
       }
    };
    struct verNode
    {
        int ver;
        edgeNode *head;
        verNode (edgeNode *h=NULL){head=h;}
    };
   verNode *verList;
   int Vers;
};*/

int main()
{
    int n,m;
    int a,b,p;

    cin>> n >> m;
    adjListGraph graph(n);
    for(int i=0; i<m; ++i){
        cin >> a >> b >> p;
        graph.insert(a,b,p);
    }
    graph.kruskal();

    return 0;
}
