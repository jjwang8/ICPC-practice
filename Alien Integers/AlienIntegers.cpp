#include <iostream>
#include <string>
#include <climits>
using namespace std;
string a;
string up(string x){
    long h[15] = {};
    if (x.length() > 10){
        return "-1";
    }
    string ans = " ";
    for (long i = 0; i < x.length();i++){
        h[x[i]-'0'] = 1;
        ans += " ";
    }
    for (long i = 0; i <= x.length();i++){
        long con = 0;
        for (long l = 0; l <= 9;l++){
            if (h[l]){
                con++;
                continue;
            }
            ans[i] = (char)(l+'0');
            break;
        }
        if (con == 10){
            return "-1";
        }
    }
    return ans;
}
string mup(string x){
    long h[15] = {};
    string ans = "";
    for (long i = 0; i < x.length();i++){
        h[x[i]-'0'] = 1;
        ans += " ";
    }
    for (long i = x[0]-'0'; i <= 9;i++){
        if (h[i] == 0){
            ans[0] = (char)(i+'0');
            break;
        }
        if (i == 9){
            return "-1";
        }
    }
    for (long i = 1; i < x.length();i++){
        long con = 0;
        for (long l = 0; l <= 9;l++){
            if (h[l]){
                con++;
                continue;
            }
            ans[i] = (char)(l+'0');
            break;
        }
        if (con == 10){
            return "-1";
        }
    }
    return ans;
}
string midd(string x){
    long h[15] = {};
    string ans = "";
    for (long i = 0; i < x.length();i++){
        h[x[i]-'0'] = 1;
        ans += " ";
    }
    for (long i = x[0]-'0'; i >= 0;i--){
        if (h[i] == 0){
            ans[0] = (char)(i+'0');
            break;
        }
        if (i == 9){
            return "-1";
        }
    }
    for (long i = 1; i < x.length();i++){
        long con = 0;
        for (long l = 9; l >= 0;l--){
            if (h[l]){
                con++;
                continue;
            }
            ans[i] = (char)(l+'0');
            break;
        }
        if (con == 10){
            return "-1";
        }
    }
    return ans;
}
string target(string x, long s){
    long h[15] = {};
    string ans = "";
    for (long i = 0; i < x.length();i++){
        h[x[i]-'0'] = 1;
    }
    for (long i = 0; i < s;i++){
        ans += "0";
    }
    for (long i = 0; i < s;i++){
        long con = 0;
        for (long l = 9; l >= 0;l--){
            if (h[l]){
                con++;
                continue;
            }
            ans[i] = (char)(l+'0');
            break;
        }
        if (con == 10){
            return "-1";
        }
    }
    return ans;
}
int main()
{
    cin >> a;
    long upa = abs(stol(up(a))-stol(a));
    long midu = abs(stol(mup(a))-stol(a));
    long mdo = abs(stol(midd(a)) - stol(a));
    long best = LONG_MAX;
    pair<string, string> w (" ", "-999999999");
    if (up(a) != "-1" && best >= upa){
        if (upa == best){
            w.second = up(a);
        } else {
            w.first = up(a);
        }
        best = min(best, upa);
        
    }
    if (mup(a) != "-1" && best >= midu){
        if (midu == best){
            w.second = mup(a);
        } else {
            w.first = mup(a);
        }
        best = min(best, midu);
        
    }
    if (midd(a) != "-1" && best >= mdo){
        best = min(best, mdo);
        if (mdo == best){
            w.second = midd(a);
        } else {
            w.first = midd(a);
        }
    }
    for (long i = 1; i <= a.length();i++){
        if (target(a,i) != "-1"){
            if (abs(stol(target(a,i))-stol(a)) <= best){
                if (abs(stol(target(a,i))-stol(a)) == best){
                    w.second = target(a,i);
                } else {
                    best = abs(stol(target(a,i))-stol(a));
                }
                w.first = target(a,i);
            }
        }
    }
    if (w.first == " "){
        cout << "-1" << endl;
        return 0;
    }
    if (abs(stol(w.second)-stol(a)) == abs(stol(w.first)-stol(a))){
        cout << w.second << " " << w.first << endl;
    } else {
        if (abs(stol(w.second)-stol(a)) < abs(stol(w.first)-stol(a))){
            cout <<  w.second << endl;
        } else {
            cout << w.first << endl;
        }
    }
    return 0;
}
