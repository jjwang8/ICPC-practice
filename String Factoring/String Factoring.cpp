#include <iostream>
#include <unordered_map>
using namespace std;
string a;
string pre[205][205];
int dp[205][205];
int f(int s, int e){
    if (s == e){
        return 1;
    }
    if (dp[s][e] > 0) {
        return dp[s][e];
    }
    int mi = INT_MAX;
    for (int i = s; i <= e-1;i++){
        unordered_map<string, bool> ch;
        int ne = i+1;
        ch[pre[s][i]] = 1;
        for (int l = i+1; l <= e-(i-s);l = l+(i-s+1)){
            //cout << pre[l][l+(s-i)] << s << e << endl;
            if (ch[pre[l][l+(i-s)]] != 1){
                break;
            }
            ne = l+(i-s+1);
        } 
        int res;
        if (ne > e){
            res = f(s, i);
            //cout << pre[s][i] << res << endl;
        } else {
            res = f(s, i) + f(ne, e);
            //cout << pre[s][i] << " " << pre[ne][e] << res << endl;
        }
        mi = min(res, mi);
    }
    dp[s][e] = mi;
    return mi;
}
int main(){
    cin >> a;
    for (int i = 0; i < a.length();i++){
        pre[i][i] = a[i];
        for (int l = i+1; l < a.length();l++){
            pre[i][l] = pre[i][l-1]+a[l];
            //cout << i << l << pre[i][l] << endl;
        }
    }
    for (int i = 0 ; i < a.length();i++){
        for (int l = 0; l < a.length();l++){
            dp[i][l] = 0;
        }
    }
    cout << f(0, a.length()-1) << endl;
}