#include <iostream>
#include <vector>
using namespace std;
int n,m;
vector<vector<int> > p(30);
int v[30][30];
int vis[35];
bool f(int can, int dep){
    if (dep == n-1){
        return 1;
    }
    vis[can] = 1;
    for (int i = 0; i < p[can].size();i++){
        if (vis[p[can][i]] == 1){
            continue;
        }
        bool res = f(p[can][i], dep+1);

        if (res){
            return 1;
        }
    }
    vis[can] = 0;
    return 0;
}
int main()
{
    cin >> n;
    cin >> m;
    fill(vis, vis+n+5, 0);
    pair<int, string> bal[2005];
    for (int i = 0; i < m;i++){
        pair<int, string> temp;
        cin >> temp.first;
        cin >> temp.second;
        bal[i] = temp;
    }
    for (int i = 0; i < n;i++){
        for (int l = 0; l < n;l++){
            v[i][l] = 0;
        }
    }
    for (int i = 0; i < m;i++){
        for (int l = 0; l < n;l++){
            for (int j = l+1; j < n;j++){
                v[bal[i].second[l]-'A'][bal[i].second[j]-'A'] += bal[i].first;
            }
        }
    }
    for (int i = 0; i < n;i++){
        for (int l = 0; l < n;l++){
            if (v[i][l] > v[l][i]){
                p[i].push_back(l);
            }
        }
    }
    for (int i = 0; i < n;i++){
        fill(vis, vis+n+5, 0);
        bool res = f(i, 0);
        char cur = (char)(i+'A');
        if (res){
            cout << cur << ": can win" << endl;
        } else {
            cout << cur << ": can't win" << endl;
        } 
    }
    return 0;
}
