#include <iostream>
#include <string>
using namespace std;

struct node{
    node *next;
    node *prev;
    int data;

    node(int x){data=x;next=NULL;prev=NULL;}
    node():next(NULL),prev(NULL){}
};

class bigint
{
friend bigint add(bigint &x1, bigint &x2);
private:
    node *low;
    node *high;
    int digit;

public:
    bigint(){low = new node;high=low;digit=0;}
    void append(int x){
        if(high==low){
            node *tmp;
            tmp = new node;
            tmp->data=x;
            low->next=tmp;
            high=tmp;
            tmp->prev=low;
            digit++;
        }
        else{
            node *tmp;
            tmp = new node;
            tmp->data=x;
            tmp->prev = low;
            tmp->next = low->next;
            tmp->next->prev=tmp;
            tmp->prev = low;
            low->next = tmp;
            //high->next=tmp;
            //tmp->prev=high;
            //high=tmp;
            digit++;
        }
    }
    void push_front(int x){
        if(high==low){
            node *tmp;
            tmp = new node;
            tmp->data=x;
            low->next=tmp;
            high=tmp;
            tmp->prev=low;
            digit++;
        }
        else{
            node *tmp;
            tmp = new node;
            tmp->data=x;
            tmp->prev = high;
            high->next = tmp;
            high = tmp;
            //high->next=tmp;
            //tmp->prev=high;
            //high=tmp;
            digit++;
        }
    }
    void print(){
        node *pos;
        pos = high;
        while(pos!=low){
            cout << pos->data;
            pos = pos->prev;
        }
    }
    int getDigit(){return digit;}
};

bigint add(bigint &x1, bigint &x2){
    int d1=x1.getDigit();
    int d2=x2.getDigit();
    int n1,n2,tmp,jinwei=0;
    node *pos1,*pos2;
    bigint result;

    if(d1==d2){
        pos1=x1.low;
        pos2=x2.low;
        for(int i=0;i<d1;i++){
            pos1=pos1->next;
            pos2=pos2->next;
            n1=pos1->data;
            n2=pos2->data;
            tmp = (n1+n2+jinwei)%10;
            jinwei = (n1+n2+jinwei)/10;
            result.push_front(tmp);
        }
        if(jinwei)
            result.push_front(jinwei);
    }
    else if(d1>d2){
        pos1=x1.low;
        pos2=x2.low;
        for(int i=0;i<d2;i++){
            pos1=pos1->next;
            pos2=pos2->next;
            n1=pos1->data;
            n2=pos2->data;
            tmp = (n1+n2+jinwei)%10;
            jinwei = (n1+n2+jinwei)/10;
            result.push_front(tmp);
        }
        for(int i=d2;i<d1;i++){
            pos1=pos1->next;
            n1=pos1->data;
            tmp = (n1+jinwei)%10;
            jinwei = (n1+jinwei)/10;
            result.push_front(tmp);
        }
        if(jinwei){
            result.push_front(jinwei);
        }
    }
    else{
        pos1=x1.low;
        pos2=x2.low;
        for(int i=0;i<d1;i++){
            pos1=pos1->next;
            pos2=pos2->next;
            n1=pos1->data;
            n2=pos2->data;
            tmp = (n1+n2+jinwei)%10;
            jinwei = (n1+n2+jinwei)/10;
            result.push_front(tmp);
        }
        for(int i=d1;i<d2;i++){
            pos2=pos2->next;
            n2=pos2->data;
            tmp = (n2+jinwei)%10;
            jinwei = (n2+jinwei)/10;
            result.push_front(tmp);
        }
        if(jinwei){
            result.push_front(jinwei);
        }
    }
    return result;
}

int main()
{
    bigint num1,num2,num3;
    char in[1000001];
    int i=0;

    cin.getline(in, 1000001);
    while(in[i]!='\0'){
        num1.append(in[i]-'0');
        i++;
    }
    cin.getline(in, 1000001);
    i=0;
    while(in[i]!='\0'){
        num2.append(in[i]-'0');
        i++;
    }

    num3 = add(num1,num2);
    num3.print();

    return 0;
}
