#include <iostream>
#include <iomanip>
using namespace std;
int n,m;
double a[3000];
double f(int x, int y){
    if (x == 0){
        return 0;
    }
    if (y == 0){
        return 1;
    }
    return f(x,y-1)*a[x+y-2] + f(x-1,y)*(1-a[x+y-2]);
}
int main(){
    cin >> n;
    cin >> m;
    for (int i = 0; i < n+m-1;i++){
        cin >> a[i];
    }
    cout << setprecision(7) << f(n,m) << endl;
}