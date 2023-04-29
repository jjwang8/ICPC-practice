#include <iostream>
using namespace std;
int x, y, n;
int s[2];
int b[20][2];
int dp[20][10000];
int dis(int f, bitset<20> d){
    if (d.count() == n){
        return abs(s[0]-b[f][0])+abs(s[1]-b[f][1]);
    }
    if (dp[f][d.to_ulong()] > 0){
        return dp[f][d.to_ulong()];
    }
    int mi = INT_MAX;
    for (int i = 0; i < n;i++){
        if (d[i] == 1){
            continue;
        }
        int dist;
        if (f == -1){
            dist = abs(s[0] - b[i][0]) + abs(s[1] - b[i][1]);
        } else {
            dist = abs(b[f][0] - b[i][0])+abs(b[f][1] - b[i][1]);
        }
        d[i] = 1;
        mi = min(mi, dis(i, d)+dist);
        d[i] = 0;
    }
    if (f != -1){
        dp[f][(int)d.to_ulong()] = mi;
    }
    return mi;
}
int main(){
    int con;
    cin >> con;
    while (con > 0){
        con--;
        cin >> x;
        cin >> y;
        cin >> s[0];
        cin >> s[1];
        cin >> n;
        for (int i = 0; i < n;i++){
            cin >> b[i][0];
            cin >> b[i][1];
            for (int l = 0; l < n;l++){
                dp[i][l] = 0;
            }
        }
        bitset<20> d;
        cout << dis(-1, d) << endl;
    }
    return 0;
}