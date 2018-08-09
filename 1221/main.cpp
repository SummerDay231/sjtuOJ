#include <iostream>
#include <string>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;

    node(int d=0, node* l=NULL, node* r=NULL):data(d),left(l),right(r){}
    ~node(){};
};

class binarySearchTree
{
private:
    node *root;

    bool find(int x, node *t) const;
    void insert(int x, node *&t);
    void remove(int x, node *&t);
    void makeEmpty(node *t);
    void delete_less_than(int x, node *&t);
    void delete_greater_than(int x, node *&t);
    void delete_interval(int x, int y, node *&t);
    void traverse(node *t) const;
    bool find_ith(int x, int &n, node *t) const;
    int size(node *t) const;

public:
    binarySearchTree(){root=NULL;};
    ~binarySearchTree(){};
    bool find(int x) const;
    void insert(int x);
    void remove(int x);
    void delete_less_than(int x);
    void delete_greater_than(int x);
    void delete_interval(int x, int y);
    void traverse() const;
    bool find_ith(int x, int &n) const;
};

bool binarySearchTree::find(int x) const
{
    return find(x, root);
}

bool binarySearchTree::find(int x, node *t) const
{
    if(t==NULL) return false;
    else if(t->data==x) return true;
    else if(x<t->data) return find(x, t->left);
    else return find(x, t->right);
}

void binarySearchTree::insert(int x)
{
    insert(x, root);
}

void binarySearchTree::insert(int x, node *&t)
{
    if(t==NULL) t=new node(x);
    else if(x<t->data) return insert(x, t->left);
    else return insert(x, t->right);
}

void binarySearchTree::remove(int x, node *&t)
{
    if(t==NULL) return;
    else if(x<t->data) remove(x, t->left);
    else if(x>t->data) remove(x, t->right);
    else{
        if(t->left!=NULL&&t->right!=NULL){
            node *tmp=t->right;
            while(tmp->left!=NULL) tmp=tmp->left;
            t->data = tmp->data;
            remove(t->data, t->right);
        }
        else{
            node *old = t;
            t = (t->left!=NULL)?t->left:t->right;
            delete old;
        }
    }
}

void binarySearchTree::remove(int x)
{
    remove(x, root);
}

void  binarySearchTree::makeEmpty(node *t)
{
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

void binarySearchTree::delete_less_than(int x)
{
    delete_less_than(x, root);
}

void binarySearchTree::delete_less_than(int x, node *&t)
{
    if(t==NULL) return;
    else if(t->data==x){
        makeEmpty(t->left);
        return;
    }
    else if(t->data<x){
        node *tmp=t;
        t=t->right;
        makeEmpty(tmp->left);
        delete tmp;
        delete_less_than(x,t);
    }
    else delete_less_than(x,t->left);
}

void binarySearchTree::delete_greater_than(int x)
{
    delete_greater_than(x, root);
}

void binarySearchTree::delete_greater_than(int x, node *&t)
{
    if(t==NULL) return;

    else if(t->data>x){
        node *tmp=t;
        t=t->left;
        makeEmpty(tmp->right);
        delete tmp;
        delete_greater_than(x,t);
    }
    else delete_greater_than(x,t->right);
}

void binarySearchTree::delete_interval(int x, int y)
{
    if(x<=y) delete_interval(x, y, root);
}

void binarySearchTree::delete_interval(int x, int y, node *&t)
{
    if(t==NULL) return;
    else if(t->data<x) delete_interval(x,y,t->right);
    else if(t->data>y) delete_interval(x,y,t->left);
    else{
        remove(t->data,t);
        delete_interval(x,y,t);
    }
}

void binarySearchTree::traverse() const
{
    traverse(root);
}

void binarySearchTree::traverse(node *t) const
{
    if(t==NULL) return;
    traverse(t->left);
    cout << t->data << ' ';
    traverse(t->right);
}

bool binarySearchTree::find_ith(int x, int &n) const
{
    return find_ith(x, n, root);
}

bool binarySearchTree::find_ith(int x, int &n, node *t) const
{
    if(t==NULL) return false;
    int rs = size(t->left);
    if(rs==x-1){
        n=t->data;
        return true;
    }
    if(rs>=x) return find_ith(x, n, t->left);
    else return find_ith(x-rs-1, n, t->right);
}

int binarySearchTree::size(node *t) const
{
    if(t==NULL) return 0;
    return 1+size(t->left)+size(t->right);
}

int instruction(string in)
{
    if(in[0]=='i') return 1;
    if(in[0]=='d'){
        if(in.length()==6) return 2;
        if(in[7]=='g') return 4;
        if(in[7]=='l') return 3;
        if(in[7]=='i') return 5;
    }
    if(in[0]=='f'){
        if(in.length()==4) return 6;
        if(in[5]=='i') return 7;
    }
    return -1;
}

int main()
{
    string in;
    int n,x,a;
    binarySearchTree bst;

    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> in;
        switch(instruction(in)){
        case 1:
            cin >> x;
            bst.insert(x);
            break;
        case 2:
            cin >> x;
            bst.remove(x);
            break;
        case 3:
            cin >> x;
            bst.delete_less_than(x);
            break;
        case 4:
            cin >> x;
            bst.delete_greater_than(x);
            break;
        case 5:
            cin >> x >> a;
            a--;
            bst.delete_interval(x+1,a);
            break;
        case 6:
            cin >> x;
            if(bst.find(x)) cout << 'Y' << endl;
            else cout << 'N' << endl;
            break;
        case 7:
            cin >> x;
            if(bst.find_ith(x,a)) cout << a << endl;
            else cout << 'N' << endl;
            break;
        }
    }

    return 0;
}
