#include <iostream>
using namespace std;

template<class T>
class priorityQueue
{
private:
    int currentSize;
    T *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

public:
    priorityQueue(int capacity=100);
    priorityQueue(const T data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
    int find(T x) const;
    void decrease(int i, int v);
};

template<class T>
priorityQueue<T>::priorityQueue(int capacity)
{
    array = new T[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template<class T>
priorityQueue<T>::~priorityQueue()
{
    delete [] array;
}

template<class T>
bool priorityQueue<T>::isEmpty() const
{
    return currentSize==0;
}

template<class T>
T priorityQueue<T>::getHead() const
{
    return array[1];
}

template<class T>
void priorityQueue<T>::enQueue(const T &x)
{
    if(currentSize==maxSize-1) doubleSpace();

    int hole = ++currentSize;
    for(; hole>1&&array[hole/2]>x; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template<class T>
T priorityQueue<T>::deQueue()
{
    T minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template<class T>
void priorityQueue<T>::percolateDown(int hole)
{
    int child;
    T tmp=array[hole];
    for(;hole*2<=currentSize;hole=child)
    {
        child = hole*2;
        if(child!=currentSize&&array[child+1]<array[child])
            child++;
        if(array[child]<tmp) array[hole]=array[child];
        else break;
    }
    array[hole]=tmp;
}

template<class T>
void priorityQueue<T>::doubleSpace()
{
    T *tmp = array;
    maxSize *= 2;
    array = new T[maxSize];
    for(int i=1; i<=currentSize; ++i)
        array[i] = tmp[i];
    delete [] tmp;
}

template<class T>
int priorityQueue<T>::find(T x) const
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
void priorityQueue<T>::decrease(int i, int v)
{
    T tmp = array[i]-v;
    int hole = i;
    for(; hole>1&&array[hole/2]>tmp; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = tmp;
}

template<class ToV, class ToE>
class adjListGraph
{
public:
    int Vers, Edges;
    adjListGraph(int vSize, const ToV d[]);
    void insert(ToV x, ToV y, ToE w);
    void remove(ToV x, ToV y);
    void dijkstra(ToV start, ToV end, ToE noEdge) const;
    ~adjListGraph();

private:
    struct edgeNode{
        int end;
        ToE weight;
        edgeNode *next;

        edgeNode(int e, ToE w, edgeNode *n=NULL){
            end = e; weight = w; next = n;}
    };
    struct verNode{
        ToV ver;
        edgeNode *head;

        verNode(edgeNode *h=NULL){head = h;}
    };
    struct queueNode{
        ToE dist;
        int node;

        bool operator<(const queueNode &rp) const {return dist<rp.dist;}
        bool operator>(const queueNode &rp) const {return dist>rp.dist;}
    };

    verNode *verList;
    int find(ToV v) const{
        //for(int i=0; i<Vers; ++i)
        //    if(verList[i].ver==v) return i;
        return v-1;
    }
    void printPath(int start, int end, int prev[]) const{
        if(start==end){
            cout << verList[start].ver;
            return;
        }
        printPath(start,prev[end],prev);
        cout << ' ' << verList[end].ver;
    }
};

template<class ToV, class ToE>
adjListGraph<ToV, ToE>::adjListGraph(int vSize, const ToV d[])
{
    Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for(int i=0; i<vSize; ++i)  verList[i].ver = d[i];
}

template<class ToV, class ToE>
adjListGraph<ToV, ToE>::~adjListGraph()
{
    int i;
    edgeNode *p;

    for(i=0; i<Vers; ++i){
        while((p=verList[i].head)!=NULL){
            verList[i].head = p->next;
            delete p;
        }
    }

    delete [] verList;
}

template<class ToV, class ToE>
void adjListGraph<ToV, ToE>::insert(ToV x, ToV y, ToE w)
{
    int u=find(x),v=find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++Edges;
}

template<class ToV, class ToE>
void adjListGraph<ToV, ToE>::remove(ToV x, ToV y)
{
    int u=find(x),v=find(y);
    edgeNode *p = verList[u].head, *q;

    if(p==NULL) return;

    if(p->end=v){
        verList[u].head = p->next;
        delete p;
        --Edges;
        return;
    }
    while(p->next!=NULL&&p->next->end!=v) p=p->next;
    if(p->next!=NULL){
        q = p->next;
        p->next = q->next;
        delete p;
        --Edges;
    }
}

template<class ToV, class ToE>
void adjListGraph<ToV, ToE>::dijkstra(ToV start, ToV end, ToE noEdge) const
{
    ToE *distance = new ToE[Vers];
    int *prev = new int [Vers];
    int *hop = new int [Vers];
    bool *known = new bool[Vers];
    priorityQueue<queueNode> q;
    queueNode min,succ;
    //int u,sNo,i,j;
    int sNo,i,eNo;
    edgeNode *p;
    //ToE min;

    for(i=0; i<Vers; ++i){
        known[i]=false;
        distance[i]=noEdge;
        hop[i] = 0;
    }

    sNo=find(start);
    eNo=find(end);
    distance[sNo]=0;
    prev[sNo]=sNo;
    min.dist=0;
    min.node=sNo;
    q.enQueue(min);

    while(!q.isEmpty()){
        min = q.deQueue();
        if(known[min.node]) continue;
        known[min.node] = true;
        for(p=verList[min.node].head; p!=NULL; p=p->next)
            if(!known[p->end]&&(distance[p->end]>min.dist+p->weight
                            ||distance[p->end]==min.dist+p->weight&&hop[p->end]>hop[min.node]+1)){
                succ.dist = distance[p->end] = min.dist+p->weight;
                hop[p->end]=hop[min.node]+1;
                prev[p->end]=min.node;
                succ.node = p->end;
                q.enQueue(succ);
            }
        if(min.node==eNo) break;
    }

    //for(i=0; i<Vers; ++i){
        //cout << "From" << start << "to" << verList[min.node].ver << ":" << endl;
        cout <<distance[min.node] << endl;
        printPath(sNo, min.node, prev);
    //}
}

int main()
{
    int n,m,start,end;
    int a,b,p;
    int *t;

    cin >> n >> m >> start >> end;
    t = new int[n];

    for(int i=0; i<n; ++i){
        t[i] = i+1;
    }

    adjListGraph<int, int> graph(n, t);

    for(int i=0; i<m; ++i){
        cin >> a >> b >> p;
        graph.insert(a, b, p);
    }
    graph.dijkstra(start, end, 2147483647);

    return 0;
}
