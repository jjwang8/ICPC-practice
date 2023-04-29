#include <iostream>
using namespace std;
int a,b;
int norm(int x){
    return -x+a;
}
int main()
{
    cin >> a;
    cin >> b;
    int sum = 0;
    int cur = b;
    int sum2 = 0;
    int sum3 = 0;
    for (int i = 0; i < a;i++){
        sum2 += norm(i);
    }
    if (b%3 == 0){
        for (int i = 0; i <= b;i++){
            cout << cur << endl;
            sum3 += cur;
         sum += cur-norm(i);
            if (i == (2.0/3.0)*b){
                cur--;
            } else if (i > (2.0/3.0)*b){
                cur = cur-2;
            } else if (i%2 == 1){
                cur--;
            }
        }
    }
    if (b%3 == 1){
        for (int i = 0; i <= (2.0/3.0*(float)b);i++){
         sum += cur-norm(i);
            if (i%2 == 1){
                sum--;
            }
        }
    }
    cout << sum  << " " << sum2 << " "<< sum3 << endl;
    return 0;
}
