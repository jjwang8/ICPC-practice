#include <iostream>
#include <vector>
using namespace std;
class unionFind{
    public:
    int *parent;
    int size;
    unionFind(int size){
        this->size=size;
        parent = new int[size];
        for (int i = 0; i < size;i++){
            parent[i] = i;
        }
    }
    void format(vector<int> in){
        for (int i = 0; i < in.size();i++){
            parent[i] = in[i];
        }
    }
    int find(int node){
        if (parent[node] == node){
            return node;
        }
        return find(parent[node]);
    }
    pair<int, int> join(int joine, int target){
        pair<int, int> result;
        if (find(target) == find(joine)){
            return make_pair(0, find(target));
        }
        parent[find(joine)] = find(target);
        return make_pair(1, find(target));
    }
};
int main()
{
    
    return 0;
}
