#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n = -1, m = -1;
int main()
{
    bool imp = false;
    while (1){
        imp = false;
        cin >> n;
        cin >> m;
        if (n == 0 && m == 0){
            break;
        }
        vector<int> a;
        vector<int> b;
        for (int i = 0; i < n;i++){
            int temp;
            cin >> temp;
            a.push_back(temp);
        }
        for (int i = 0; i < m;i++){
            int temp;
            cin >> temp;
            b.push_back(temp);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int l = -1;
        int ans = 0;
        for (int i = 0; i < n;i++){
            for (l = l+1; l < m;l++){
                if (a[i] <= b[l]){
                    ans += b[l];
                    break;
                }
            }
            if (l == m){
                cout << "Loowater is doomed!" << endl;
                imp = true;
                break;
            }
            if (imp){
                break;
            }
        }
        if (imp){
            continue;
        }
        cout << ans << endl;
    }
    
    return 0;
}
