#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n,m,t,k;
vector<vector<pair<int, int> > > a(100005);
int p[2];
int s[100005];
int d[100005];
void pre(){
    vector<int> v(100005);
    queue<pair<int, int> > q;
    for (int i = 0; i < k;i++){
        q.push(make_pair(s[i], 0));
        v[s[i]] = -1;
    }
    while (!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < a[cur.first].size();i++){
            if (v[a[cur.first][i].first] != 0){
                continue;
            }
            d[a[cur.first][i].first] = cur.second+1;
            v[a[cur.first][i].first] = cur.second+1;
            q.push(make_pair(a[cur.first][i].first, cur.second+1));
        }
    }
}
int c(int v){
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, p[0]));
    int tim[100005];
    for (int i = 0; i < n;i++){
        tim[i] = INT_MAX;
    }
    while (!q.empty()){
        pair<int, int> cur = q.top();
        q.pop();
        if (cur.second == p[1]){
            if (cur.first > t){
                return 0;
            }
            return 1;
        }
        if (tim[cur.second] <= cur.first){
            continue;
        }
        tim[cur.second] = cur.first;
        for (int i = 0; i < a[cur.second].size();i++){
            pair<int, int> nex = a[cur.second][i];
            if (tim[i] < nex.second+cur.first){
                continue;
            }
            if (d[nex.first] < v){
                continue;
            }
            q.push(make_pair(nex.second+cur.first, nex.first));
        }
    }
    return 0;
}
int main(){
    cout << "aaa" << endl;
    cin >> n;
    cin >> m;
    cin >> t;
    for (int i = 0; i < m;i++){
        int temp[3];
        cin >> temp[0];
        cin >> temp[1];
        cin >> temp[2];
        a[temp[0]].push_back(make_pair(temp[1],temp[2]));
        a[temp[1]].push_back(make_pair(temp[0],temp[2]));
    }
    cin >> p[0];
    cin >> p[1];
    cin >> k;
    for (int i = 0; i < k;i++){
        cin >> s[i];
    }
    pre();
    int l = 0;
    int h = n;
    m = (l+h)/2;
    int ans = 0;
    while (1){
        int res = c(m);
        if (abs(l-h) <= 1){
            if (c(l) == 1){
                ans = l;
            } else if (c(h) == 1){
                ans = h;
            } else {
                ans = 0;
            }
            break;
        }
        if (res == 1){
            l = m;
        }
        if (res == 0){
            h = m;
        }
        m = (l+h)/2;
    }
    cout << ans << endl;    
    return 0;
}