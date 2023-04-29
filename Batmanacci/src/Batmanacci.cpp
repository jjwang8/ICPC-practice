//============================================================================
// Name        : Batmanacci.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
string a[50];
int n,k;
int main() {
	a[0] = "n";
	a[1] = "a";
	cout << "n" << endl;
	cout << "a" << endl;
	for (int i = 2; i < 20;i++){
		a[i] = a[i-2]+a[i-1];
		cout << a[i] << endl;
	}
	cin >> n;
	cin >> k;
	k--;
	k = k-2;
	k = k%3;
	string b = "ANA";
	if (n <= 2){
		if (n == 1){
			cout << "N" << endl;
		}
		if (n == 2){
			cout << "A" << endl;
		}
		return 0;
	}
	cout << b[k] << endl;
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
