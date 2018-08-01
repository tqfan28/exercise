//
//  main.cpp
//  milk6_v2
//
//  Created by TFAN on 2018/7/31.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: milk6
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
#include <cmath>
#include <utility>


using namespace std;
const int infty = 0x7fffffff;
int N;
int M;

struct e {
    int index;
    int u;
    int v;
    int c;
    bool operator < (const e & rhs) const {
        return (c > rhs.c || (c == rhs.c && index < rhs.index));
    }
};

const int MAXNODE = 32;
const int MAXM = 1000;
e edges[MAXM];

list<e>::iterator findList (list<e>& ls, int index) {
    list<e>::iterator itr = ls.begin();
    while(itr != ls.end()) {
        if (itr->index == index)
            return itr;
        itr ++;
    }
    return itr;
}

int Flow(int scr, int sink, int NODE, int dm) {
    
    list<e> adj[MAXNODE+1];
    for (int i = 0; i < M; ++i) {
        if (edges[i].index != dm && edges[i].c != infty) {
            e obj;
            //cout << edges[i].index << endl;
            obj.v = edges[i].v;
            obj.c = edges[i].c;
            obj.index = edges[i].index;
            adj[(edges[i].u)].push_back(obj);
        }
    }
    
    int totalFlow = 0;
    if (sink == scr) {
        totalFlow = infty;
        return 0;
    }
    int prevnode[MAXNODE+1] = {};
    int prevedge[MAXNODE+1] = {};
    bool visited[MAXNODE+1] = {};
    int flow[MAXNODE+1] = {};
    int counter = M+1;
    while(true) {
        //find path with highest capacity from source to sink with a modified djikstra's algorithm
        for (int i = 1; i < NODE+1; ++i) {
            prevnode[i] = -1;
            prevedge[i] = -1;
            flow[i] = 0;
            visited[i] = false;
        }
        flow[scr] = infty;
        
        int maxflow, maxloc;
        
        while(true) {
            maxflow = 0;
            maxloc = -1;
            //find the unvisited node with the highest capacity to it
            for (int i = 1; i < NODE+1; ++i) {
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
            for (list<e>::iterator itr = adj[maxloc].begin(); itr != adj[maxloc].end(); ++itr) {
                if (flow[itr->v] < min(maxflow, itr->c)) {
                    prevnode[itr->v] = maxloc;
                    prevedge[itr->v] = itr->index;
                    flow[itr->v] = min(maxflow, itr->c);
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
            int curedge = prevedge[curnode];
            list<e>::iterator itr = findList(adj[nextnode], curedge);
            itr->c -= pathcapacity;
            
            if (itr->c == 0) {
                adj[nextnode].erase(itr);
            }
            list<e>::iterator itr2 = findList(adj[curnode], nextnode);
            if (itr2 != adj[curnode].end())
                itr2->c += pathcapacity;
            else {
                e tmp;
                tmp.v = nextnode;
                tmp.c = pathcapacity;
                tmp.index = counter;
                counter ++;
                adj[curnode].push_back(tmp);
            }
            
            curnode = nextnode;
        }
        
    }
    return totalFlow;
}

int main(int argc, const char * argv[]) {
    
    
    
    ifstream fin;
    fin.open("milk6.in");
    fin >> N >> M;
    for (int i = 0; i < M; ++i) {
        fin >> edges[i].u >> edges[i].v >> edges[i].c;
        edges[i].index = i;
    }
    fin.close();
    
    int maxflow = Flow(1, N, N, -1);
    int flowcopy = maxflow;
    sort(edges, edges+M);
    vector<int> ans;
    
    for (int i = 0; i < M; ++i) {
        int currentFlow = Flow(1, N, N, edges[i].index);
        //cout << i << ' ' << currentFlow << ' ' << currentFlow + edges[i].c << endl;
        if ( (currentFlow + edges[i].c) == flowcopy) {
            
            ans.push_back(edges[i].index);
            flowcopy -= edges[i].c;
            edges[i].c = infty;
            //cout << edges[i].index << ' ' << edges[i].c << endl;
        }
    }
    
    ofstream fout;
    fout.open("milk6.out");
    sort(ans.begin(), ans.end());
    fout << maxflow << ' ' << ans.size() << endl;;
    for (vector<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
        fout << *i+1 << endl;
    }
    
    fout.close();
    
    return 0;
}


































