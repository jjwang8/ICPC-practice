//============================================================================
// Name        : Emptying.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;
int h, w;
int a[600][600];
int s[2];
priority_queue<pair<int, pair<int, int> > > q;
vector<pair<int, int> > g;
int lvl[600][600];
bool ok(int x, int y) {
	if (x < 0 || y < 0) {
		return false;
	}
	if (x >= h || y >= w) {
		return false;
	}
	return true;
}
int main() {
	cin >> h;
	cin >> w;
	for (int i = 0; i < h; i++) {
		for (int l = 0; l < w; l++) {
			lvl[i][l] = INT_MAX;

			cin >> a[i][l];
			//cout << a[i][l] << i << l << endl;
		}
	}
	cin >> s[0];
	cin >> s[1];
	q.push(make_pair(-a[s[0]-1][s[1]-1], make_pair(s[0]-1, s[1]-1)));
	for (int i = 0 - 1; i <= 1; i++) {
		for (int l = -1; l <= 1; l++) {
			if (i == 0 && l == 0) {
				continue;
			}
			g.push_back(make_pair(i, l));
		}
	}
	while (!q.empty()) {
		pair<int, pair<int, int> > cur = q.top();
		q.pop();
		cur.first *= -1;
		//cout << cur.first << " " << cur.second.first << " " << cur.second.second << endl;
		if (cur.first > lvl[cur.second.first][cur.second.second]){
			continue;
		}
		for (int i = 0; i < 8; i++) {
			pair<int, pair<int, int> > res;
			int cord[2] = { cur.second.first + g[i].first, cur.second.second
					+ g[i].second };
			if (!ok(cord[0], cord[1]) || a[cord[0]][cord[1]] >= 0) {
				continue;
			}
			if (cur.first >= lvl[cord[0]][cord[1]]){
				continue;
			}
			if (a[cord[0]][cord[1]] < cur.first) {
				res.first = -cur.first;
				res.second.first = cord[0];
				res.second.second = cord[1];
				lvl[cord[0]][cord[1]] = cur.first;
				q.push(res);
			} else {
				res.first = -a[cord[0]][cord[1]];
				res.second.first = cord[0];
				res.second.second = cord[1];
				lvl[cord[0]][cord[1]] = a[cord[0]][cord[1]];
				q.push(res);
			}
		}
	}
	int tot =0;
	for (int i = 0; i < h;i++){
		for (int l = 0; l < w;l++){
			if (lvl[i][l] > 0){
				continue;
			}
			//cout << lvl[i][l] << " ";
			tot += -lvl[i][l];
		}
		//cout << endl;
	}
	cout <<tot << endl; // prints !!!Hello World!!!
	return 0;
}
