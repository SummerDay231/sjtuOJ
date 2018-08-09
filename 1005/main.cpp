#include <iostream>
#include <math.h>
using namespace std;

bool test(int l[]){
    int ans=pow(2,9)-1;
    int n;
    for(int i=0; i<9; i++){
        n = pow(2,l[i]-1);
        ans = ans^n;
    }
    return not ans;
}

bool isLegal(int sudoku[9][9]){
    int i,j,x,y;
    int l[9];
    bool result;
    for(i=0; i<9; i++){             //hang jian cha
        for(j=0; j<9; j++){
            l[j] = sudoku[i][j];
        }
        result = test(l);
        if(!result) return false;
    }
    for(i=0; i<9; i++){             //lie jian cha
        for(j=0; j<9; j++){
            l[j] = sudoku[j][i];
        }
        result = test(l);
        if(!result) return false;
    }
    for(i=0; i<9; i++){             //lie jian cha
        for(j=0; j<9; j++){
            x = i/3*3 + j/3;
            y = i%3*3 + j%3;
            l[j] = sudoku[x][y];
        }
        result = test(l);
        if(!result) return false;
    }
    return true;
}
int main()
{
    int sudoku[9][9];
    int n,i,j,k;
    bool result;

    cin >> n;
    for(k=0; k<n; k++){
        for(i=0; i<9; i++){
            for(j=0; j<9; j++)
                cin >> sudoku[i][j];
        }
        result = isLegal(sudoku);
        if(result) cout << "Right" << '\n';
        else cout << "Wrong" << '\n';
    }

    return 0;
}
