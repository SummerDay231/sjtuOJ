#include <iostream>
#include <cstring>
using namespace std;

template<class elemType>
class linkList
{
friend ostream &operator<<(ostream & os, const linkList<elemType> &obj)
{   node *n;
    n = obj.head;
    while(n!= obj.end){
        os << n->next->data << ' ';
        n = n->next;
    }
    return os;}

private:
    struct node{
        elemType data;
        node *next;

        node(const elemType &x, node *n=NULL)
            {data=x;next=n;}
        node():next(NULL){}
        ~node(){}
    };

    node *head;
    node *end;

public:
    linkList(){head = new node; end = head;}
    //~linkList(){clear();delete head;}
    void clear(){
        node *p=head->next, *q;
        head->next=NULL;
        while(p!=NULL){
            q = p->next;
            delete p;
            p = q;
        }
    }
    void push_back(elemType x){node *tmp; tmp = new node; tmp->data=x; end->next=tmp; end = tmp;}
    void push_back(linkList *x){end->next = x->head->next; end = x->end; x->end = x->head;}
};

//template<class elemType>
//ostream &operator<<(ostream &os, const linkList<elemType> &obj)
//{
//    return os;
//}

int main()
{
    char type[7];
    int n,m;

    cin >> type >> n >> m;
    if(strcmp(type, "int")==0){
        int tmp;
        linkList<int> a,b;
        for(int i=0;i<n;i++){
            cin >> tmp;
            a.push_back(tmp);
        }
        for(int i=0;i<m;i++){
            cin >> tmp;
             b.push_back(tmp);
        }
        a.push_back(&b);
        cout << a;
    }
    else if(strcmp(type, "double")==0){
        double tmp;
        linkList<double> a,b;
        for(int i=0;i<n;i++){
            cin >> tmp;
            a.push_back(tmp);
        }
        for(int i=0;i<m;i++){
            cin >> tmp;
            b.push_back(tmp);
        }
        a.push_back(&b);
        cout << a;
    }
    else if(strcmp(type, "char")==0){
        char tmp;
        linkList<char> a,b;
        for(int i=0;i<n;i++){
            cin >> tmp;
            a.push_back(tmp);
        }
        for(int i=0;i<m;i++){
            cin >> tmp;
            b.push_back(tmp);
        }
        a.push_back(&b);
        cout << a;
    }

    return 0;
}
