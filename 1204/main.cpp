#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char line[2000];
    char row[100][2000];
    char instruct[5];
    int i,j,num;
    char str[100];
    int r=0;

    cin.getline(line,2000);

    while(strcmp(line,"******")!=0){
        strcpy(row[r++], line);
        cin.getline(line, 2000);
    }

    cin >> instruct;
    while(strcmp(instruct, "quit")!=0){
        switch(instruct[0]){
            case 'l':
                cin >> i >> j;
                if(i<=0||i>r||j<=0||j>r||i>j){
                    cout << "Error!" << endl;
                }
                else{
                    for(int k=i; k<=j; k++)
                        cout << row[k-1] << endl;
                }
                break;
            case 'i':
                cin >> i >> j;
                cin.getline(str, 100);
                if(i<=0||i>r||j<=0||j>strlen(row[i-1])+1){
                    cout << "Error!" << endl;
                }
                else{
                    int l = strlen(str)-1;
                    int length = strlen(row[i-1]);
                    for(int pos=length+1; pos>=j; pos--){
                        row[i-1][pos-1+l] = row[i-1][pos-1];
                    }
                    for(int pos=j; pos<j+l; pos++){
                        row[i-1][pos-1] = str[pos-j+1];
                    }
                    //cout << str[0];
                }
                break;
            case 'd':
                cin >> i >> j >> num;
                if(i<=0||i>r||j<=0||j>strlen(row[i-1])||num<0||num+j>strlen(row[i-1])+1){
                    cout << "Error!" << endl;
                }
                else{
                    int length = strlen(row[i-1]);
                    for(int pos=j; pos<=length+1-num; pos++){
                        row[i-1][pos-1] = row[i-1][pos-1+num];
                    }
                }
                break;
        }
        cin >> instruct;
    }
    for(int k=1; k<=r; k++)
        cout << row[k-1] << endl;
    return 0;
}
