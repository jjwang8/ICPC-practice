#include <iostream>
#include <vector>
using namespace std;
int n, x,y, k;
vector<int> a[2];
int main(){
    cin >> n;
    for (int i = 0 ; i < n;i++){
        int lim[205][205];
        cin >> x;
        cin >> y;
        for (int l = 0; l < x;l++){
            int temp;
            cin >> temp;
            a[0].push_back(temp);
        }
        for (int l = 0; l < y;l++){
            int temp;
            cin >> temp;
            a[1].push_back(temp);
        }
        cin >> k;
        char temp[4];
        for (int l = 0; l < k;l++){
            cin >> temp[0];
            cin >> temp[1];
            cin >> temp[2];
            cin >> temp[3];
            if (temp[2] == '=' || temp[2] == '>'){
                if (temp[0] == '0' && temp[1] == '0'){
                    for (int j = 0; j < x;j++){
                        a[0][j] -= temp[3]-'0';
                    }
                    for (int j = 0; j < y;j++){
                        a[1][j] -= temp[3] - '0';
                    }
                } else if (temp[0] == '0'){
                    for (int j = 0; j < y;j++){
                        a[1][j] -= temp[3]-'0';
                    }
                } else if (temp[1] == '0'){
                    for (int j = 0; j < x;j++){
                        a[0][j] -= temp[3]-'0';
                    }
                } else {
                    a[0][temp[0]-'0'-1] -= temp[3]-'0';
                    a[1][temp[1]-'0'-1] -= temp[3]-'0';
                }
            } else {
                if (temp[0] == '0' && temp[1] == '0'){
                    for (int j = 0; j < x;j++){
                        for (int t = 0; t < y;t++){
                            lim[j][t] = temp[3]-'0';
                        }
                    }
                } else if (temp[0] == '0'){
                    for (int j = 0; j < y;j++){
                        lim[j][temp[1]-'0'-1] = temp[3]-'0';
                    }
                } else if (temp[1] == '0'){
                    for (int j = 0; j < x;j++){
                        a[0][j] -= temp[3]-'0';
                    }
                } else {
                    a[0][temp[0]-'0'-1] -= temp[3]-'0';
                    a[1][temp[1]-'0'-1] -= temp[3]-'0';
                }
            }
        }

    }

}