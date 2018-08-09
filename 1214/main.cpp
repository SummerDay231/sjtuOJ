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

void levelOrder(node *t){
    queue<node*> que;
    node *tmp;

    que.push(t);

    while(!que.empty()){
        tmp = que.front();
        que.pop();
        cout << tmp->num << ' ';
        if(tmp->left) que.push(tmp->left);
        tmp = tmp->right;
        while(tmp){
            if(tmp->left) que.push(tmp->left);
            cout << tmp->num << ' ';
            tmp = tmp->right;
        }
    }
}

void preOrder(node *t){
    if(t==NULL) return;
    cout << t->num << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

void postOrder(node *t){
    if(t==NULL) return;
    node *tmp;
    tmp = t->left;
    if(tmp)
        while(tmp){
            postOrder(tmp);
            tmp = tmp->right;
        }
    cout << t->num << ' ';
}

int main()
{
    int n,a,b,num;
    node *nodes;

    cin >> n;
    nodes = new node[n];

    for(int i=0; i<n; i++){
        cin >> a >> b >> num;
        nodes[i].num = num;
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

    preOrder(root);
    cout << endl;
    postOrder(root);
    cout << endl;
    levelOrder(root);

    return 0;
}
