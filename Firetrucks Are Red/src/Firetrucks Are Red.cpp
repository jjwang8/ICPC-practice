//============================================================================
// Name        : Firetrucks.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int n;
vector<vector<int> > v(200005);
int vis[200005];
unordered_map<int, vector<int> > num;
vector<int> d(200005);
void f(int s){
	//cout << s << endl;
	for (int i = 0; i < v[s].size();i++){
		//cout << num[v[s][i]].size() << endl;
		for (int l = 0; l < num[v[s][i]].size();l++){
			int to = num[v[s][i]][l];
			//cout << to << " " << s << endl;
			if (vis[to] == 1){
				continue;
			}
			//cout << to << endl;
			vis[to] = 1;
			d[to] = s;
			f(to);
		}



	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n;i++){
		vis[i] = 0;
		d[i] = -1;
		int s;
		cin >> s;
		for (int l = 0; l < s;l++){
			int temp;
			cin >> temp;
			v[i].push_back(temp);
			num[temp].push_back(i);
		}
	}
	vis[0] = 1;
	d[0] = 0;
	f(0);
	string res = "";
	for (int i = 0; i < n;i++){
		if (d[i] == -1){
			cout << "impossible" << endl;
			//return 0;
		} else {
			res += to_string(i+1) + " " + to_string(d[i]+1) + "\n";
		}
	}
	cout << res << endl; // prints !!!Hello World!!!
	return 0;
}
