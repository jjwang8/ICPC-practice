#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> a;
int threat[500005] = {};
int main()
{
    cin >> n;
    for (int i = 0; i < n;i++){
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i =1; i < n;i++){
        threat[i] = threat[i-1]+a[i-1];
    }
    
    return 0;
}
