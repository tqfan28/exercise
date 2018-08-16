//
//  main.cpp
//  schlnet
//
//  Created by TFAN on 2018/8/7.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: schlnet
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>


using namespace std;
//const int infty = 0x7fffffff;
int N;
const int MAXN = 100;
int adj[MAXN][MAXN] = {};
int comps[MAXN] = {};

int id = 0;
stack<int> S;
int lowlink[MAXN] = {};
int indx[MAXN] = {};
bool onStack[MAXN] = {};
int cnt = 0;

void scc(int scr) {
    
    indx[scr] = id;
    lowlink[scr] = id;
    id++;
    S.push(scr);
    onStack[scr] = true;
    
    for (int i = 0; i < N; ++i) {
        if (adj[scr][i] == 1) {
            if (indx[i] == -1) {
                scc(i);
                lowlink[scr] = min(lowlink[scr], lowlink[i]);
            }
            else if (onStack[i]) {
                lowlink[scr] = min(lowlink[scr], indx[i]);
            }
        }
    }
    
    if (lowlink[scr] == indx[scr]) {
        int j = 0;
        do {
            j = S.top();
            S.pop();
            onStack[j] = false;
            comps[j] = cnt;
        } while(j != scr);
        cnt++;
    }
    
}

void tarjan() {
    
    for (int i = 0; i < N; ++i) {
        if (indx[i] == -1) {
            scc(i);
        }
    }

}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("schlnet.in");
    
    fin >> N;
    for (int i = 0; i < N; ++i) {
        int v = 0;
        while(fin >> v) {
            if (v == 0)
                break;
            else
                adj[i][v-1] = 1;
        }
    }

    fin.close();
    
    for (int i = 0; i < N; ++i) {
        indx[i] = -1;
        lowlink[i] = -1;
    }
    
    tarjan();
    int adj2[MAXN][MAXN] = {};
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (adj[i][j] == 1) {
                adj2[comps[i]][comps[j]] = 1;
            }
        }
    }
    
    for (int i = 0; i < cnt; ++i) {
        adj2[i][i] = 0;
    }

    int x = 0;
    int y = 0;
    for (int i = 0; i < cnt; ++i) {
        int sum = 0;
        for (int j = 0; j < cnt; ++j) {
            sum += adj2[i][j];
        }
        if (sum == 0) {
            x++;
        }
    }
    
    for (int j = 0; j < cnt; ++j) {
        int sum = 0;
        for (int i = 0; i < cnt; ++i) {
            sum += adj2[i][j];
        }
        if (sum == 0) {
            y++;
        }
    }
    
    ofstream fout;
    fout.open("schlnet.out");
    
    if (cnt == 1) {
        fout << 1 << endl;
        fout << 0 << endl;
    }
    else {
        fout << y << endl;
        fout << max(x, y) << endl;
    }
    
    fout.close();
    
    return 0;
}






































