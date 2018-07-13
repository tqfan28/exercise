//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: agrinet
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;
int N;
const int MAXN  = 100;
const int infty = 999999;
int adj[MAXN][MAXN];
//distance from tree to node j
int dist[MAXN];
//is the node in the tree now?
bool intree[MAXN] = {};
// the parent element of a node in the tree
int source[MAXN];

int find_min() {
    int index;
    int tmp = infty;
    for (int i = 0; i < N; ++i) {
        if (!intree[i] && tmp > dist[i]) {
            index = i;
            tmp = dist[i];
        }
    }
    return index;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("agrinet.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> adj[i][j];
        }
    }
    //Prim's algorithm for minimal spanning tree
    int treesize = 0;
    int treecost = 0;
    for (int i = 0; i < N; ++i) {
        dist[i] = infty;
        source[i] = -1;
    }
    
    intree[0] = true;
    treesize ++;
    for (int j = 0; j < N; ++j) {
        dist[j] = adj[0][j];
        source[j] = 0;
    }
    
    while(treesize < N) {
        int i = find_min();
        //cout << i << endl;
        intree[i] = true;
        treesize ++;
        treecost += dist[i];
        
        for (int j = 0; j < N; ++j) {
            if (adj[i][j] < dist[j]) {
                dist[j] = adj[i][j];
                source[j] = i;
            }
        }
    }
    
    ofstream fout ("agrinet.out");
    
    fout << treecost << endl;
    
    fout.close();
    
    return 0;
}































