#include <iostream>
#include <vector>
#include <unordered_map>
#include<bitset>
#include <queue>
#include <algorithm>
using namespace std;
int n;
vector<string> a;
class strings{
    private:
    struct node{
        char let;
        int child[26];
        int par;
        vector<int> cl;
        int count;
        unordered_map<string, bool> con;
    };
    public:
    vector<string> slist;
    string ms;
    int size;
    vector<node> trie;
    strings (vector<string> slist, int size){
        this->slist = slist;
        this->size = size;
        sort(slist.begin(), slist.end());
        create();
    } 
    strings(string ms){
        this->ms = ms;
        size = 1;
    }
    string reverse(string key){
        for (int i = key.size(); i >= 0;i--){
            
        }
    }
    vector<int> contains(string key){
        vector<int> result;
        queue<int> table;
        for (int i = 0; i < ms.length();i++){
            int cur = 0;
            if (ms[i] == key[0]){
                table.push(0);
            }
            int s = table.size();
            for (int l = 0; l < s;l++){
                int temp = 0;
                if (key[table.front()] == ms[i]){
                    temp = table.front()+1;
                } 
                if (temp == key.length()){
                    result.push_back(i-(key.length()-1));
                } else {
                    table.push(temp);
                }
                table.pop();
            }
            

        }
        return result;
    }
    pair<int, int> hash(string key, char base){
        int result[2] = {0,0};
        int p = 29791, m[2] = {1000000000+7, 1000000000+9};
        long pow = 1;
        for (int i = 0; i < key.length();i++){
            result[0] = (result[0]+(key[i]-base+1)*pow)%m[0];
            pow = (pow*p)%m[0];
        }
        pow = 1;
        for (int i = 0; i < key.length();i++){
            result[1] = (result[1]+(key[i]-base+1)*pow)%m[1];
            pow = (pow*p)%m[1];
        }
        return make_pair(result[0], result[1]);
    }
    node imake(char let, int par){
        node result;
        result.let = let;
        result.par = par;
        fill(result.child, result.child+26, -1);
        result.count = 0;
        return result;
    }
    void icreate(int index, string key){
        int cur = slist[index][0]-'a';
        string tar = slist[index];
        int i;
        for (i = 1; i < tar.length();i++){
            if (trie[cur].child[tar[i]-'a'] != -1){
                cur = trie[cur].child[tar[i]-'a'];
            } else {
                break;
            }
        }
        for (i = i; i < tar.length();i++){
            trie[cur].child[tar[i]-'a'] = trie.size();
            trie[cur].cl.push_back(trie.size());
            trie.push_back(imake(tar[i], cur));
            cur = trie.size()-1;
        }
        trie[cur].count++;
    }
    void create(){
        for (int i = 0; i < 26;i++){
            trie.push_back(imake(i+'a', -1));
        }
        for (int i = 0; i < size;i++){
            icreate(i, slist[i]);
        }
    }
    int count(string key){
        int cur = key[0]-'a';
        int i;
        for (i = 1; i < key.length();i++){
            if (trie[cur].child[key[i]-'a'] != -1){
                cur = trie[cur].child[key[i]-'a'] ;
            } else {
                break;
            }
        }
        if (key.length() == 1){
            return trie[cur].count;
        }
        if (i == key.length()){
            return trie[cur].count;
        } else {
            return 0;
        }
    }
    template <typename T>
    int binSeach(vector<T> in, T key){
        int l = 0;
        int h = in.size()-1;
        int m = (l+h)/2;
        while (in[m] != key){
            if (abs(l-h) < 2){
                return l;
            }
            if (in[m] > key){
                h = m;
            } else if (in[m] < key){
                l = m;
            }
            m = (l+h)/2;
        }
        return m;
    }
    template <typename T>
    int longSubSeq(vector<T> list){
        vector<T> result;
        for (int i = 0; i < list.size();i++){
            if (result.size() == 0){
                result.push_back(list[i]);
                continue;
            }
            if (list[i] >= result[result.size()-1]){
                result.push_back(list[i]);
                continue;
            }
            if (list[i] < result[0]){
                result[0] = list[i];
                continue;
            }
            int index = binSeach<T>(result, list[i]);
            result[index+1] = list[i];
        }
        return result.size();
    }
};
int main()
{
    cin >> n;
    for (int i = 0; i < n;i++){
        string temp;
        cin >> temp;
        a.push_back(temp);
    }
    strings lll(a, n);

    return 0;
}
