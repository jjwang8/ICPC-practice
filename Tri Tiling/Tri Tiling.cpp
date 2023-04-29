#include <iostream>
using namespace std;
int n = 0;
int main()
{
    int kp[40];
    fill(kp, kp+36, 0);
    kp[0] = 1;
    for (int i = 0; i <= 30;i++){
        if (kp[i] > 0){
            kp[i+2] += kp[i]*3;
            for (int l = 4; l <= 30;l = l+2){
                if (i+l > 35){
                    continue;
                }
                kp[i+l] += kp[i]*2;
            }
        }
    }
    //cout << kp[30] << endl;
    cin >> n;
    while (n != -1){
        cout << kp[n] << endl;
        //cout << countWays(n) << endl;
        cin >> n;
    }
    return 0;
}
