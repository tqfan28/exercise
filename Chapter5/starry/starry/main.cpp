//
//  main.cpp
//  starry
//
//  Created by TFAN on 2018/8/3.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: starry
 LANG: C++
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <math.h>
#include <iomanip>


using namespace std;
const int infty = 0x7fffffff;
int H;
int W;
const int MAXH = 100;
const int MAXW = 100;
int board[MAXH][MAXW] = {};
bool visited[MAXH][MAXW] = {};
char print[MAXH][MAXW];
const string itoc = "abcdefghijklmnopqrstuvwxyz";

struct xy {
    int x;
    int y;
    bool operator < (const xy & rhs) const {
        return ( x < rhs.x || (x == rhs.x && y < rhs.y) );
    }
};

const int MAXPOINT = 160;

struct pattern{
    int h;
    int w;
    int xmin;
    int ymin;
    xy crds[8][MAXPOINT+1];
};

pattern patterns [26];

bool cmp2 (int len, const xy crds1[MAXPOINT+1], const xy crds2[MAXPOINT+1]) {
    for(int i = 1; i < len+1; ++i) {
        if (crds1[i].x != crds2[i].x || crds1[i].y != crds2[i].y) {
            return false;
        }
    }
    return true;
}

bool cmp (const pattern & a, const pattern & b) {
    
    if (a.crds[0][0].x != b.crds[0][0].x) {
        return false;
    }
    
    if (a.h == b.h && a.w == b.w) {
        if (cmp2(a.crds[0][0].x, a.crds[0], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[2], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[4], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[6], b.crds[0])) {
            return true;
        }
    }
    if (a.h == b.w && a.w == b.h) {
        if (cmp2(a.crds[0][0].x, a.crds[1], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[3], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[5], b.crds[0])) {
            return true;
        }
        if (cmp2(a.crds[0][0].x, a.crds[7], b.crds[0])) {
            return true;
        }
    }
    return false;
}

void reflection(pattern & aPattern) {
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[4][i].y = aPattern.crds[0][i].y;
        aPattern.crds[4][i].x = aPattern.w - aPattern.crds[0][i].x -1;
    }
    sort(aPattern.crds[4]+1, aPattern.crds[4]+aPattern.crds[0][0].x+1);
}

void rotation(pattern & aPattern) {
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[1][i].x = aPattern.crds[0][i].y;
        aPattern.crds[1][i].y = aPattern.w - aPattern.crds[0][i].x -1;
    }
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[2][i].x = aPattern.w - aPattern.crds[0][i].x -1;
        aPattern.crds[2][i].y = aPattern.h - aPattern.crds[0][i].y -1;
    }
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[3][i].x = aPattern.h - aPattern.crds[0][i].y -1;
        aPattern.crds[3][i].y = aPattern.crds[0][i].x;
    }
    reflection(aPattern);
    
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[5][i].x = aPattern.crds[4][i].y;
        aPattern.crds[5][i].y = aPattern.w - aPattern.crds[4][i].x -1;
    }
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[6][i].x = aPattern.w - aPattern.crds[4][i].x -1;
        aPattern.crds[6][i].y = aPattern.h - aPattern.crds[4][i].y -1;
    }
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[7][i].x = aPattern.h - aPattern.crds[4][i].y -1;
        aPattern.crds[7][i].y = aPattern.crds[4][i].x;
    }
    
    sort(aPattern.crds[1]+1, aPattern.crds[1]+aPattern.crds[0][0].x+1);
    sort(aPattern.crds[2]+1, aPattern.crds[2]+aPattern.crds[0][0].x+1);
    sort(aPattern.crds[3]+1, aPattern.crds[3]+aPattern.crds[0][0].x+1);
    sort(aPattern.crds[5]+1, aPattern.crds[5]+aPattern.crds[0][0].x+1);
    sort(aPattern.crds[6]+1, aPattern.crds[6]+aPattern.crds[0][0].x+1);
    sort(aPattern.crds[7]+1, aPattern.crds[7]+aPattern.crds[0][0].x+1);
}


void findhw( pattern & aPattern) {
    int xmax = 0;
    int xmin = infty;
    int ymax = 0;
    int ymin = infty;
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        
        xmax = max( aPattern.crds[0][i].x, xmax);
        xmin = min( aPattern.crds[0][i].x, xmin);
        ymax = max( aPattern.crds[0][i].y, ymax);
        ymin = min( aPattern.crds[0][i].y, ymin);
    }
    
    for (int i = 1; i < aPattern.crds[0][0].x+1; ++i) {
        aPattern.crds[0][i].x -= xmin;
        aPattern.crds[0][i].y -= ymin;
    }
    aPattern.xmin = xmin;
    aPattern.ymin = ymin;
    aPattern.h = ymax - ymin + 1;
    aPattern.w = xmax - xmin + 1;
}

const int diff[16] = {
    1, 0,
    1, 1,
    0, 1,
    -1, 1,
    -1, -1,
    1, -1,
    0, -1,
    -1, 0};

void findcrds(xy start, pattern & aPattern) {
    
    queue<xy> line;
    line.push(start);
    visited[start.y][start.x] = true;
    int counter = 0;
    
    while(!line.empty()) {
        xy cur = line.front();
        line.pop();
        aPattern.crds[0][counter+1] = cur;
        counter ++;
        //cout << cur.x << ' ' << cur.y << ' ' << board[cur.y][cur.x] << endl;
        xy next;
        for (int i = 0; i < 15; i = i+2) {
            next.x = cur.x + diff[i];
            next.y = cur.y + diff[i+1];
            if (next.x >= 0 && next.x < W && next.y >= 0 && next.y < H &&
                !visited[next.y][next.x] && board[next.y][next.x] != 0) {
                line.push(next);
                visited[next.y][next.x] = true;
            }
        }
    }
    aPattern.crds[0][0].x = counter;
    
    findhw(aPattern);
    sort(aPattern.crds[0]+1, aPattern.crds[0]+counter+1);

}

void printB() {
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cout << print[i][j];
        }
        cout << endl;
    }
}

void setPrint(const pattern & a, int index) {
    
    for (int i = 1; i < a.crds[0][0].x+1; ++i) {
        print[a.crds[0][i].y + a.ymin][a.crds[0][i].x + a.xmin] = itoc[index];
    }
}



int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("starry.in");
    fin >> W >> H;
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            fin >> print[i][j];
            board[i][j] = print[i][j] - '0';;
        }
    }
    
    int cnt = 0;
    
//    xy tmp;
//    tmp.x = 0;
//    tmp.y = 0;
//    pattern a;
//    findcrds(tmp, a);
//    setPrint(a, 0);
//    printB();
//    return 0;
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (!visited[i][j] && board[i][j] != 0) {
                //cout << i << ' ' << j << endl;
                pattern a;
                xy tmp;
                tmp.x = j;
                tmp.y = i;
                findcrds(tmp, a);
                if (cnt == 0) {
                    rotation(a);
                    patterns[cnt] = a;
                    setPrint(a, cnt);
                    cnt ++;
                }
                else {
                    int index = -1;
                    for (int k = 0; k < cnt; ++k) {
                        if (cmp(patterns[k], a)) {
                            index = k;
                            break;
                        }
                    }
                    if (index == -1) {
                        rotation(a);
                        patterns[cnt] = a;
                        setPrint(a, cnt);
                        cnt ++;
            
                    }
                    else {
                        setPrint(a, index);
            
                    }
                }
            }
        }
    }
    
    ofstream fout;
    fout.open("starry.out");
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            fout << print[i][j];
        }
        fout << endl;
    }
    fout.close();
    
    return 0;
}

































