#include <iostream>
#include <queue>
using namespace std;

struct node{
    node *left;
    node *right;
    node *parent;
    int num;
    node(){left=right=parent=NULL;}
};

class binaryTree
{
public:
    node *root;

    binaryTree(){root=NULL;}
    void preOrder(node *t){
        if(t==NULL) return;
        cout << t->num << ' ';
        preOrder(t->left);
        preOrder(t->right);
    }
};

bool isCBT(node *t){
    queue<node*> que;
    node *tmp;

    que.push(t);
    bool existNULL=false;

    while(!que.empty()){
        tmp = que.front();
        que.pop();
        if(tmp!=NULL){
            if(existNULL) return false;
            if(tmp->left) que.push(tmp->left);
            else que.push(NULL);
            if(tmp->right) que.push(tmp->right);
            else que.push(NULL);
        }
        else{
            existNULL=true;
        }
    }
    return true;
}

int main()
{
    int n,a,b;
    node *nodes;

    cin >> n;
    nodes = new node[n];

    for(int i=0; i<n; i++){
        cin >> a >> b;
        nodes[i].num = i+1;
        if(a){
            nodes[i].left = &nodes[a-1];
            nodes[a-1].parent = &nodes[i];
        }
        if(b){
            nodes[i].right = &nodes[b-1];
            nodes[b-1].parent = &nodes[i];
        }
    }

    node *root;
    root = &nodes[0];
    while(root->parent!=NULL)
        root = root->parent;

    if(isCBT(root)) cout << 'Y';
    else cout << 'N';

    return 0;
}
