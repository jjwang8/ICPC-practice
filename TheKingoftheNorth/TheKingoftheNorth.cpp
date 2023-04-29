#include <cmath>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int r, c;
int a[300][300];
int px, py;
const int INF = 2000000000;

struct Edge {
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic {
    int N;
    vector<vector<Edge> > G;
    vector<Edge *> dad;
    vector<int> Q;
    
    Dinic(int N) : N(N), G(N), dad(N), Q(N) {
        this->N = N;
        vector<vector<Edge> > temp(N);
        G = temp;
        vector<int> temp2(N);
        Q = temp2;
        //vector<Edge *> dad5;
        //dad = dad5;
    }
    
    void AddEdge(int from, int to, int cap) {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    }
    
    long long BlockingFlow(int s, int t) {
        fill(dad.begin(), dad.end(), (Edge *) NULL);
        dad[s] = &G[0][0] - 1;
        
        int head = 0, tail = 0;
        Q[tail++] = s;
        while (head < tail) {
            int x = Q[head++];
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = G[x][i];
                if (!dad[e.to] && e.cap - e.flow > 0) {
                    dad[e.to] = &G[x][i];
                    Q[tail++] = e.to;
                }
            }
        }
        if (!dad[t]) return 0;
        
        long long totflow = 0;
        for (int i = 0; i < G[t].size(); i++) {
            Edge *start = &G[G[t][i].to][G[t][i].index];
            int amt = INF;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                if (!e) { amt = 0; break; }
                amt = min(amt, e->cap - e->flow);
            }
            if (amt == 0) continue;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                e->flow += amt;
                G[e->to][e->index].flow -= amt;
            }
            totflow += amt;
        }
        return totflow;
    }
    
    long long GetMaxFlow(int s, int t) {
        long long totflow = 0;
        while (long long flow = BlockingFlow(s, t))
            totflow += flow;
        return totflow;
    }
};
bool val(int x, int y){
    if (x < 0 || y < 0){
        return false;
    }
    if (x >= r || y >= c){
        return false;
    }
    if (a[x][y] == 0){
        return false;
    }
    return true;
}
int main()
{
    cin >> r;
    cin >> c;
    for (int i = 0; i < r;i++){
        for (int l = 0; l < c;l++){
            cin >> a[i][l];
        }
    }
    cin >> px;
    cin >> py;
    Dinic net(r*c*10);
    int g[4][2] = {{1, 0}, {-1, 0}, {0,1}, {0,-1}};
    int count = 0;
    pair<int, int> nod[305][305];
    for (int i = 0; i < r;i++){
        for (int l = 0; l < c;l++){
            nod[i][l] = make_pair(count, count+1);
            count = count+2;
        }
    }
    for (int i = 0; i < r;i++){
        for (int l = 0; l < c;l++){
            if (a[i][l] == 0){
                continue;
            }
            net.AddEdge(nod[i][l].first, nod[i][l].second, a[i][l]);
            for (int j = 0; j < 4;j++){
                if (val(i+g[j][0], l+g[j][1]) == false){
                    continue;
                }
                net.AddEdge(nod[i][l].second, nod[i+g[j][0]][l+g[j][1]].first, INF);
            }
        }
    }
    count++;
    for (int i = 0; i < r;i++){
        if (a[i][0] != 0){
            net.AddEdge(count, nod[i][0].first, INF);
        }
        if (a[i][c-1] != 0){
            net.AddEdge(count, nod[i][c-1].first, INF);
        }
        
    }
    for (int i = 0; i < c;i++){
        if (a[0][i] != 0){
            net.AddEdge(count, nod[0][i].first, INF);
        }
        if (a[r-1][i] != 0){
            net.AddEdge(count, nod[r-1][i].first, INF); 
        }
        
    }
    count++;
    net.AddEdge(nod[px][py].second, count, INF);
    cout << net.GetMaxFlow(count-1, count) << endl;
    return 0;
}
