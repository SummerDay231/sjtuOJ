#include <iostream>
#include <algorithm> sort
using namespace std;

class set
{
    friend set operator*(const set &a, const set &b);
    friend set operator+(const set &a, const set &b);
    friend set operator-(const set &a, const set &b);
private:
    int *elem;
    int size,volume;

    void doubleSpace();
    bool exist(int x) const;
public:
    set();
    set(const set &a);
    ~set(){delete [] elem;}

    set &operator=(const set &a);
    int getSize(){return size;}
    bool insert(int x);
    bool erase(int x);
    void display();
};

set::set()
{
    size=0;
    volume=20;
    elem = new int[volume];
}

set::set(const set &a)
{
    size = a.size;
    volume = a.volume;
    elem = new int[volume];
    for(int i=0; i<size; ++i) elem[i] = a.elem[i];
}

void set::doubleSpace()
{
    volume *= 2;
    int *tmp = new int[volume];
    for(int i=0; i<size; ++i) tmp[i] = elem[i];
    delete elem;
    elem = tmp;
}

bool set::exist(int x) const
{
    for(int i=0; i<size; ++i)
        if(elem[i]==x) return true;
    return false;
}

bool set::insert(int x)
{
    if(exist(x)) return false;
    if(size==volume) doubleSpace();
    elem[size++] = x;
    //if(size==0)
    return true;
}

bool set::erase(int x)
{
    bool flag=false;
    int i;
    for(i=0; i<size; ++i)
        if(elem[i]==x){
            flag=true;
            break;
        }
    if(flag)
        for(;i<size-1;++i) elem[i] = elem[i+1];
    return flag;
}

set &set::operator=(const set &a)
{
    size = a.size;
    volume = a.volume;
    delete [] elem;
    elem = new int[volume];
    for(int i=0; i<size; ++i) elem[i] = a.elem[i];
    return *this;
}

void set::display()
{
    sort(elem, elem+size);
    for(int i=0; i<size; ++i) cout << elem[i] << ' ';
    cout << endl;
}

set operator*(const set &a, const set &b)
{
    set c;
    for(int i=0; i<a.size; ++i){
        if(b.exist(a.elem[i])) c.insert(a.elem[i]);
    }
    return c;
}

set operator+(const set &a, const set &b)
{
    set c=a;
    for(int i=0; i<b.size; ++i){
        c.insert(b.elem[i]);
    }
    return c;
}

set operator-(const set &a, const set &b)
{
    set c;
    for(int i=0; i<a.size; ++i){
        if(!b.exist(a.elem[i])) c.insert(a.elem[i]);
    }
    return c;
}

int main()
{
    set s;
    int n,m,x;
    char i;

    cin >> n;
    for(int j=0; j<n; ++j){
        cin >> i;
        cin >> m;
        set tmp;
        for(int k=0; k<m; ++k){
            cin >> x;
            tmp.insert(x);
        }
        if(i=='+'){
            s = s+tmp;
        }
        else if(i=='-'){
            s = s-tmp;
        }
        else if(i=='*'){
            s = s*tmp;
        }
        s.display();
    }

    return 0;
}
