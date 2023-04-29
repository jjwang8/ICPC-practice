#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int t, n;
int main()
{
    double a[160];
   
    cin >> t;
    while (t){
        t--;
        cin >> n;
        vector<pair<int, double> > party;
        for (int i = 0; i < n;i++){
            pair<int, double> temp;
            cin >> temp.first;
            cin >> temp.second;
            temp.second = temp.second/100;
            party.push_back(temp);
        }
        fill(a, a+155, 0);
        a[0] = 1;
        double ma = 0;
        for (int i = n-1; i >= 0;i--){
            for (int l = 150; l >= 0;l--){
                if (abs(a[l]) < 0.0000001){
                    continue;
                }
                if (l+party[i].first > 150){
                    continue;
                }
                a[l+party[i].first] = max(a[l+party[i].first], a[l]*party[i].second);
                if (l > 75){
                    ma = max(ma, a[l]);
                }
            }
        }
        cout << setprecision(6) << ma*100 << endl;
    }
    return 0;
}
