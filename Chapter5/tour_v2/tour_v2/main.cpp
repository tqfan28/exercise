//
//  main.cpp
//  tour_v2
//
//  Created by TFAN on 2018/8/10.
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
//#include <algorithm>
//#include <math.h>
//#include <iomanip>


using namespace std;
const int infty = 0x7fffffff;
int N;
int V;
map<string,int> citymap;
const int MAXN = 100;
bool adj[MAXN][MAXN] = {};
int dp[MAXN][MAXN] = {};



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
    
    dp[0][0] = 1;
    
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            dp[i][j] = -100000;
            for (int k = 0; k < j; ++k) {
                if (adj[k][j] && dp[i][k] > 0) {
                    dp[i][j] = max(dp[i][j], dp[i][k]);
                }
            }
            dp[i][j]++;
            dp[j][i] = dp[i][j];
        }
    }
    
    ofstream fout;
    fout.open("tour.out");
    
    int sol = 1;
    
    for (int i = 0; i < N-1; ++i) {
        if (adj[i][N-1] && dp[i][N-1] > sol) {
            sol = dp[i][N-1];
        }
    }
    
    fout << sol << endl;
    
    fout.close();
    
    return 0;
}










































