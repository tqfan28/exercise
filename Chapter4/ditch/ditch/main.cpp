//
//  main.cpp
//  ditch
//
//  Created by TFAN on 2018/7/16.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: ditch
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>


using namespace std;
const int infty = 0x7fffffff;
int N;
int M;
const int MAXM = 200;
list<pair<int, int>> adj[MAXM+1];

list<pair<int, int>>::iterator findList (list<pair<int, int>>& ls, int v) {
    list<pair<int, int>>::iterator itr = ls.begin();
    while(itr != ls.end()) {
        if (itr->first == v)
            return itr;
        itr ++;
    }
    return itr;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("ditch.in");
    fin >> N >> M;
    // N: number of edges; M: number of vertexes
    int u, v, c;
    for (int i = 0; i < N; ++i) {
        fin >> u >> v >> c;
        adj[u].push_back(make_pair(v, c));
    }
    int totalFlow = 0;
    if (M == 1) {
        totalFlow = infty;
        return 0;
    }
    int prevnode[MAXM+1] = {};
    bool visited[MAXM+1] = {};
    int flow[MAXM+1] = {};
    while(true) {
        //find path with highest capacity from source to sink with a modified djikstra's algorithm
        for (int i = 1; i < M+1; ++i) {
            prevnode[i] = 0;
            flow[i] = 0;
            visited[i] = false;
        }
        flow[1] = infty;
        
        int maxflow, maxloc;
        
        while(true) {
            maxflow = 0;
            maxloc = 0;
            //find the unvisited node with the highest capacity to it
            for (int i = 1; i < M+1; ++i) {
                if (!visited[i] && flow[i] > maxflow) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            if (maxloc == 0)
                break;
            if (maxloc == M)
                break;
            visited[maxloc] = true;
            for (list<pair<int, int>>::iterator itr = adj[maxloc].begin(); itr != adj[maxloc].end(); ++itr) {
                if (flow[itr->first] < min(maxflow, itr->second)) {
                    prevnode[itr->first] = maxloc;
                    flow[itr->first] = min(maxflow, itr->second);
                }
            }
        }
        
        // no path;
        if (maxloc == 0)
            break;
        int pathcapacity = flow[M];
        totalFlow += pathcapacity;
        
        //add that flow to the network, update capacity appropriately
        int curnode = M;
        while(curnode != 1) {
            int nextnode = prevnode[curnode];
            list<pair<int, int>>::iterator itr = findList(adj[nextnode], curnode);
            itr->second -= pathcapacity;
            if (itr->second == 0)
                adj[nextnode].erase(itr);
            list<pair<int, int>>::iterator itr2 = findList(adj[curnode], nextnode);
            if (itr2 != adj[curnode].end())
                itr2->second += pathcapacity;
            else
                adj[curnode].push_back(make_pair(nextnode, pathcapacity));
            curnode = nextnode;
        }
    }
    
    
    ofstream fout ("ditch.out");
    fout << totalFlow << endl;
    fout.close();
    return 0;
}




























