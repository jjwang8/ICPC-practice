#include <iostream>
#include <vector>
using namespace std;
int n, m;
string a[200];
vector<pair<int, int> > e;
int q[4][2] = {{1,0}, {-1, 0}, {0,1}, {0,-1}};
int score[26] = {};
bool valid(int x, int y){
    if (x < 0 || x >= n){
        return false;
    }
    if (y < 0 || y >= m){
        return false;
    }
    if (a[x][y] == 'X'){
        return false;
    }
    if (a[x][y] == '.' || a[x][y] == ' '){
        return true;
    }
    return false;
}
void fill(int x, int y, char let){
    if (!(a[x][y] >= 'A' && a[x][y] <= 'Z')){
        if (a[x][y] == '.'){
            score[let-'a']++;
        }
        a[x][y] = let;
    }
    for (int i = 0; i < 4;i++){
        if (!valid(x+q[i][0], y+q[i][1])){
            continue;
        }
        fill(x+q[i][0], y+q[i][1], let);
    }
}
int main()
{
    cin >> n;
    cin >> m;
    string b;
    getline(cin, b);
    for (int i = 0; i < n;i++){
        getline(cin, a[i]);
    }
    for (int i = 0; i < m;i++){
        if (a[0][i] != 'X' && a[0][i] != '.'){
            e.push_back(make_pair(0,i));
        }
        if (a[n-1][i] != 'X' && a[n-1][i] != '.'){
            e.push_back(make_pair(n-1,i));
        }
    }
    for (int i = 0; i < n;i++){
        if (a[i][0] != 'X' && a[i][0] != '.'){
            e.push_back(make_pair(i,0));
        }
        if (a[i][m-1] != 'X' && a[i][m-1] != '.'){
            e.push_back(make_pair(i,m-1));
        }
    }
    for (int i = 0; i < e.size();i++){
        fill(e[i].first, e[i].second, (char)tolower(a[e[i].first][e[i].second]));
    }
    pair<int, int> ans;
    ans.first = 0;
    ans.second =0;
    int seen[26] = {};
    for (int i = 0; i < 26;i++){
        seen[i] = 0;
    }
    for (int i = 0; i < n;i++){
        for (int l = 0; l < m;l++){
            //cout << a[i][l] << " " << (a[i][l] >= 'a' && a[i][l] <= 'z')<< endl;
            if (a[i][l] >= 'a' && a[i][l] <= 'z' && seen[a[i][l]-'a'] == 0 && score[a[i][l]-'a'] > 0){
                ans.first++;
                seen[a[i][l]-'a'] = 1;
            }
            if (a[i][l] == '.'){
                ans.second++;
            }
        }
    }
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
