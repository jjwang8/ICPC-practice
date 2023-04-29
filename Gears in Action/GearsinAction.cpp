#include <iostream>
#include <vector>
using namespace std;
long long t, n;
long long inv(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
 
    if (m == 1)
        return 0;
 
    // Apply extended Euclid Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
 
        t = m;
 
        // m is remainder now, process same as
        // euclid's algo
        m = a % m, a = t;
 
        t = x0;
 
        x0 = x1 - q * x0;
 
        x1 = t;
    }
 
    // Make x1 positive
    if (x1 < 0)
        x1 += m0;
 
    return x1;
}
long long findMinX(long long num[], long long rem[], long long k)
{
    // Compute product of all numbers
    long long prod = 1;
    for (long long i = 0; i < k; i++)
        prod *= num[i];
 
    // Initialize result
    long long result = 0;
 
    // Apply above formula
    for (long long i = 0; i < k; i++) {
        long long pp = prod / num[i];
        result += rem[i] * inv(pp, num[i]) * pp;
    }
 
    return result % prod;
}
long long gcdExtended(long long a, long long b, long long *x, long long *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    long long x1, y1; // To store results of recursive call
    long long gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of
    // recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
long long lcm(long long a, long long b)
{
    long long x, y;
    return (a / gcdExtended(a, b, &x, &y)) * b;
}
int main()
{
    cin >> t;
    vector<pair<long long, long long> > a;
    while (t > 0){
        t--;
        cin >> n;
        for (long long i = 0; i < n;i++){
            pair<long long, long long> temp;
            cin >> temp.first;
            cin >> temp.second;
            a.push_back(temp);
        }
        long long ans = a[0].second;
        bool impos = false;
        for (long long i = 1; i < n;i++){
            long long num[] = {a[i].first, a[i-1].first};
            long long dist;
            if (a[i].second-ans%a[i].first < 0){
                dist = a[i].second + (a[i].first-(ans%a[i].first));
            } else {
                dist = a[i].second-ans%a[i].first;
            }
            long long rem[] = {dist, 0};
            long long x,y;
            long long gcd = gcdExtended(a[i].first, a[i-1].first, &x, &y);

            if (gcd != 1){
                if (dist%gcd != 0){
                    impos = 1;
                    i = INT_MAX;
                    cout << "impossible" << endl;
                    continue;
                } else{
                    long long cyl = dist/gcd;

                }
            } 
            long long rot = findMinX(num, rem, sizeof(num) / sizeof(num[0]));
            ans += rot;
            a[i].first = lcm(a[i].first, a[i-1].first);
        }
        if (impos){
            continue;
        }
        cout << ans << endl;
    }
    return 0;
}
