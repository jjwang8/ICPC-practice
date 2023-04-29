//============================================================================
// Name        : Peculiar.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
priority_queue<int> res;
vector<vector<int> > pre(15);
int lim[2];
void com(int s, int w){
	if (w == n){
		if (s >= lim[0] && s <= lim[1]){
			res.push(-s);
		}
		return;
	}
	if (s >= lim[0]){
		//cout << "aaa" << endl;
		res.push(-s);
		//cout << "b" << endl;
	}
	//cout << s << " " << w << endl;
	com(s, w+1);
	for (int i = 0; i < pre[w].size();i++){
		if (i < 0){
			com(s, w+1);
			continue;
		}
		//cout << pre[w][i] << " " << s << endl;
		if (s*pre[w][i] > lim[1]){
			return;
		}

		com(s*pre[w][i], w+1);
	}
}
int main() {
	while (1){
		int lis[15];
		cin >> n;
		if (n == 0){
			break;
		}
		for (int i = 0; i < n;i++){
			cin >> lis[i];
		}
		cin >> lim[0];
		cin >> lim[1];
		for (int i = 0; i < n;i++){
			int ru = 1;
			while (ru <= lim[1]){
				//cout << ru << endl;
				pre[i].push_back(ru);
				ru *= lis[i];
			}
		}
		//cout << n << " " << lim[0] << " " << lim[1] << endl;
		com(1, 0);
		//cout << res.size() << endl;
		int prev = -1;
		string ans = "none";
		while (!res.empty()){
			int cur = -res.top();
			res.pop();
			//cout << cur << endl;
			if (cur == prev){
				continue;
			}
			if (prev == -1){
				ans = to_string(cur);
			} else {
				ans += "," + to_string(cur);
			}
			prev = cur;
		}
		cout << ans << endl;
		for (int i = 0; i < n;i++){
			pre[i].clear();
		}
	}
	return 0;
}
