#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
struct p{
        double x;
        double y;
        p(double x=0, double y=0) 
        : x(x), y(y)
        {
        }
        bool operator==(const p& key) const {
            return abs(x-key.x) < 0.0000001 && abs(y-key.y) < 0.0000001 ;
        }
        bool operator>(const p& key) const {
            if (x > key.x){
                return true;
            } else if (abs(x-key.x) < 0.0000001){
                return y > key.y;
            } else {
                return false;
            }
        }
        bool operator>=(const p& key) const {
            if (x > key.x){
                return true;
            } else if (abs(x-key.x) < 0.0000001){
                return y > key.y || abs(y-key.y) < 0.0000001;
            } else {
                return false;
            }
        }
        p operator+(const p& key){
            return p(x+key.x, y+key.y);
        }
    };
p mpoint (double x, double y){
    p temp;
    temp.x = x;
    temp.y = y;
    return temp;
}
class Geo{
    public:
    vector<pair<p, p> > llist;
    Geo(){

    }
    Geo(vector<pair<p, p> > llist){
        this->llist = llist;
    }
    int ortientation(p p1, p p2, p p3){
        double val = (p2.y - p1.y) * (p3.x-p2.x) - (p2.x-p1.x) * (p3.y - p2.y);
        if (abs(val) < 0.0000001){
            return -1;
        } else if (val > 0){
            return 1;
        } else if (val < 0){
            return 0;
        }
    }
    double dist(p p1, p p2){
        return sqrt((p1.x-p2.x)*(p1.x-p2.x) - (p1.y-p2.y)*(p1.y-p2.y));
    }
    //line p1, check, line p2
    bool onSegment(p p1, p p3, p p2) {
        if (max(p1.x, p3.x) >= p2.x && p2.x >= min(p1.x, p3.x) &&
            max(p1.y, p3.y) >= p2.y && p2.y >= min(p1.y, p3.y))
        return true;
        return false;
    }
    pair<p,p> cross(pair<p, p> l1, pair<p,p> l2){
        double slope[2] = {(l1.second.y-l1.first.y)/(l1.second.x-l1.first.x), 
                        (l2.second.y-l2.first.y)/(l2.second.x-l2.first.x)};
        double yint[2] = {l1.first.y - slope[0]*l1.first.x, l2.first.y - slope[1]*l2.first.x};
        if (abs(slope[0]-slope[1]) < 0.0000001){
            if (l1.first == l2.first || l1.first == l2.second){
                return make_pair(l1.first, l1.first);
            } else if (l1.second == l2.first || l1.second == l2.second){
                return make_pair(l1.second, l1.second);
            }
            if (onSegment(l1.first, l2.first, l1.second) && onSegment(l1.first, l2.second, l1.second)){
                return l2;
            }
            if (onSegment(l2.first, l1.first, l2.second) && onSegment(l2.first, l1.second, l2.second)){
                return l1;
            }
        }
        double x = (yint[0]-yint[1])/(slope[0]-slope[1]);
        double y = slope[0]*x+yint[0];
        return make_pair(mpoint(x,y), mpoint(x,y));
    }
    int intersect(pair<p, p> l1, pair<p,p> l2){
        int o[4] = {ortientation(l1.first, l1.second, l2.first), 
                    ortientation(l1.first, l2.second, l2.second),
                    ortientation(l2.first, l2.second, l1.first),
                    ortientation(l2.first, l2.second, l1.second)};
        if (o[0] != o[1] && o[2] != o[3]){
            return 1;
        }
        if (o[0] == -1 && )
    }
    int circleSections(vector<pair<p, p> > cuts, double r){
        int res = 1;
        for (int i = 0; i < cuts.size();i++){
            for (int l = i+1; l < cuts.size();l++){
                int inter = intersect(cuts[i], cuts[l]);
                if (inter == 2){
                    continue;
                }
                res++;
                if (inter == 1){
                    p mid = cross(cuts[i], cuts[l]).first;
                    if (dist(mid, mpoint(0,0)) > r){
                        continue;
                    }
                    res++;
                } else if (inter == 0){
                    continue;
                } 
            }
        }
        return res;
    }
};
    
int main()
{
    
    
    system("pause");
    return 0;
}
