//
//  main.cpp
//  snail
//
//  Created by TFAN on 2018/8/4.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: snail
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
int N;
int B;
const int MAXN = 120;
bool obs[MAXN+2][MAXN+2] = {};
bool visited[MAXN+2][MAXN+2] = {};
pair<int, int> oris[4];
int sol = 0;

struct node {
    int x;
    int y;
    int ori;
};

void printV() {
    for (int i = 0; i < N+2; ++i) {
        for (int j = 0; j < N+2; ++j) {
            cout << visited[i][j] << ' ';
        }
        cout << endl;
    }
}


void dfs(node cur, int len) {
   
    if (visited[cur.y][cur.x] || obs[cur.y][cur.x]) {
        //printV();
        sol = max(sol, len);
        //cout << sol << endl;
        return ;
    }
    
    visited[cur.y][cur.x] = true;
    
    int i = cur.y + oris[cur.ori].second;
    int j = cur.x + oris[cur.ori].first;
    
    if (obs[i][j]) {
        node n1;
        n1.ori = (cur.ori-1 < 0? 3:cur.ori-1);
        n1.x = cur.x+oris[n1.ori].first;
        n1.y = cur.y+oris[n1.ori].second;
        node n2;
        n2.ori = (cur.ori+1 > 3? 0:cur.ori+1);
        n2.x = cur.x+oris[n2.ori].first;
        n2.y = cur.y+oris[n2.ori].second;

        dfs(n1, len+1);
        dfs(n2, len+1);
    }
    else {
        node n1;
        n1.ori = cur.ori;
        n1.x = cur.x+oris[n1.ori].first;
        n1.y = cur.y+oris[n1.ori].second;
        dfs(n1, len+1);
    }
    visited[cur.y][cur.x] = false;
    
}

void init() {
    oris[0] = make_pair(1, 0);
    oris[1] = make_pair(0, -1);
    oris[2] = make_pair(-1, 0);
    oris[3] = make_pair(0, 1);
    for (int i = 0; i < N+2; ++i) {
        obs[0][i] = true;
        obs[i][0] = true;
        obs[N+1][i] = true;
        obs[i][N+1] = true;
    }
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("snail.in");
    
    fin >> N >> B;
    
    init();
    
    for (int i = 0; i < B; ++i) {
        char x;
        int y;
        fin >> x >> y;
        obs[y][int(x-64)] = true;
    }
    
    fin.close();
    
    node st;
    st.x = 1;
    st.y = 1;
    st.ori = 0;
    dfs(st, 0);
    st.ori = 3;
    dfs(st, 0);
    
    ofstream fout;
    fout.open("snail.out");
    
    fout << sol << endl;
    
    fout.close();
    
    return 0;
}


































