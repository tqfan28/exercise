//
//  main.cpp
//  stall4
//
//  Created by TFAN on 2018/7/16.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: stall4
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
const int MAXNODE = 400+2;
list<pair<int, int>> adj[MAXNODE+1];

list<pair<int, int>>::iterator findList (list<pair<int, int>>& ls, int v) {
    list<pair<int, int>>::iterator itr = ls.begin();
    while(itr != ls.end()) {
        if (itr->first == v)
            return itr;
        itr ++;
    }
    return itr;
}

int Flow(int scr, int sink, int NODE) {
    
    int totalFlow = 0;
    if (sink == scr) {
        totalFlow = infty;
        return 0;
    }
    int prevnode[MAXNODE+1] = {};
    bool visited[MAXNODE+1] = {};
    int flow[MAXNODE+1] = {};
    while(true) {
        //find path with highest capacity from source to sink with a modified djikstra's algorithm
        for (int i = 0; i < NODE+1; ++i) {
            prevnode[i] = -1;
            flow[i] = 0;
            visited[i] = false;
        }
        flow[scr] = infty;
        
        int maxflow, maxloc;
        
        while(true) {
            maxflow = 0;
            maxloc = -1;
            //find the unvisited node with the highest capacity to it
            for (int i = 0; i < NODE+1; ++i) {
                if (!visited[i] && flow[i] > maxflow) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            if (maxloc == -1)
                break;
            if (maxloc == sink)
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
        if (maxloc == -1)
            break;
        int pathcapacity = flow[sink];
        totalFlow += pathcapacity;
        
        //add that flow to the network, update capacity appropriately
        int curnode = sink;
        while(curnode != scr) {
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
    return totalFlow;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("stall4.in");
    fin >> N >> M;
    
    int scr = 0;
    int sink = N+M+1;
    
    for (int i = 1; i < N+1; ++i) {
        adj[0].push_back(make_pair(i, 1));
    }
    for (int j = N+1; j < sink; ++j) {
        adj[j].push_back(make_pair(sink, 1));
    }
    int l, v;
    for (int i = 1; i < N+1; ++i) {
        fin >> l;
        for (int k = 0; k < l; ++k) {
            fin >> v;
            adj[i].push_back(make_pair(N+v, 1));
        }
    }
    
    ofstream fout ("stall4.out");
    fout << Flow(scr, sink, N+M+1) << endl;
    fout.close();
    return 0;
}





























