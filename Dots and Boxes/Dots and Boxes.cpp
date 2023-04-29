#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
string a[200];
int t[100][100];
int go[4][2] = {{1,0},{-1,0},{0,-1}, {0,1}};
vector<vector<pair<int, int> > > res(10000);
int v[10000];
int red[10000];
bool valid(int x, int y, int maxx, int maxy){
    if (x < 0 || y < 0){
        return false;
    }
    if (x >= maxx || y >= maxy){
        return false;
    }
    return true;
}
class networkFlow{
    public:
    int sx;
    vector<vector<pair<int, int> > > p;
    int *lvl;   
    networkFlow(int sx){
        this->sx = sx;
        for (int i = 0; i < sx;i++){
            vector<pair<int, int> > temp;
            p[i] = temp;
        }
        lvl = new int[sx+5];
        
    }
    bool level(){
        fill(lvl,lvl+sx+5,0);
        queue<pair<int, int> > q;
        q.push(make_pair(0, 0));
        bool result = false;
        while (!q.empty()){
            pair<int, int> cur = q.front();
            q.pop();
            lvl[cur.first] = cur.second;
            if (cur.first == sx-1){
                result = true;
            }
            for (int i = 0; i < p[cur.first].size();i++){
                if (lvl[p[cur.first][i].first] > 0){
                    continue;
                }
                q.push(make_pair(p[cur.first][i].first, p[cur.first][i].second+1));
            }
        }
    }
    int flow(int cur, int sentf){
        int total = 0;
        if (cur == sx-1){
            return sentf;
        }
        for (int i = 0; i < p[cur].size();i++){
            if (lvl[p[cur][i].first] != lvl[cur]+1){
                continue;
            }
            if (p[cur][i].second <= 0){
                continue;
            }
            int csend = min(sentf, p[cur][i].second);
            int subtot = flow(p[cur][i].first, csend);
            p[cur][i] = make_pair(p[cur][i].first, p[cur][i].second-subtot);
            p[p[cur][i].first].push_back(make_pair(cur, subtot));
            total += subtot;
            sentf -= subtot;
        }
        return total;
    }
    int getMax(){
        bool result = level();
        int total = 0;
        while (result){
            total += flow(0, INT_MAX);
            result = level();
        }
        return result;
    }
    
};
void dps(int s, vector<vector<int> > p, bool re){
    v[s] = 1;
    if (re){
        red[s] = 1;
    } 
    for (int i = 0;i < p[s].size();i++){
        if (p[s][i] == -1){
            res[s].push_back(make_pair(1, -1));
            if (re = 0){
                
            }
            continue;
        }
        if (v[p[s][i]] == 1){
            continue;
        }
        res[s].push_back(make_pair(1, p[s][i]));
        dps(p[s][i], p, !re);
    }
}
int main(){
    cin >> n;
    vector<vector<int > > temp(10000);
    for (int i = 0; i < 2*n-1;i++){
        cin >> a[i];
    }
    for (int i = 0; i < n;i++){
        fill(t[i],t[i]+n,0);
    }
    for (int i = 1; i < 2*n+1;i = i+2){
        for (int l = 1; l < 2*n+1;l = l+2){
            int c = 0;
            
            for (int j = 0; j < 4;j++){
                if (!valid(i+go[j][0], l+go[j][1], 2*n+1, 2*n+1)){
                    continue;
                }
                if (a[i+go[j][0]][l+go[j][1]] == '.'){
                    if (!valid(i+2*go[j][0], l+2*go[j][1], 2*n+1, 2*n+1)){
                        temp[i*n+l].push_back(-1);
                    }
                    if (valid(i+2*go[j][0], l+2*go[j][1], 2*n+1, 2*n+1) && t[i+2*go[j][0]][l+2*go[j][0]] == -1){
                        continue;
                    }
                    c++;
                }
            }
            if (c <= 1){
                t[(i-1)/2][(l-1)/2] = -1; 
            } else {
                t[(i-1)/2][(l-1)/2] = c-1; 
            }
        }
    }
    
    for (int i = 0; i < n;i++){
        for (int l = 0; l < n;l++){
            if (t[i][l] > 1){
                for (int j = 0; j < 4;j++){
                    if (!valid(i+go[j][0], l+go[j][1], n, n)){
                        continue;
                    }
                    if (t[i+go[j][0]][l+go[j][1]] > 1){
                        temp[i*n+l].push_back((i+go[j][0])*n+(l+go[j][1]));
                    }
                }
            }
        }
    }

    fill(v,v+n*n,0);
    fill(red, red+n*n,0);
    for (int i = 0; i < n*n;i++){
        if (v[i] == 1){
            continue;
        }
        dps(i, temp, 1);
        v[i] = 1;
    }
    
    networkFlow out(n*n);

}