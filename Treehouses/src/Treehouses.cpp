//============================================================================
// Name        : Treehouses.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
int n, e, p;
float a[1005][1005];
float val[1005];
vector<vector<int> > v(1005);
struct two{
	int x;
	int y;
};
vector<int> d(1005);
priority_queue<pair<float, int> > q;
int vis = 0;
int main() {
	cin >> n;
	cin >> e;
	cin >> p;
	for (int i = 0; i < n;i++){
		cin >> a[i][0];
		cin >> a[i][1];
		val[i] = INT_MAX;
		d[i] = -1;
	}
	for (int i = 0; i < p;i++){
		int temp[2];
		cin >> temp[0];
		cin >> temp[1];
		temp[0]--;
		temp[1]--;
		v[temp[0]].push_back(temp[1]);
		v[temp[1]].push_back(temp[0]);
	}
	for (int i = 0; i < e;i++){
		val[i] = 0;
		for (int l = 0; l < v[i].size();l++){
			val[v[i][l]] = 0;
		}
	}
	for (int i = 0; i < n;i++){
		if (val[i] == 0){
			vis++;
			for (int l = e; l < n;l++){
				float dist = (a[i][0]-a[l][0])*(a[i][0]-a[l][0]) +
											(a[i][1]-a[l][1])*(a[i][1]-a[l][1]);
				if (val[l] >  sqrt(dist)){
					//cout << sqrt(dist) << " " << i << " " << l << endl;
					q.push(make_pair(sqrt(dist), l));
					val[l] = sqrt(dist);
					d[l] = i;
				}
			}
		}
	}
	while (!q.empty()){
		pair<float, int> cur = q.top();
		q.pop();

		if (val[cur.second] < cur.first){
			continue;
		}
		cout << cur.first << " " << cur.second << " " << val[cur.second] << endl;
		for (int i = e; i < n;i++){
			float dist = (a[cur.second][0]-a[i][0])*(a[cur.second][0]-a[i][0]) +
						(a[cur.second][1]-a[i][1])*(a[cur.second][1]-a[i][1]);
			//cout << val[i] << " " << cur.first << " " << cur.second << " " << i << endl;
			if (val[i] > cur.first+sqrt(dist) && i != cur.second){
				cout << i << cur.second << endl;
				val[i] = cur.first+sqrt(dist);
				q.push(make_pair(cur.first+sqrt(dist), i));
				d[i] = cur.second;
			}
		}
	}
	vector<int> d2(1005);
	float tot = 0;
	for (int i = 0; i < n;i++){
		if (d[i] != -1){
			float dist = (a[d[i]][0]-a[i][0])*(a[d[i]][0]-a[i][0]) +
									(a[d[i]][1]-a[i][1])*(a[d[i]][1]-a[i][1]);
			//cout << dist << endl;
			tot += sqrt(dist);
		}
	}
	cout << tot << endl; // prints !!!Hello World!!!
	return 0;
}
