//
//  main.cpp
//  telecow
//
//  Created by TFAN on 2018/8/12.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: telecow
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
const int infty = 0x7fffffff;
int N;
int M;
int c1;
int c2;

struct e {
    int u;
    int v;
};

const int MAXN = 101;
const int MAXM = 600;
e edges[MAXM];
int adj[MAXN*2][MAXN*2] = {};


int Flow(int scr, int sink, int dlt) {
    
    if (dlt != -1) {
        adj[dlt][dlt+100] = 0;
    }
    
    int adj2[MAXN*2][MAXN*2];
    for (int i = 0; i < MAXN*2; ++i) {
        for (int j = 0; j < MAXN*2; ++j) {
            adj2[i][j] = adj[i][j];
        }
    }
    
    int totalFlow = 0;
    if (sink == scr) {
        totalFlow = infty;
        return 0;
    }
    
    int prevnode[MAXN*2] = {};
    bool visited[MAXN*2] = {};
    int flow[MAXN*2] = {};
    
    while(true) {
        //find path with highest capacity from source to sink with a modified djikstra's algorithm
        for (int i = 1; i < N+1; ++i) {
            prevnode[i] = -1;
            flow[i] = 0;
            visited[i] = false;
        }
        for (int i = 1+100; i < N+1+100; ++i) {
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
            for (int i = 1; i < N+1; ++i) {
                if (!visited[i] && flow[i] > maxflow) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            for (int i = 1+100; i < N+1+100; ++i) {
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
            
            for (int i = 1; i < N+1; ++i) {
                for (int j = 0; j < 101; j = j+100) {
                    if (maxloc != i+j) {
                        if (flow[i+j] < min(maxflow, adj2[maxloc][i+j])) {
                            prevnode[i+j] = maxloc;
                            flow[i+j] = min(maxflow, adj2[maxloc][i+j]);
                        }
                    }
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
            adj2[nextnode][curnode] -= pathcapacity;
            adj2[curnode][nextnode] += pathcapacity;
            curnode = nextnode;
        }
        
    }
    return totalFlow;
}

void init() {
    for (int i = 1; i <= N; ++i) {
        adj[i][i+100] = 1;
    }
    for (int i = 0; i < M; ++i) {
        adj[(edges[i].u)+100][(edges[i].v)] = 1;
        adj[(edges[i].v)+100][(edges[i].u)] = 1;
    }
    for (int i = 1; i <= N; ++i) {
        adj[100+c2][i] = 0;
        adj[100+i][c1] = 0;
    }
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    
    fin.open("telecow.in");
    
    fin >> N >> M >> c1 >> c2;
    
    for (int i = 0; i < M; ++i) {
        fin >> edges[i].u >> edges[i].v;
    }
    
    fin.close();
    
    init();

    
    int maxflow = Flow(c1+100, c2, -1);
    int flowcopy = maxflow;
    int ans[MAXN] = {};
    int cnt = 0;
    
    for (int i = 1; i <= N; ++i) {
        if (i != c1 && i != c2) {
            int currentFlow = Flow(c1+100, c2, i);
            if ( (currentFlow + 1) == flowcopy) {
                ans[cnt] = i;
                cnt ++;
                flowcopy -= 1;
            }
            else {
                 adj[i][i+100] = 1;
            }
            //cout << i << ' ' << currentFlow << endl;
        }
    }

    
    ofstream fout;
    fout.open("telecow.out");
    
    fout << maxflow << endl;
    for (int i = 0; i < cnt-1; ++i) {
        fout << ans[i] << ' ';
    }
    if (cnt > 0) {
        fout << ans[cnt-1] << endl;
    }
    
    fout.close();
    
    return 0;
}


















































