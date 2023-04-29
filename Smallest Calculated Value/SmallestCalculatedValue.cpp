#include <iostream>
#include <climits>
using namespace std;
int a[3];

int main()
{
    cin >> a[0];
    cin >> a[1];
    cin >> a[2];
    int best = INT_MAX;
    for (int i = 0; i < 4;i++){
        for (int l = 0; l < 4;l++){
            int cur = a[0];
            if (i == 0){
                cur += a[1];
            }
            if (i == 1){
                cur -= a[1];
            }
            if (i == 2){
                cur *= a[1];
            }
            if (i == 3 && cur%a[1] == 0){
                cur = cur/a[1];
            }
            if (l == 0){
                cur += a[2];
            }
            if (l == 1){
                cur -= a[2];
            }
            if (l == 2){
                cur *= a[2];
            }
            if (l == 3 && cur%a[2] == 0){
                cur = cur/a[2];
            }
            if (cur >= 0){
                //cout << i << l << endl;
                best = min(cur, best);
            }
        }
    }
    cout << best << endl;
    return 0;
}
