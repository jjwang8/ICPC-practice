#include <iostream>
#include <climits>
using namespace std;
int n,p;
int main()
{
    cin >> n;
    cin >> p;
    int a[100005];
    for (int i = 0; i < n;i++){
        cin >> a[i];
        a[i] -= p;
    }
    int mi = INT_MAX;
    int ru = 0;
    int index = 0;
    for (int i = 0; i < n;i++){
        ru += a[i];
        if (ru < mi){
            mi = ru;
            index = i;
        }
    } 
    int ma = -100000;
    int runn = 0;
    int index2 = 0;
    for (int i = 0; i < n;i++){
        runn += a[i];
        if (ma < runn){
            ma = runn;
            index2 = i;
        }
    }
    int ans = 0;
    int ans2 = 0;
    if (ma == 0 && mi == n-1){
        cout << a[0] << endl;
        return 0;
    }
    int oindex = index;
    if (index2 > index){
        if (mi >= 0){
            cout << runn << endl;
            return 0;
        }
        for (int i = index+1; i <= index2;i++){
            ans += a[i];
        }
        cout << ans << endl;
    } else {
        mi = INT_MAX;
        runn = 0;
        for (int i = 0; i <= index2;i++){
            runn += a[i];
            if (mi > runn){
                index = i;
                mi = runn;
            }
        }
        if (mi >= 0){
            ans = runn;
        } else {
            for (int i = index+1; i <= index2;i++){
                ans += a[i];
            }
        }
        runn = 0;
        ma = -100000;
        for (int i = oindex; i < n;i++){
            runn += a[i];
            if (ma < runn){
                ma = runn;
                index2 = i;
            }
        }
        for (int i = oindex+1; i <= index2;i++){
            ans2 += a[i];
        }
        cout << max(ans, ans2) << endl;
    }
    return 0;
}
