//============================================================================
// Name        : Paintings.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;
int t;
int len[10];
int no[10];
string a[10][20];
unordered_map<string, bitset<20> > p;
unordered_map<string, int> loc;
vector<string> b;
int q[20][10000];
int dp(string s, bitset<20> c, int size, int cas) {
	if (q[loc[s]][c.to_ulong()] > 0){
		return q[loc[s]][c.to_ulong()] ;
	}
	bool ran = 0;
	//cout << c << endl;
	if (c.count() == size) {
		return 1;
	}
	int tot = 0;
	for (int i = 0; i < size; i++) {
		if (c[i] == 1) {
			continue;
		}
		string nex = a[cas][i];
		//cout << p[s] << " " << i << endl;
		if (p[s][i] == 1) {
			continue;
		}
		c[i] = 1;
		int res = dp(nex, c, size, cas);
		if (res == -1) {
			c[i] = 0;
			continue;
		}
		c[i] = 0;
		tot += res;
		ran = 1;
	}
	if (ran == 0) {
		return -1;
	}
	q[loc[s]][c.to_ulong()] = tot;
	return tot;
}
int best(string s, bitset<20> c, int size, int cas) {
	bool run = 0;
	//cout << c << endl;
	b.push_back(s);
	if (c.count() == size) {
		return 1;
	}
	//cout << c << endl;
	for (int i = 0; i < size; i++) {
		//cout << c << " " << i << endl;
		if (c[i] == 1) {
			continue;
		}
		string nex = a[cas][i];
		//cout << p[s] << endl;
		if (p[s][loc[nex]] == 1) {
			continue;
		}
		c[i] = 1;
		if (best(nex, c, size, cas) != -1) {
			run = 1;
			break;
		}
		b.pop_back();
		c[i] = 0;
	}
	if (run == 0) {
		return -1;
	}
	return 1;
}
int main() {
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> len[i];
		for (int l = 0; l < len[i]; l++) {
			cin >> a[i][l];
			loc[a[i][l]] = l;
			p[a[i][l]].reset();
		}
		cin >> no[i];
		for (int l = 0; l < no[i]; l++) {
			string temp[2];
			cin >> temp[0];
			cin >> temp[1];
			p[temp[0]][loc[temp[1]]] = 1;
			p[temp[1]][loc[temp[0]]] = 1;
		}
		for (int l = 0; l < len[i];l++){
					for (int j = 0; j < 10000;j++){
						q[l][j] = 0;
					}
				}
		int tot = 0;
		bool run = 0;
		for (int l = 0; l < len[i]; l++) {
			bitset<20> temp;
			temp[l] = 1;
			//cout << temp << endl;
			int res = dp(a[i][l], temp, len[i], i);
			if (res == -1) {
				continue;
			}
			tot += res;
			//cout << tot << " " << l << endl;
			if (run == 0) {
				res = best(a[i][l], temp, len[i], i);
				if (res == -1) {
					b.clear();
					continue;
				} else {
					run = 1;
				}
			}

		}
		cout << tot << endl;
		for (int l = 0; l < b.size(); l++) {
			cout << b[l] << " ";
		}
		b.clear();
		loc.clear();

		//if (i == 0) {
		//	break;
		//}
	}
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
