#include <iostream>

using namespace std;

class adjListGraph
{
public:
    int Vers,Edges;
    adjListGraph(int vSize);
    void insert(int x, int y);
    ~adjListGraph(){};
    void dfs() const;
    int find(int start, int M) const;

private:
    struct edge{
        int end;
        edge *next;

        edge(int e, edge *n=NULL){end = e; next = n;}
    };

    struct verNode{
        int ver;
        edge *head;

        verNode(edge *h=NULL){head=h;}
    };

    verNode *verList;
    int find(int v) const{
        for(int i=0; i<Vers; ++i)
            if(verList[i].ver==v) return i;
        return -1;
    }
    void dfs(int start, bool visited[]) const;
    void find(int start, int M, int &top, bool visited[], int st[], int &result) const;
};

adjListGraph::adjListGraph(int vSize)
{
    Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for(int i=0; i<Vers; ++i) verList[i].ver=i+1;
}

void adjListGraph::insert(int x, int y)
{
    int u=find(x),v=find(y);
    verList[u].head = new edge(v, verList[u].head);
    ++Edges;
}

void adjListGraph::dfs() const
{
    bool *visited = new bool[Vers];
    for(int i=0; i<Vers; ++i) visited[i]=false;

    for(int i=0; i<Vers; ++i){
        if(visited[i]==true) continue;
        dfs(i, visited);
        cout << endl;
    }
}

void adjListGraph::dfs(int start, bool visited[]) const
{
    edge *p=verList[start].head;

    cout << verList[start].ver << '\t';
    visited[start] = true;

    while(p!=NULL){
        if(visited[p->end]==false) dfs(p->end, visited);
        p = p->next;
    }

    return;
}

int adjListGraph::find(int start, int M) const
{
    int result=0;
    bool *visited = new bool[Vers];
    int *stack = new int[M+1], top=0, i;

    for(i=0; i<Vers; ++i) visited[i]=false;

    for(i=0; i<Vers; ++i)
        if(verList[i].ver==start) break;

    find(i, M, top, visited, stack, result);

    return result;
}

void adjListGraph::find(int start, int M, int &top, bool visited[], int st[], int &result) const
{
    edge *p = verList[start].head;

    visited[start] = true;
    st[top++] = start;
    if(top==M+1){
        //cout << endl;
        //for(int i=0; i<top; ++i)
        //    cout << verList[st[i]].ver << '\t';
        visited[start] = false;
        --top;
        ++result;
        return;
    }

    while(p!=NULL){
        if(!visited[p->end]) find(p->end, M, top, visited, st, result);
        p = p->next;
    }
    visited[start] = false;
    --top;
}

int main()
{
    int n,m,start,M;
    int a,b;

    cin>> n >> m >> start >> M;
    adjListGraph graph(n);
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        graph.insert(a,b);
    }
    cout << graph.find(start, M);

    return 0;
}
