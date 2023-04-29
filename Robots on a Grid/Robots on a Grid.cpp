#include <iostream>
using namespace std;
int n;
string a[1005];
int dp[1005][1005];
int v[1005][1005];
bool val(int x, int y){
    if (x < 0 || y < 0){
        return false;
    }
    if (x >= n || y >= n){
        return false;
    }
    return true;
}
int f(int x, int y){
    if (x == n-1 && y == n-1){
        return 1;
    }
    if (dp[x][y] > 0){
        return dp[x][y];
    }
    int fi = 0,se = 0;
    if (val(x+1,y) && a[x+1][y] != '#'){
        fi = f(x+1,y);
    } 
    if (val(x, y+1) && a[x][y+1] != '#'){
        se = f(x,y+1);
    } 
    dp[x][y] = se+fi;
    return se+fi;
}
bool pos(int x, int y){
    int q[4][2] = {{1,0}, {-1, 0}, {0,1}, {0,-1}};
    if (x == n-1 && y == n-1){
        return true;
    }
    if (v[x][y] == 1){
        return false;
    }
    v[x][y] = 1;
    bool res = false;
    for (int i = 0; i < 4;i++){
        if (!val(x+q[i][0],y+q[i][1] )){
            continue;
        }
        if (v[x+q[i][0]][y+q[i][1]] == 1){
            continue;
        }
        if (a[x+q[i][0]][y+q[i][1]] == '#'){
            continue;
        }
        res = res || pos(x+q[i][0], y+q[i][1]);
    }
    return res;
}
int main(){
    cin >> n;
    for (int i = 0; i < n;i++){
        cin >> a[i];
        for (int l = 0; l < n;l++){
            dp[i][l] = 0;
        }
    }
    int res = f(0,0);
    if (res == 0){
        if (pos(0,0) == true){
            cout << "THE GAME IS A LIE" << endl;
        } else {
            cout << "INCONCEIVABLE" << endl;
        }
    } else {
        cout << res << endl;
    }
}