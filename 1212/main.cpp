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
        if(tmp->right) que.push(tmp->right);
    }
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

    levelOrder(root);


    return 0;
}
