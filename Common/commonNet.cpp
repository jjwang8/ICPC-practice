#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class networkFlow{
    public:
    int sx;
    vector<vector<pair<int, int> > > p;
    int *lvl;   
    networkFlow(int sx){
        this->sx = sx;
        for (int i = 0; i < sx;i++){
            vector<pair<int, int> > temp;
            p.push_back(temp);
        }
        lvl = new int[sx+5];
        
    }
    bool level(){
        fill(lvl,lvl+sx+5,INT_MAX);
        queue<pair<int, int> > q;
        q.push(make_pair(0, 0));
        bool result = false;
        while (!q.empty()){
            pair<int, int> cur = q.front();
            q.pop();
            if (lvl[cur.first] <= cur.second+1){
                continue;
            }
            lvl[cur.first] = cur.second;
            if (cur.first == sx-1){
                result = true;
            }
            for (int i = 0; i < p[cur.first].size();i++){
                if (lvl[p[cur.first][i].first] <= cur.second+1){
                    continue;
                }
                if (p[cur.first][i].second <= 0){
                    continue;
                }
                q.push(make_pair(p[cur.first][i].first, cur.second+1));
            }
        }
        return result;
    }
    int flow(int cur, int sentf){
        int total = 0;
        if (cur == sx-1){
            return sentf;
        }
        for (int i = 0; i < p[cur].size();i++){
            if (lvl[p[cur][i].first] != lvl[cur]+1){
                continue;
            }
            if (p[cur][i].second <= 0){
                continue;
            }
            int csend = min(sentf, p[cur][i].second);
            int subtot = flow(p[cur][i].first, csend);
            p[cur][i] = make_pair(p[cur][i].first, p[cur][i].second-subtot);
            p[p[cur][i].first].push_back(make_pair(cur, subtot));
            total += subtot;
            sentf -= subtot;
        }
        return total;
    }
    int getMax(){
        bool result = level();
        int total = 0;
        while (result){
            total += flow(0, INT_MAX);
            result = level();
        }
        return total;
    }
    
};
class unweightBipart{
    public:
    int sx;
    int *lnode;
    int *rnode;
    vector<vector<int> > p;
    vector<vector<int> > match;
    unweightBipart(int sx){
        lnode = new int[sx+5];
        rnode = new int[sx+5];
        this->sx = sx;
        for (int i = 0; i < sx;i++){
            vector<int> temp;
            p.push_back(temp);
            temp.push_back(-1);
            match.push_back(temp);
        }
        fill(lnode, lnode+sx, -1);
    }
    void setL(int toset[], int size){
        for (int i = 0; i < size;i++){
            lnode[toset[i]] = 1;
        }
    }
    vector<vector< int> > fAPath(){
        queue<pair<int, pair<bool, int> > > q;
        int vis[sx+5];
        vector<vector<int> > res;
        fill(vis, vis+sx,0);
        int count = 0;
        for (int i = 0; i < sx;i++){
            if (lnode[i] == -1){
                continue;
            }
            if (match[i][0] != -1){
                continue;
            }
            q.push(make_pair(i, make_pair(0, count++)));
            vector<int> temp;
            temp.push_back(i);
            res.push_back(temp);
            vis[i] = 1;
        }
        while (!q.empty()){
            pair<int, pair<bool, int> > cur = q.front();
            q.pop();
            count = 0;
            for (int i = 0; i < p[cur.first].size();i++){
                if (match[cur.first][0] == p[cur.first][i] && cur.second.first == 0){
                    continue;
                }
                if (match[cur.first][0] != p[cur.first][i] && cur.second.first == 1){
                    continue;
                }
                if (vis[p[cur.first][i]]){
                    continue;
                }
                vis[p[cur.first][i]] = 1;
                
                if (count > 0){
                    vector<int> temp;
                    temp = res[cur.second.second];
                    res.push_back(temp);
                    res[res.size()-1][res[res.size()-1].size()-1] = p[cur.first][i];
                    q.push(make_pair(p[cur.first][i], make_pair(!cur.second.first, res.size()-1)));
                } else {
                    res[cur.second.second].push_back(p[cur.first][i]);
                    count++;
                    q.push(make_pair(p[cur.first][i], make_pair(!cur.second.first, cur.second.second)));
                }
            }
        }
        return res;
    }
    void addM(vector<int> ps){
        
        for (int i = 0; i < ps.size();i = i+2){
            match[ps[i]].erase(match[ps[i]].begin());
            match[ps[i+1]].erase(match[ps[i+1]].begin());
            match[ps[i]].push_back(ps[i+1]);
            match[ps[i+1]].push_back(ps[i]);
        }
    }
    int maxMatch(){
        int res =0;
        while(1){
            vector<vector<int> > APath = fAPath();
            vector<int> work;
            for (int i = 0; i < APath.size();i++){
                if (APath[i].size()%2 ==0 && APath.size() != 0){
                    work.push_back(i);
                }
            }
            if (work.size() == 0){
                break;
            }
            int vis[sx+5];
            fill(vis, vis+sx, 0);
            for (int i = 0; i < work.size();i++){
                bool cont = 0;
                for (int l = 0; l < APath[work[i]].size();l++){
                    if (vis[APath[work[i]][l]] == 1){
                        cont = 1;
                        break;
                    }
                    vis[APath[work[i]][l]] = 1;
                }
                if (cont){
                    continue;
                }
                addM(APath[work[i]]);
                res++;
            }
        } 
        return res;
    }
};
class weightBipart{
    public:
    int r,c;
    vector<vector<int> > matrix;
    vector<vector<bool > > notu;
    vector<vector<int> > matrix2;
    bool stars[250][250];
    bool cover[2][250];
    int con;
    bool star[2][250];
    weightBipart(int r, int c){
        this->c = c;
        this->r = r;
        con = 0;
        for (int i = 0; i < r;i++){
            vector<bool > temp(c);
            notu.push_back(temp);
        }
        for (int i = 0; i < max(r,c);i++){
            star[0][i] = 0;
            star[1][i] = 0;
            for (int l = 0; l < max(r,c);l++){
                stars[i][l] = 0;
            }
        }
    }
    void format(){
        if (r > c){
            for (int i = 0; i < r;i++){
                for (int l = matrix[i].size(); l < c;l++){
                    matrix[i].push_back(INT_MAX);
                }
            }
        } else if (c > r){
            for (int i = matrix.size(); i < c;i++){
                vector<int> temp;
                for (int l = 0; l < c;l++){
                    temp.push_back(INT_MAX);
                }
                matrix.push_back(temp);
            }
        }
        for (int i = 0; i < max(r,c);i++){
            for (int l = 0; l < max(r,c);l++){
                if (matrix[i][l] == -1){
                    matrix[i][l] = INT_MAX;
                }
            }
        }
        for (int i = 0; i < r;i++){
            for (int l = 0; l < c;l++){
                notu[i][l] = 1;
            }
        }
    }
    int line(){
        bool prime[max(r,c)][max(r,c)];
        for (int i = 0; i < max(r,c);i++){
            for (int l = 0; l < max(r,c);l++){
                stars[i][l] = 0;
                prime[i][l] = 0;
            }
        }
        while (1){
            bool end = 0;
            bool nm = 0;
            for (int i = 0; i < max(r,c);i++){
                for (int l = 0; l < max(r,c);l++){
                    if (star[1][l] == 1){
                        continue;
                    }
                    if (star[0][i]){
                        break;
                    }
                    if (matrix[i][l] == 0){
                        star[0][i] = 1;
                        star[1][l] = 1;
                        stars[i][l] = 1;
                        con++;
                    }
                }
            }
            fill(cover[0], cover[0]+max(r,c),0);
            fill(cover[1], cover[1]+max(r,c),0);
            for (int i = 0; i < max(r,c);i++){
                for (int l = 0; l < max(r,c);l++){
                    prime[i][l] = 0;
                }
            }
            //if (con == max(r,c)){
            //    return c;
            //}
            for (int i = 0; i < max(r,c);i++){
                cover[1][i] = star[1][i];
            }
            for (int i = 0; i < max(r,c);i++){
                int fs = -1;
                if (cover[0][i]){
                    continue;
                }
                for (int l = 0; l < max(r,c);l++){
                    if (cover[1][l]){
                        if (matrix[i][l] == 0 && fs == -1){
                            fs = l;
                        }
                        continue;
                    }
                    if (matrix[i][l] == 0){
                        if (fs == -1){
                            nm = 1;
                            int rs = -1;
                            for (int j = i-1; j >= 0;j--){
                                if (stars[j][l] == 1){
                                    rs = j;
                                    break;
                                }
                            }
                            if (rs == -1){
                                stars[i][l] = 1;
                                star[0][i] = 1;
                                star[1][l] = 1;
                                con++;
                                continue;
                            }
                           
                            for (int j = l+1; j < max(r,c);j++){
                                if (matrix[rs][j] == 0 && prime[rs][j] == 1){
                                    stars[rs][j] = 1;
                                    star[0][rs] = 1;
                                    star[1][j] = 1;
                                    stars[rs][l] = 0;
                                    star[1][l] = 0;
                                    prime[rs][l] = 1;

                                    stars[i][l] = 1;
                                    star[0][i] = 1;
                                    star[1][l] = 1;
                                    con++;
                                    end = 1;
                                    break;
                                }
                            }
                            break;
                        }
                        cover[0][i] = 1;
                        cover[1][fs] = 0;
                        prime[i][l] = 1;
                        break;
                    }
                }
                if (end){
                    break;
                }
                if (cover[0][i]){
                    continue;
                }
            }
            if (nm == 0){
                return con;
            }
        }
        return con;
    }
    void copy(){
        for (int i = 0; i < matrix.size();i++){
            vector<int> temp;
            for (int l = 0; l < matrix[i].size();l++){
                temp.push_back(matrix[i][l]);
            }
            matrix2.push_back(temp);
        }
    }
    pair<bool ,int> minAss(){
        copy();
        for (int i = 0; i < max(r,c);i++){
            //if (i >= r){
            //   for (int l = 0; l < max(r,c);l++){
            //        matrix[i][l] -= INT_MAX;
            //    }
            //    continue;
            //}
            int mi = INT_MAX;
            for (int l = 0; l < max(r,c);l++){
                if (matrix[i][l] < mi){
                    mi = matrix[i][l];
                }
            }
            for (int l = 0; l < max(r,c);l++){
                matrix[i][l] -= mi;
            }
        }   
        for (int i = 0; i < max(c,r);i++){
             //if (i >= c){
             //   for (int l = 0; l < max(r,c);l++){
             //       matrix[l][i] -= INT_MAX;
            //    }
            //    continue;
            //}
            int mi = INT_MAX;
            for (int l = 0; l < max(r,c);l++){
                if (matrix[l][i] < mi){
                    mi = matrix[l][i];
                }
            }
            for (int l = 0; l < max(r,c);l++){

                matrix[l][i] -= mi;
            }
        }
        while (1){
            int con = line();
            if (con == max(r,c)){
                int ass = 0;
                bool fail = 0;
                for (int i = 0; i < max(r,c);i++){
                    for (int l = 0; l < max(r,c);l++){
                        if (stars[i][l] == 1){
                            if (matrix2[i][l] == INT_MAX){
                                fail = 1;
                            } else {
                                ass += matrix2[i][l];
                            }
                        }
                    }
                }
                return make_pair(fail, ass);
            }
            int mi = INT_MAX;
            for (int i = 0; i < max(r,c);i++){
                if (cover[0][i]){
                    continue;
                }
                for (int l = 0; l < max(r,c);l++){
                    if (cover[1][l]){
                        continue;
                    }
                    mi = min(mi, matrix[i][l]);
                }
            }
            for (int i = 0; i < max(r,c);i++){
                if (cover[0][i] == 0){
                    for (int l = 0; l < max(r,c);l++){
                        matrix[i][l] -=mi;
                    }
                }
            }
            for (int i = 0; i < max(r,c);i++){
                if (cover[1][i]){
                    for (int l = 0; l < max(r,c);l++){
                        matrix[i][l] += mi;
                    }
                }
            }
        }
    }
};
vector<vector<pair<int, int> > > constructdgraph(){
    vector<vector<pair<int, int> > > result(8);
    result[0].push_back(make_pair(1,16));
    result[0].push_back(make_pair(2,13));
    result[1].push_back(make_pair(2,10));
    result[1].push_back(make_pair(3,12));
    result[2].push_back(make_pair(1,4));
    result[2].push_back(make_pair(4,14));
    result[3].push_back(make_pair(2,9));
    result[3].push_back(make_pair(5,20));
    result[4].push_back(make_pair(3,7));
    result[4].push_back(make_pair(5,4));
    return result;
}
vector<vector<int> > constructbipart(){
    vector<vector<int> > result(22);
    result[1].push_back(6);
    result[1].push_back(7);
    result[2].push_back(5  );
    result[3].push_back(6);
    result[4].push_back(6);
    result[4].push_back(8);
    //for (int i = 1; i <= 6;i++){
    //    result[0].push_back(make_pair(i,1));
    //    result[i+6].push_back(make_pair(13,1));
    //}
    return result;
}
vector<vector< int > > makeMatch(){
    vector<vector<int> > result(2);
    result[0].push_back(2500);
    result[0].push_back(4000);
    result[0].push_back(3500);
    result[1].push_back(4000);
    result[1].push_back(6000);
    result[1].push_back(3500);
    return result;
}
int main(){
    vector<vector<int> > result = constructbipart();
    weightBipart temp(2,3);
    temp.matrix = makeMatch();
    temp.format();
    cout << temp.minAss().second << endl;
    return 0;
}