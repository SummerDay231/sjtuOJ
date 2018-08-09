#include <iostream>
using namespace std;


class Queue
{
private:
    struct node{
        node *next;
        int data;

        node(int x, node *N=NULL){data = x; next = N;}
        node():next(NULL){}
        ~node(){}
    };

    node *head;
    node *rear;

public:
    Queue(){head = rear = NULL;}
    bool isEmpty(){return head==NULL;}
    int enQueue(int x){
        if(head==NULL){
            head = new node(x);
            rear = head;
        }
        else{
            node *tmp;
            tmp = new node(x);
            rear->next = tmp;
            rear = rear->next;
        }
        return x;
    }
    int deQueue(){
        node *tmp=head;
        int t=head->data;
        head = head->next;
        if(head==NULL)
            rear = NULL;
        delete tmp;
        return t;
    }
    int getHead(){
        return head->data;
    }
    bool isExist(int x){
        node *tmp=head;
        while(tmp!=NULL){
            if(tmp->data==x) return true;
            tmp = tmp->next;
        }
        return false;
    }
};

template<class ToV, class ToE>
class adjListGraph
{
public:
    int Vers, Edges;
    adjListGraph(int vSize, const ToV d[]);
    void insert(ToV x, ToV y, ToE w);
    void remove(ToV x, ToV y);
    void weightdNegative(ToV start, ToV end, ToE noEdge);
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
    int find(ToV v) const{return v-1;}
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
void adjListGraph<ToV, ToE>::weightdNegative(ToV start, ToV end, ToE noEdge)
{
    Queue q;
    edgeNode *p;
    ToE *distance = new ToE[Vers];
    int *prev = new int[Vers];
    int sNo,eNo,v,i;

    for(i=0; i<Vers; ++i){
        distance[i] = noEdge;
    }

    sNo=find(start);
    eNo=find(end);
    distance[sNo]=0;
    prev[sNo]=sNo;
    q.enQueue(sNo);

    while(!q.isEmpty()){
        v = q.deQueue();
        for(p=verList[v].head; p!=NULL; p=p->next){
            if(distance[v]+p->weight<distance[p->end]){
                distance[p->end] = distance[v]+p->weight;
                prev[p->end]=v;
                if(!q.isExist(p->end)) q.enQueue(p->end);
            }
        }
    }

    //for(i=0; i<Vers; ++i){
        //cout << "From" << start << "to" << verList[i].ver << ":" << endl;
        //printPath(sNo, i, prev);
        cout <<distance[eNo];
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
    graph.weightdNegative(start, end, 2147483647);

    return 0;
}
