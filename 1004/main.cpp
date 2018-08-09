#include <iostream>

using namespace std;

int main()
{
    int M,T,U,F,D,m=0,t=0,a;
    char road;
    cin >> M >> T >> U >> F >> D;

    for(int i=0; i<T; i++){
        cin >> road;
        if(road=='f') a=F*2;
        else a=U+D;
        if(m+a<=M){
            t++;
            m += a;
        }
        else break;
    }
    cout << t;

    return 0;
}
