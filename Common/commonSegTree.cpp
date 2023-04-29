#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
struct node{
    int value;
    int lpoint;
    int rpoint;
    int cpos;
    int lrange;
    int rrange;
};
class segTree{
    struct lupdate{
        int change;
        string type;
        int lrange;
        int rrange;
    };
    private:
    lupdate lmake(int change, string type, int lrange, int rrange){
        lupdate temp;
        temp.change = change;
        temp.type = type;
        temp.lrange= lrange;
        temp.rrange=rrange;
        return temp;
    }
    void push(int curn){
        int result = bulk[curn].value;
        for (int i = 0; i < lazy[curn].size();i++){
            if (lazy[curn][i].type == "null"){
                continue;
            }
            if (bulk[curn].lrange != bulk[curn].rrange){
                lazy[bulk[bulk[curn].lpoint].cpos].push_back(lazy[curn][i]);
                lazy[bulk[bulk[curn].rpoint].cpos].push_back(lazy[curn][i]);
            }
            //if (!(lazy[curn][i].lrange <= bulk[curn].lrange && lazy[curn][i].rrange >= bulk[curn].rrange)){
            //    continue;
            //}
            if (lazy[curn][i].type == "set"){
                if (type == "sum"){
                    result = lazy[curn][i].change*(bulk[curn].rrange-bulk[curn].lrange+1);
                } else if (type == "min" || type == "max"){
                    result = lazy[curn][i].change;
                }
            } else if (lazy[curn][i].type == "add"){
                if (type == "sum"){
                    result += lazy[curn][i].change*(bulk[curn].rrange-bulk[curn].lrange+1);
                } else if (type == "min" || type == "max"){
                    result += lazy[curn][i].change;
                }
            }
        }
        bulk[curn].value = result;
        lazy[curn].clear();
    }
    public:
    string type;
    vector<node> bulk;
    vector<int> oarray;
    int head;
    vector<vector<lupdate> > lazy;
    lupdate nupdate;
    segTree(string type, vector<int> oarray){
        this->type = type;
        this->oarray = oarray;
        head = create(type, 0, oarray.size()-1).cpos;
        nupdate = lmake(0,"null",-1,-1);
        for (int i = 0; i < head;i++){
            vector<lupdate> temp;
            lazy.push_back(temp);
        }
    }
    node imake(int value, int lpoint, int rpoint, int cpos, int lrange, int rrange){
        node temp;
        temp.value = value;
        temp.lpoint = lpoint;
        temp.rpoint = rpoint;
        temp.cpos = cpos;
        temp.lrange = lrange;
        temp.rrange = rrange;
        return temp;
    }
    node create(string type, int left, int right){
        node temp;
        if (left == right){
            temp = imake(oarray[left], -1, -1, bulk.size(), left, left);
            bulk.push_back(temp);
            return temp;
        }
        node l, r;
        if (abs(left-right) < 2){
            l = create(type, left, left);
            r = create(type, right, right);
            
        } else {
            l = create(type,left,(left+right)/2);
            r = create(type,(left+right)/2+1,right);
        }
        if (type == "sum"){
            temp = imake(l.value+r.value, l.cpos, r.cpos, bulk.size(), left, right);
        } else if (type == "min"){
            temp = imake(min(l.value, r.value), l.cpos, r.cpos, bulk.size(), left, right);
        } else if (type == "max"){
            temp = imake(max(l.value, r.value), l.cpos, r.cpos, bulk.size(), left, right);
        }
        bulk.push_back(temp);
        if (left == 0 && right == oarray.size()-1){
            head = temp.cpos;
        }
        return temp;
    }
    int query(int left, int right, int curn){
        if (curn == -1){
            curn = head;
        }
        int mid = (bulk[curn].lrange+bulk[curn].rrange)/2;
        push(curn);
        if (left <= bulk[curn].lrange && right >= bulk[curn].rrange){
            return bulk[curn].value;
        }
        int lvalue, rvalue;
        if (type == "sum"){
            lvalue = 0;
            rvalue = 0;
        } else if (type == "min"){
            lvalue = INT_MAX;
            rvalue = INT_MAX;
        } else if (type == "max"){
            lvalue = 0;
            rvalue = 0;
        }
        if (left <= mid){
            lvalue = query(left, right, bulk[curn].lpoint);
        } 
        if (right > mid){
            rvalue = query(left, right, bulk[curn].rpoint);
        }
        if (type == "sum"){
            return lvalue + rvalue;
        } else if (type == "min"){
            return min(lvalue, rvalue);
        } else if (type == "max"){
            return max(lvalue, rvalue);
        }
        return -1;
    }
    bool update(int index, int change){
        stack<int> path;
        int curn = head;
        while (1){
            path.push(curn);
            int mid = (bulk[curn].lrange+bulk[curn].rrange)/2;
            if (bulk[curn].lrange == bulk[curn].rrange){
                break;
            }
            if (index <= mid){
                curn = bulk[curn].lpoint;
            } else if (index > mid){
                curn = bulk[curn].rpoint;
            }
        }
        int org = 0;
        while(!path.empty()){
            curn = path.top();
            path.pop();
            if (bulk[curn].lrange == bulk[curn].rrange){
                org = bulk[curn].value;
                bulk[curn].value = change;
                oarray[index] = change;
                continue;
            }
            if (type == "sum"){
                bulk[curn].value = (change-org)+bulk[curn].value;
            } else if (type == "min"){
                bulk[curn].value = min(bulk[bulk[curn].lpoint].value,bulk[bulk[curn].rpoint].value);
            } else if (type == "max"){
                bulk[curn].value = max(bulk[bulk[curn].lpoint].value,bulk[bulk[curn].rpoint].value);
            }
        }
        return 1;
    }
    //no left = right
    void update(int left, int right, int change, string type){
        int curn = head;
        if (right < bulk[curn].lrange || left > bulk[curn].rrange){
            return;
        }
        stack<int> path[2];
        int lequal = head;
        queue<int> coma;
        while (1){
            path[0].push(curn);
            coma.push(curn);
            //lazy[curn].push_back(lmake(change, type, left, right));
            int mid = (bulk[curn].lrange+bulk[curn].rrange)/2;
            if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                lazy[curn].push_back(lmake(change, type, left, right));
                break;
            }
            if (left <= mid){
                curn = bulk[curn].lpoint;
            } else if (left > mid){
                curn = bulk[curn].rpoint;
            }
        }
        curn = head;
        while (1){
            path[1].push(curn);
            //lazy[curn].push_back(lmake(change, type, left, right));
            bool lazya = 0;
            if (curn == coma.front()){
                lequal = coma.front();
                coma.pop();
                lazya = 1;
            }
            int mid = (bulk[curn].lrange+bulk[curn].rrange)/2;
            if (bulk[curn].lrange >= left && bulk[curn].rrange <= right && lazya == 0){
                lazy[curn].push_back(lmake(change, type, left, right));
                break;
            }
            if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                break;
            }
            if (right <= mid){
                curn = bulk[curn].lpoint;
            } else if (right > mid){
                curn = bulk[curn].rpoint;
            }
        }
        int prev = path[0].top();
        while (1){
            curn = path[0].top();
            path[0].pop();
            if (curn == lequal){
                break;
            }
            if (bulk[curn].lrange== bulk[curn].rrange){
                push(curn);
                continue;
            }
            if (prev == curn){
                push(curn);
                continue;
            }
            int result = bulk[curn].value;
            int other;
            if (prev == bulk[curn].lpoint){
                if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                    lazy[bulk[curn].rpoint].push_back(lmake(change, type, left, right));
                }
                other = bulk[curn].rpoint;
            } else {
                if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                    lazy[bulk[curn].lpoint].push_back(lmake(change, type, left, right));
                }
                other = bulk[curn].lpoint;
            }
            push(other);
            if (this->type == "sum"){
                result = bulk[prev].value+bulk[other].value;
            } else if (this->type == "min"){
                result = min(bulk[prev].value,bulk[other].value);
            } else if (this->type == "max"){
                result = max(bulk[prev].value,bulk[other].value);
            }
            bulk[curn].value = result;
        }
        prev = path[1].top();
        while (1){
            curn = path[1].top();
            if (curn == lequal){
                break;
            }
            path[1].pop();
            if (bulk[curn].lrange== bulk[curn].rrange){
                push(curn);
                continue;
            }
            if (prev == curn){
                push(curn);
                continue;
            }
            int result = bulk[curn].value;
            int other;
            if (prev == bulk[curn].lpoint){
                if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                    lazy[bulk[curn].rpoint].push_back(lmake(change, type, left, right));
                }
                other = bulk[curn].rpoint;
            } else {
                if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                    lazy[bulk[curn].lpoint].push_back(lmake(change, type, left, right));
                }
                
                other = bulk[curn].lpoint;
            }
            push(other);
            if (this->type == "sum"){
                result = bulk[prev].value+bulk[other].value;
            } else if (this->type == "min"){
                result = min(bulk[prev].value,bulk[other].value);
            } else if (this->type == "max"){
                result = max(bulk[prev].value,bulk[other].value);
            }
            bulk[curn].value = result;
        }
        while (!path[1].empty()){
            curn = path[1].top();
            path[1].pop();
            if (bulk[curn].lrange >= left && bulk[curn].rrange <= right){
                push(curn);
                continue;
            }
            push(bulk[curn].lpoint);
            push(bulk[curn].rpoint);
            if (this->type == "sum"){
                bulk[curn].value = bulk[bulk[curn].lpoint].value + bulk[bulk[curn].rpoint].value;
            } else if (this->type  == "min"){
                bulk[curn].value = min(bulk[bulk[curn].lpoint].value, bulk[bulk[curn].rpoint].value);
            } else if (this->type == "max"){
                bulk[curn].value = max(bulk[bulk[curn].lpoint].value, bulk[bulk[curn].rpoint].value);
            }
        }
    }
    void force(int left, int right){
        for (int i = left; i <= right;i++){
            query(i,i,-1);
        }
    }
};
vector<int> genRanArray(){
    vector<int> result;
    int temp[10] = {7,5,3,5,6,7,9,2,3,8};
    for (int i = 0; i < 10;i++){
        result.push_back(temp[i]);
    }
    return result;
}
int main()
{
    segTree temp("min", genRanArray());
    cout << temp.query(0,9, -1) << endl;
    temp.update(0,9,-2,"add");
    temp.update(5,9,-2,"add");
    cout << temp.query(0,9,-1) << endl;
    return 0;
}
