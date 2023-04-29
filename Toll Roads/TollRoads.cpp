#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
int n,m,qn;
vector<vector<pair<int, int> > > a(100005);
vector<pair<int, int> > qs;
int par[100005] = {};
int main()
{
    cin >> n;
    cin >> m;
    cin >> qn;
    for (int i = 0; i < m;i++){
        int temp[3];
        cin >> temp[0];
        cin >> temp[1];
        cin >> temp[2];
        a[temp[0]].push_back(make_pair(temp[1], temp[2]));
        a[temp[1]].push_back(make_pair(temp[0], temp[2]));
    }
    unordered_map<pair<int, int>, int> quen; 
    for (int i = 0; i < qn;i++){
        int temp[2];
        cin >> temp[0];
        cin >> temp[1];
        qs.push_back(make_pair(temp[0], temp[1]));
        quen[make_pair(temp[0], temp[1])] = i;
    }
    priority_queue<pair<pair<int, int> , pair<int, int> > > q;
    q.push(make_pair(make_pair(0,0),make_pair(1,1)));
    int v[100005];
    int count = 0;
    vector<vector<pair<int, int> > > tree(100005);
    vector<tuple<int, int, int> > sor;
    while (!q.empty()){
        pair<pair<int, int> , pair<int, int> > cur = q.top();
        q.pop();
        if (v[cur.second.first]){
            continue;
        }
        v[cur.second.first] = 1;
        if (count == n){
            break;
        }
        count++;
        tree[cur.second.second].push_back(make_pair(cur.second.first,  cur.first.second));
        sor.push_back(make_tuple(cur.first.second, cur.second.second, cur.second.first));
        for (int i = 0; i< a[cur.second.first].size();i++){
            if (v[a[cur.second.first][i].first]){
                continue;
            }
            q.push(make_pair(make_pair(max(a[cur.second.first][i].second,cur.first.first),a[cur.second.first][i].second), 
            make_pair(a[cur.second.first][i].first,cur.second.first) ));
        }
    }
    sort(sor.begin(), sor.end());
    for (int i = 0; i < n;i++){
        par[i+1] = i+1;
    }
    unordered_map<pair<int, int>, bool> ch;
    vector<vector<int> > cont(100005);
    for (int i = 0; i < sor.size();i++){
        if (cont[get<1>(sor[i])].size() >= cont[get<2>(sor[i])].size()){
            
            for (int l = 0; l < cont[get<2>(sor[i])].size();l++){
                cont[get<1>(sor[i])].push_back(cont[get<2>(sor[i])][l]);
                ch[make_pair(get<1>(sor[i]), cont[get<2>(sor[i])][l])] =1;
            }
        }
    }
    return 0;
}
