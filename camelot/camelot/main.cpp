
/*
 ID: tfan0328
 PROG: camelot
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <map>
#include <cmath>


using namespace std;
const int infty = 0x7fffffff;
int R;
int C;

struct pos {
    int x;
    int y;
};
list<pos> knights;
pos king;
int kingdist[27][31] = {};
int kingcost[27][31] = {};
int knightdist[27][31] = {};
int knightTotal[27][31] = {};
bool isknight[27][31] = {};

const int dx[]={1,1,-1,-1,2,2,-2,-2};
const int dy[]={2,-2,2,-2,1,-1,1,-1};

void bfsknight(pos knight) {
    
    bool visited[27][31] = {};
    queue<pos> line;
    line.push(knight);
    knightdist[knight.x][knight.y] = 0;
    visited[knight.x][knight.y] = true;
    
    while(!line.empty()) {
        pos current = line.front();
        line.pop();
        pos next;
        
        for (int i = 0; i < 8; ++i) {
            next.x = current.x+dx[i];
            next.y = current.y+dy[i];
            
            if (next.x > 0 && next.x < C+1 && next.y<R+1 && next.y > 0 && !visited[next.x][next.y]) {
                line.push(next);
                visited[next.x][next.y] = true;
                knightdist[next.x][next.y] = knightdist[current.x][current.y] + 1;
                knightTotal[next.x][next.y] += knightdist[next.x][next.y];
            }
        }
    }
    
    int kingdist2[27][31];
    for (int i = 1; i < C+1; ++i) {
        for (int j = 1; j < R+1; ++j) {
            kingdist2[i][j] = kingdist[i][j];
        }
    }
    
    for (int i = 1; i < C+1; ++i) {
        for (int j = 1; j < R+1; ++j) {
            line.push(pos{i, j});
            
            while(!line.empty()) {
                pos current = line.front();
                line.pop();
                pos next;
                for (int i = 0; i < 8; ++i) {
                    next.x = current.x+dx[i];
                    next.y = current.y+dy[i];
                    if (next.x > 0 && next.x < C+1 && next.y<R+1 && next.y > 0
                        && kingdist2[current.x][current.y] + knightdist[current.x][current.y]+1
                        < kingdist2[next.x][next.y] + knightdist[next.x][next.y]) {
                        line.push(next);
                        kingdist2[next.x][next.y] = kingdist2[current.x][current.y]+knightdist[current.x][current.y] +1
                        - knightdist[next.x][next.y];
                    }
                }
            }
            
        }
    }
    
    for (int i = 1; i < C+1; ++i) {
        for (int j = 1; j < R+1; ++j) {
            kingcost[i][j] = min(kingdist2[i][j], kingcost[i][j]);
        }
    }
    
}



int main(int argc, const char * argv[]) {
    
    ifstream fin ("camelot.in");
    fin >> R >> C;
    int x;
    char a;
    int y;
    fin >> a;
    king.x = a-64;
    fin >> king.y;
    
    while (fin >> a) {
        x = a - 64;
        fin >> y;
        knights.push_back(pos{x, y});
    }
    
    for (int i = 1; i < C+1; ++i) {
        for (int j = 1; j < R+1; ++j) {
            kingdist[i][j] = max(abs(i-king.x), abs(j-king.y));
            kingcost[i][j] = kingdist[i][j];
        }
    }
    
    
    int result = infty;
    
    for (list<pos>::iterator k = knights.begin(); k != knights.end(); ++k) {
        bfsknight(*k);
        isknight[k->x][k->y] = true;
    }
    
    for (int i = 1; i < C+1; ++i) {
        for (int j = 1; j < R+1; ++j) {
            if (knightTotal[i][j] != 0 || isknight[i][j])
                result = min(result, kingcost[i][j] + knightTotal[i][j]);
        }
    }
    
    if (result == infty)
        result = 0;
    ofstream fout ("camelot.out");
    fout << result << endl;
    
    return 0;
}





















