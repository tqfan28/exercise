//
//  main.cpp
//  tour
//
//  Created by TFAN on 2018/8/9.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: tour
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
//#include <queue>
//#include <stack>
//#include <list>
#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>


using namespace std;
//const int infty = 0x7fffffff;
int N;
int V;
map<string,int> citymap;
const int MAXN = 100;
bool adj[MAXN][MAXN] = {};
int sol = 0;
int path[MAXN] = {};

void init() {
    path[0] = 0;
    for (int i = 1; i < N; ++i) {
        path[i] = -1;
    }
}

int inpath(int v, int pathpos) {
    for (int i = 0; i < pathpos; ++i) {
        if (path[i] == v) {
            return i;
        }
    }
    return -1;
}

void printP() {
    for (int i = 0; i < N; ++i) {
        cout << path[i] << ' ';
    }
    cout << endl;
}

bool inorder(int Npos, int pathpos) {
    if (Npos == -1) {
        for (int i = 0; i < pathpos-1; ++i) {
            if (path[i+1] < path[i]) {
                return false;
            }
        }
        return true;
    }
    
    else {
        for (int i = 0; i < Npos; ++i) {
            if(path[i+1] < path[i]) {
                return false;
            }
        }
        for (int i = Npos; i < pathpos-1; ++i) {
            if(path[i+1] > path[i]) {
                return false;
            }
        }
        return true;
    }
}

bool search(int pathpos) {
    
    int Npos = inpath(N-1, pathpos);
    if (!inorder(Npos, pathpos)) {
        return false;
    }
    
    if (pathpos == N) {
        if (adj[path[pathpos-1]][0]) {
            sol = max(sol, pathpos);
            return true;
        }
        else {
            return false;
        }
    }
    
    for (int i = 0; i < N; ++i) {
        if (adj[path[pathpos-1]][i] && inpath(i, pathpos) == -1) {
            path[pathpos] = i;
            if (search(pathpos+1)) {
                return true;
            }
            path[pathpos] = -1;
        }
    }
    
    if (Npos != -1 && adj[path[pathpos-1]][0]) {
        sol = max(sol, pathpos);
        printP();
    }
    //printP();
    return false;
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("tour.in");
    
    fin >> N >> V;
    
    string city;
    
    for (int i = 0; i < N; ++i) {
        fin >> city;
        citymap.insert(pair<string,int>(city,i));
    }
    
    for (int i = 0; i < V; ++i) {
        string u, v;
        fin >> u >> v;
        adj[citymap[u]][citymap[v]] = true;
        adj[citymap[v]][citymap[u]] = true;
    }
    
    fin.close();
    
    init();
    
    ofstream fout;
    fout.open("tour.out");
    
    if (search(1)) {
        fout << N << endl;
    }
    else if (sol == 0)
        fout << 1 << endl;
    else {
        fout << sol << endl;
    }
    
    fout.close();
    
    return 0;
}








































