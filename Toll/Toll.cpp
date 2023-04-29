#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int k,n,m,o;
vector<vector<pair<int, int> > > p(50005);
pair<int, int> to[50005];
vector<vector<pair<int, int> > > from(50005);
int dpp[50005];
void minspan(int cur){
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0,0));
    int pr[50005];
    fill(pr, pr+n+5, INT_MAX);
    int count = 0;
    while (!q.empty()){
        pair<int, int> cur = q.top();
        q.pop();
        if (pr[cur.second] <= cur.first){
            if (pr[cur.second] == INT_MAX){
                count++;
            }
            continue;
        }
        pr[cur.second] = cur.first;

        for (int i = 0; i < p[cur.second].size();i++){
            if (pr[p[cur.second][i].first] <= cur.first+p[cur.second][i].second){
                continue;
            }
            q.push(make_pair(cur.first+p[cur.second][i].second,p[cur.second][i].first));
            to[p[cur.second][i].first] = make_pair(cur.second, p[cur.second][i].second);
        }
        if (count == n){
            return;
        }
    }
}
int dpminp(int cur, int pri){
    if (from.size() == 1){
        dpp[cur] = pri;
        dpminp(from[cur][0].first, pri+from[cur][0].second);
    } else {
        dpp[cur] = pri;
        for (int i = 0; i < from[cur].size();i++){
            dpminp(from[cur][i].first, from[cur][i].second);
        }
    }
    
}
int main()
{
    cin >> k;
    cin >> n;
    cin >> m;
    cin >> o;
    for (int i = 0; i < m;i++){
        int temp[3];
        cin >> temp[0];
        cin >> temp[1];
        cin >> temp[2];
        p[temp[0]].push_back(make_pair(temp[1], temp[2]));
    }
    fill(to, to+n+5, make_pair(-1, 0));
    minspan(0);
    for (int i = 0; i < n;i++){
        if (to[i].first == -1){
            continue;
        }
        from[to[i].first].push_back(make_pair(i, to[i].second));
    }
    fill(dpp, dpp+n+5, -1);
    dpminp(0, 0);
    
    return 0;
}
