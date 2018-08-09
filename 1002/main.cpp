#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int l,w,tmp,a,b,sum=0,m=0;
    vector<vector<int> > garden;

    cin >> l >> w;
    for(int i=0; i<l; i++){
        vector<int> row;
        for(int j=0; j<w; j++){
            cin >> tmp;
            row.push_back(tmp);
        }
        garden.push_back(row);
    }
    cin >> a >> b;

    for(int i=0; i<l-a; i++){
        for(int p=i; p<a+i; p++){
            for(int q=0; q<b; q++){
                sum += garden[p][q];
            }
        }
        m = sum>m ? sum:m;
        for(int j=1; j<w-b; j++){
            for(int k=i; k<a+i; k++){
                sum -= garden[k][j];
                sum += garden[k][j+b-1];
            }
            m = sum>m ? sum:m;
        }
    }

    cout << m;
    return 0;
}
