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
    T tmp=array[hole];

    for(; hole*2<=currentSize; hole=child)
    {
        child = hole*2;
        if(child!=currentSize&&array[child+1]<array[child]){
            ++child;
        }
        if(array[child]<tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
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

int main()
{
    int n,i,v;
    char in[10];
    MinHeap<int> q;

    cin >> n;
    for(int j=0; j<n; ++j){
        cin >> in;
        if(in[0]=='i'){
            cin >> i;
            q.enQueue(i);
        }
        else if(in[0]=='m'){
            cout << q.getHead() << endl;
        }
        else{
            q.deQueue();
        }
    }
    return 0;
}
