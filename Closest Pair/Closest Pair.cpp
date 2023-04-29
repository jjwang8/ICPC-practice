#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n;
vector<pair<float, float> > a;
vector<pair<float, float> > b;
struct ans{
    float res;
    pair<float, float> fi;
    pair<float, float> se;
};
float dist(pair<float, float> f, pair<float, float> s){
    int temp = (f.first-s.first)*(f.first-s.first) + (f.second-s.second)*(f.second-s.second);
    return sqrt(temp);
}
ans dis(int l, int h){
    if (abs(l-h) <= 1){
        ans temp;
        temp.res = dist(a[l], a[h]);
        temp.fi = a[l];
        temp.se = a[h];
        return temp;
    }
    int m = (l+h)/2;
    ans f = dis(l, (l+h)/2);
    ans s = dis((l+h)/2, h);
    ans tot;
    if (f.res > s.res){
        tot = s;
    } else {
        tot = f;
    }
    vector<pair<float, float> > con;
    for (int i = 0; i < n;i++){
        if (b[i].second < l || b[i].second > h){
            continue;
        }
        if (abs(b[i].second - a[m].first) < tot.res){
            con.push_back(b[i]);
        }
    }
    for (int i = 0; i < con.size();i++){
        for (int j = 1; j < 8;j++){
            if (i+j >= con.size()){
                continue;
            }
            float temp = dist(con[i], con[i+j]);
            if (temp < tot.res){
                tot.res = temp;
                tot.fi = con[i];
                tot.se = con[i+j];
            }
        }
    }
    return tot;
}
int main(){
    while (1){
        cin >> n;
        if (n == 0){
            break;
        }
        for (int i = 0; i < n;i++){
            pair<float, float> temp;
            cin >> temp.first;
            cin >> temp.second;
            a.push_back(temp);
            b.push_back(make_pair(temp.second, temp.first));
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ans temp = dis(0,n-1);
        cout << "aaa" << endl;
        cout << temp.fi.first << " " << temp.fi.second << " " << temp.se.first << " " << temp.se.second << endl;
        a.clear();
        b.clear();
    }
    return 0;
}