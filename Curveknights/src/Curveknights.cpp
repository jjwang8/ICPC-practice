//============================================================================
// Name        : Curveknights.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n,m;
int a[100];
struct two{
	int x;
	int y;
};
vector<vector<two> > v(1000);
int res[100] = {};
int p[100] = {};
int main() {
	cin >> n;
	cin >> m;
	bool b[100];
	for (int i = 0; i < n;i++){
		res[i] = 0;
		b[i] = false;
		p[i] = 0;
		cin >> a[i];
	}
	for (int i = 0; i < m;i++){
		int temp[3];
		cin >> temp[0];
		cin >> temp[1];
		cin >> temp[2];
		two temp2;
		p[temp[0]]++;
		temp2.x = temp[0];
		temp2.y = temp[2];
		v[temp[1]].push_back(temp2);

	}
	queue<int> q;
	for (int i = 0; i < n;i++){
		res[i] = a[i];
		if (p[i] == 0){
			q.push(i);
			res[i] = a[i];
		}
	}

	while(!q.empty()){
		int cur = q.front();
		q.pop();
		if (b[cur] == true){
			continue;
		}
		b[cur] = 1;
		for (int i = 0; i < v[cur].size();i++){
			q.push(v[cur][i].x);
			res[v[cur][i].x] += res[cur]*v[cur][i].y;
			//cout << res[v[cur][i].x] << " " << v[cur][i].x  << " "<< cur << endl;
		}
	}
	for (int i = 0; i < n;i++){
		cout << res[i] << endl;
	}
	return 0;
}
