//============================================================================
// Name        : Conquest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <set>
using namespace std;
int r,c,n;
int a[10005][2];
int b[1000][1000];
queue<pair<int, int> > q;
int main() {
	cin >> r;
	cin >> c;
	cin >> n;
	for (int i = 0; i < r;i++){
			for (int l = 0; l < c;l++){
				b[i][l] = 0;
			}
		}
	for (int i = 0; i < n;i++){
		cin >> a[i][0];
		cin >> a[i][1];
		a[i][0]--;
		a[i][1]--;
		b[a[i][0]][a[i][1]] = 1;
	}

	for (int i = 0; i < n;i++){
		q.push(make_pair(a[i][0], a[i][1]));

	}
	int tot = 0;
	q.push(make_pair(-1,-1));
	while (!q.empty()){
		pair<int, int> cur = q.front();
		q.pop();
		cout << cur.first << cur.second << endl;
		if (cur.first == -1 && cur.second == -1){
			tot++;
			if (q.size() == 0){
				break;
			}

			q.push(make_pair(-1,-1));
			continue;
		}

		int t[4][2] = {{1,0}, {-1, 0}, {0, 1}, {0,-1}};
		for (int i = 0; i < 4;i++){
			if (cur.first+t[i][0] < 0 || cur.second+t[i][1] < 0){
				continue;
			}
			if (cur.second+t[i][1] >= c || cur.first+t[i][0] >= r){
				continue;
			}
			if (b[cur.first+t[i][0]][cur.second+t[i][1]] != 1){
				b[cur.first+t[i][0]][cur.second+t[i][1]] = 1;
				pair<int, int> temp;
				temp.first = cur.first+t[i][0];
				temp.second = cur.second+t[i][1];
				q.push(temp);

			}
		}
	}
	cout << tot;
	return 0;
}
