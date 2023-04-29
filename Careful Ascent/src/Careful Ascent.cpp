//============================================================================
// Name        : Careful.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
double pos[2];
vector<vector<double> > a;
int n;
int w(double s){
	double v = 0;
	for (int i = 0; i < n;i++){
		if (i == 0){
			v += ((a[i][0])*s);
		} else {
			v += ((a[i][0]-a[i-1][1])*s);
		}
		v += (a[i][1]-a[i][0])*(s*a[i][2]);
		cout << s << ' ' << v << " " << i << endl;
		//cin.ignore();
	}
	v += (pos[1]-a[n-1][1])*s;
	cout << v << endl;
	if (abs(v-pos[0]) < 0.000000001){
		return 0;
	}
	if (v < pos[0]){
		return -1;
	}
	if (v > pos[0]){
		return 1;
	}
	return 0;
}
int main() {
	cin >> pos[0];
	cin >> pos[1];
	cin >> n;
	for (int i = 0; i < n;i++){
		double temp[3];
		cin >> temp[0];
		cin >> temp[1];
		cin >> temp[2];
		vector<double> temp2;
		temp2.push_back(temp[0]);
		temp2.push_back(temp[1]);
		temp2.push_back(temp[2]);
		a.push_back(temp2);
	}

	sort(a.begin(), a.end());
	//for (int i = 0; i < n;i++){
	//	cout << a[i][0] << " " << a[i][1] << " " << a[i][2] << endl;
	//}
	double l = 0;
	double h = pos[0]*10;
	double m = (l+h)/2;
	bool f = true;
	//w(1.96078431373);
	//cout << m << " " << w(m) << endl;
	while (f){
		//cout << l << " " << m << " " << h << endl;
		//cin.ignore();
		int c = w(m);
		//cout << c << endl;
		if (c == 0){
			f = false;
			break;
		}
		if (c == -1){
			l = m;
		}
		if (c == 1){
			h = m;
		}
		m = (l+h)/2;
	}
	cout << std::setprecision(12)<< m << endl; // prints !!!Hello World!!!
	return 0;
}
