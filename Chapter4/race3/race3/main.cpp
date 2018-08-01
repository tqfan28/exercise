//
//  main.cpp
//  race3
//
//  Created by TFAN on 2018/7/28.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: race3
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
const int MAXN = 50;
int mat[MAXN+1][MAXN+1] = {};
bool visited[MAXN+1] = {};
int matSplit[MAXN+1][MAXN+1] = {};
int N = 0;

void dfs(int scr) {
    queue<int> aq;
    aq.push(scr);
    visited[scr] = true;
    while(!aq.empty()) {
        int u = aq.front();
        aq.pop();
        for (int i = 0; i < N+1; ++i) {
            if (matSplit[u][i] == 1 && !visited[i]) {
                aq.push(i);
                visited[i] = true;
            }
        }
    }
}

bool dfs2(int scr, int split) {
    queue<int> aq;
    
    aq.push(scr);
    bool visited2[MAXN+1] = {};
    visited2[scr] = true;

    while(!aq.empty()) {
        int u = aq.front();
        aq.pop();
        for (int i = 0; i < N+1; ++i) {
            if (matSplit[u][i] == 1 && !visited2[i]) {
                aq.push(i);
                visited2[i] = true;
                if (visited[i] && i != split) {
                    return false;
                }
            }
        }
    }
    
    if (!visited2[N-1])
        return false;
    return true;
}

bool dfs3(int scr, int sink) {
    queue<int> aq;
    bool visited3[MAXN+1] = {};
    aq.push(scr);
    visited3[scr] = true;
    while(!aq.empty()) {
        int u = aq.front();
        aq.pop();
        for (int i = 0; i < N+1; ++i) {
            if (matSplit[u][i] == 1 && !visited3[i]) {
                aq.push(i);
                visited3[i] = true;
                if (!visited[i]) {
                    return false;
                }
            }
        }
    }
    if (!visited3[sink])
        return false;
    return true;
}

void splitAt(int u) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N+1; ++j) {
            if (i == u) {
                matSplit[N][j] = mat[u][j];
                matSplit[u][j] = infty;
            }
            else {
                matSplit[i][j] = mat[i][j];
            }
        }
    }
    matSplit[u][u] = 0;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin ("race3.in");
    int u;
    
    while(u != -1) {
        fin >> u;
        if (u == -2) {
            N++;
        }
        else if (u != -1) {
            mat[N][u] = 1;
        }
    }
    for (int i = 0; i < N+1; ++i) {
        for (int j = 0; j < N+1; ++j) {
            if (mat[i][j] != 1) {
                mat[i][j] = infty;
            }
        }
        if (mat[i][i] == infty) {
            mat[i][i] = 0;
        }
    }

    
    vector<int> unavoidable;
    vector<int> splitting;
    for (int i = 1; i < N-1; ++i) {
        
        splitAt(i);

        for (int j = 0; j < N+1; ++j) {
            visited[j] = false;
        }
        
        dfs(0);
        if (!visited[N-1]) {
            unavoidable.push_back(i);
            bool check = true;
            for (int j = 1; j < N+1; ++j) {
                if (!visited[j]) {
                    if (!dfs2(j, i)) {
                        check = false;
                        break;
                    }
                }
            }
            if (check) {
                bool check2 = true;
                for (int j = 1; j < N-1; ++j) {
                    if (visited[j]) {
                        if (!dfs3(j, i)) {
                            check2 = false;
                            break;
                        }
                    }
                }
                if (check2) {
                    splitting.push_back(i);
                }
            }
        }
    }
    
    ofstream fout ("race3.out");
    fout << unavoidable.size();
    if (unavoidable.size() > 0) {
        sort(unavoidable.begin(), unavoidable.end());
        for (vector<int>::iterator i = unavoidable.begin(); i != unavoidable.end(); ++i) {
            fout << ' ' << *i;
        }
    }
    fout << endl;
    fout << splitting.size();
    if (splitting.size() > 0) {
        sort(splitting.begin(), splitting.end());
        for (vector<int>::iterator i = splitting.begin(); i != splitting.end(); ++i) {
            fout << ' ' << *i;
        }
    }
    fout << endl;
    fout.close();
    return 0;
}
































