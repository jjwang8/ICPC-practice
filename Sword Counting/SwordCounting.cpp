#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
using namespace std;
int n,m;
vector<vector<pair<int, int > > > a(100005);
int hei[100005][3];
bool vis[100010];
unsigned long long ans = 0;
int vn[100005];
//unordered_map<string, int > tris;
vector<pair<int, int> > edges;
//vector<bitset<100005> > nei;
int tris[100015];
string tos(pair<int, int> key){
    return to_string(key.first) + to_string(key.second);
}
void triange(bitset<100005> ps, int v, int e){
    //cout << v << ps << endl;
    bitset<100005> temp = 0;
    vn[v] = 1;
    for (int i = 0; i < a[v].size();i++){
        temp[a[v][i].first] = 1;
    }
    if (e != -1){
        vis[e] = 1;
        tris[e] = (temp&ps).count();
    }
    for (int i = 0; i < a[v].size();i++){
        if (vis[a[v][i].second] == 1){
            continue;
        }
        triange(temp, a[v][i].first, a[v][i].second);
    }
/*
    for (int i = 0; i < edges.size();i++){
        //cout << i << endl;
        bitset<100005> fir = 0;
        bitset<100005> sec = 0;
        for (int l = 0; l < a[edges[i].first].size();l++){
            fir[a[edges[i].first][l].first] = 1;
        }
        for (int l = 0; l < a[edges[i].second].size();l++){
            sec[a[edges[i].second][l].first] = 1;
        }
        bitset<100005> sam = fir&sec;
        tris[i] = sam.count();
        //tris[tos(edges[i])] = sam.count();
        //tris[tos(make_pair(edges[i].second, edges[i].first))] = sam.count();
    }
    */
}
void f(int v){
    hei[v][0] = 0;
    hei[v][1] = 0;
    hei[v][2] = 0;
    vis[v] = 1;
    vector<pair<int, int> > u;
    //cout << v << endl;
    for (int i = 0; i < a[v].size();i++){
        hei[v][1] += a[a[v][i].first].size()-1;
        if (a[a[v][i].first].size() == 1){
            hei[v][0]++;
        } else {
            hei[v][2]++;
            u.push_back(a[v][i]);
        }
        if (vis[a[v][i].first]){
            continue;
        }
        f(a[v][i].first);
    }
    if (hei[v][1] >= 1 && hei[v][0] >= 3){
        ans += (hei[v][0]*(hei[v][0]-1)*(hei[v][0]-2)/(3*2)) * hei[v][1];
    }
    if (hei[v][2] >= 2 && hei[v][0] >= 2){
        for (int i = 0; i < u.size();i++){
            //int ti = tris[tos(make_pair(u[i], v))];
            int ti = tris[u[i].second];
            ans += (ti)*(hei[v][2]-2)*(hei[v][0]*(hei[v][0]-1)/2);
            ans += (a[u[i].first].size()-1-ti)*(hei[v][2]-1)*(hei[v][0]*(hei[v][0]-1)/2);
        }
    }
    if (hei[v][2] >= 3 && hei[v][0] >= 1){
        for (int i = 0; i < u.size();i++){
            int ti = tris[u[i].second];
            ans += (ti) * ((hei[v][2]-2)*(hei[v][2]-3)/2) * (hei[v][0]);
            ans += (a[u[i].first].size()-1-ti) * ((hei[v][2]-1)*(hei[v][2]-2)/2) * hei[v][0];
        }
    }
    if (hei[v][2] >= 4){
        for (int i = 0; i < u.size();i++){
            int ti = tris[u[i].second];
            ans += (ti) * ((hei[v][2]-2)*(hei[v][2]-3)*(hei[v][2]-4)/6);
            ans += (a[u[i].first].size()-1-ti) * ((hei[v][2]-1)*(hei[v][2]-2)*(hei[v][2]-3)/6);
        }
    }
}
int main()
{
    cin >> n;
    cin >> m;
    //n = 100000;
    //m = 100000;
    fill(vis,vis+m+5,0);
    fill(tris, tris+m+5, 0);
    //vector<bitset<100005> > temp(n);
    //nei = temp;
    for (int i = 0; i < m;i++){
        int temp[2];
        cin >> temp[0];
        cin >> temp[1];
        //temp[0] = (i+1*m)%n;
        //temp[1] = ((i+2)*m)%n;
        temp[0]--;
        temp[1]--;
        a[temp[0]].push_back(make_pair(temp[1],i));
        a[temp[1]].push_back(make_pair(temp[0], i));
        //edges.push_back(make_pair(temp[0],temp[1]));
        //cout << i << endl;
    }
    fill(vn, vn+    n+5, 0);
    for (int i = 0; i < n;i++){
        bitset<100005> temp = 0;
        if (vn[i] == 0){
            triange(temp, i, -1);
        }
    }
    fill(vis, vis+n+5, 0);
    for (int i = 0; i < n;i++){
        if (vis[i] == 0){

            f(
                i);
        }
    }
    cout << ans << endl;
    return 0;
}
