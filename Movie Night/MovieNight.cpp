#include <iostream>
#include <vector>
using namespace std;
long n;
long a[100005];
long par[100005];
long ls[100005] = {};
long dis[100005] = {};
vector<int> con;
long loop(long x, long p, long d){
    if (par[x] != 0){
        return par[x];
    }
    if (dis[x] > 0){
        ls[p] = d-dis[x];
        par[x] = p;
        con.push_back(x);
        return p;
    }
    dis[x] = d;
    par[x] = loop(a[x], p,d+1);
    return par[x];
}
vector<pair<long, long> > lcount;
vector<long> lis;

vector<vector<int> > back(100005);
int inlop[100005] = {};
void loopc(int x, int par){
    if (inlop[x] == 1){
        return;
    }
    inlop[x] = 1;
    int si = back[x].size();
    if (x != par){
        for (int i = 0; i < si;i++){
            if (inlop[back[x][i]] == 1){
                continue;
            }
            back[par].push_back(back[x][i]);
        }
    }
    loopc(a[x], par);
}
long dp[100005] = {};
long bcomb(int x){
    if (dp[x] > 0){
        return dp[x];
    }
    long ans = 1;
    for (int i = 0; i < back[x].size();i++){
        if (inlop[back[x][i]] == 1){
            continue;
        }
        long cur  = ans;
        ans = cur*bcomb(back[x][i])%1000000007;
        ans += cur%1000000007; 
        ans = ans;
    }
    dp[x] = ans;
    return ans;
}
int main()
{
    cin >> n;
    for (long i = 0; i < n;i++){
        long temp;
        cin >> temp;
        a[i+1] = temp;
        back[temp].push_back(i+1);
    }
    for (long i = 0; i < n;i++){
        loop(i+1, i+1, 0);
    }
    for (int i = 0; i < con.size();i++){
        loopc(con[i], con[i]);
        back[0].push_back(con[i]);
        inlop[con[i]] = 0;
    }
    /*long ss[100005] = {};
    for (long i = 0; i < n;i++){
        ss[par[i+1]]++; 
    }

    for (long i = 0; i < n;i++){
        if (ls[i+1] >0){
            lcount.push_back(make_pair(ls[i+1], ss[i+1]));
            lis.push_back(i+1);
        }
    }
    cout << d(0)-1 << endl;*/
    cout << bcomb(0)-1 << endl;
    return 0;
}
