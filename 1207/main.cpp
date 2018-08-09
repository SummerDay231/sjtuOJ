#include <iostream>
#include <iomanip>
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
};

bool isBothEmpty(Queue *a, Queue *b){
    return a->isEmpty()&&b->isEmpty();
}

int main(){
    Queue coach, truck;
    int n, type, arrive_time, num_c=0, num_t=0;
    int time_now=0, sum_c=0, sum_t=0, car_on_boat=0, passed_coach=0;

    cin >> n;
    for(int i=0; i<n; i++){
        cin >> type >> arrive_time;
        if(type){
            truck.enQueue(arrive_time);
            ++num_t;
        }
        else{
            coach.enQueue(arrive_time);
            ++num_c;
        }
    }

    while(!isBothEmpty(&coach, &truck)){
        car_on_boat = 0;
        passed_coach =0;
        while(car_on_boat<10){
            if(!coach.isEmpty()&&coach.getHead()<=time_now){
                if(passed_coach<4){
                    sum_c += time_now-coach.deQueue();
                    ++car_on_boat;
                    ++passed_coach;
                }
                else if(!truck.isEmpty()&&truck.getHead()<=time_now){
                    sum_t += time_now-truck.deQueue();
                    ++car_on_boat;
                    passed_coach=0;
                }
                else{
                    sum_c += time_now-coach.deQueue();
                    ++car_on_boat;
                    ++passed_coach;
                }
            }
            else if(!truck.isEmpty()&&truck.getHead()<=time_now){
                sum_t += time_now-truck.deQueue();
                ++car_on_boat;
                passed_coach=0;
            }
            else break;
        }

        time_now += 10;
    }
    cout << fixed << setprecision(3) << double(sum_c)/num_c << ' ' << double(sum_t)/num_t;

    return 0;
}


/*#include <iostream>
#include <iomanip>
#include <limits.h>
using namespace std;
class Queue
{
private:
    struct node{
        node *next;
        int arrive_time;

        node(int x, node *N=NULL){arrive_time=x;next=N;}
        node():next(NULL){}
        ~node(){}
    };

    node *front;
    node *rear;

public:
    Queue(){front = rear = NULL;}
    bool isEmpty(){return front==NULL;}
    void enQueue(int x){
        if(rear==NULL){
            rear = new node(x);
            front = rear;
        }
        else{
            rear->next = new node(x);
            rear = rear->next;
        }
    }
    int getHead(){
        if(isEmpty()){
            return INT_MAX;
        }
        else
            return front->arrive_time;
    }
    int deQueue(){
        if(isEmpty()){
            return 0;
        }
        else{
            node *tmp=front;
            int t=front->arrive_time;
            front = front->next;
            if(front==NULL)
                rear = NULL;
            delete tmp;
            return t;
        }
    }
};


int main()
{
    int num,type,time, cnum=0, tnum=0, t;
    int Time_Now=0, c_sum=0, t_sum=0, car_on_boat=0, passed_coach=0;
    Queue coach,truck;

    cin >> num;
    for(int i=0; i<num; i++){
        cin >> type >> time;
        if(type==0){
            coach.enQueue(time);
            cnum++;
        }
        if(type==1){
            truck.enQueue(time);
            tnum++;
        }
    }
    while(!coach.isEmpty()||!truck.isEmpty()){
        while(car_on_boat<10){
            t = 0;
            if(coach.getHead()<=Time_Now){
                if(passed_coach<4){
                    t = coach.deQueue();
                    c_sum += Time_Now-t;
                    car_on_boat++;
                    passed_coach++;
                }
                else if(truck.getHead()<=Time_Now){
                    t = truck.deQueue();
                    t_sum += Time_Now-t;
                    car_on_boat++;
                    passed_coach = 0;
                }
                else{
                    t = coach.deQueue();
                    t_sum += Time_Now-t;
                    car_on_boat++;
                }
            }
            else if(truck.getHead()<=Time_Now){
                t = truck.deQueue();
                t_sum += Time_Now - t;
                car_on_boat++;
                passed_coach = 0;
            }
            else break;
        }
        car_on_boat = 0;
        passed_coach = 0;
        Time_Now += 10;
    }

    cout << fixed << setprecision(3) << double(c_sum)/cnum << ' ' << double(t_sum)/tnum;

    return 0;
}*/
