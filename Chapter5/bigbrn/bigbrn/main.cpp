//
//  main.cpp
//  bigbrn
//
//  Created by TFAN on 2018/8/8.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: bigbrn
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
int T;
const int MAXN = 1000;
int dp[MAXN][MAXN] = {};



int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("bigbrn.in");
    
    fin >> N >> T;
    for (int i = 0; i < T; ++i) {
        int x = 0;
        int y = 0;
        fin >> y >> x;
        dp[y-1][x-1] = -1;
    }
    
    fin.close();
    
    for (int i = 0; i < N; ++i) {
        if (dp[0][i] == 0)
            dp[0][i] ++;
        if (dp[i][0] == 0)
            dp[i][0] ++;
    }
    
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            
            if (dp[i][j] != -1) {
                int up = dp[i-1][j];
                int left = dp[i][j-1];
                int ul = dp[i-1][j-1];
                if (up == -1 || left == -1 || ul == -1) {
                    dp[i][j] = 1;
                }
                else {
                    if (ul >= up && left >= up) {
                        dp[i][j] = up+1;
                    }
                    else if (ul >= up && left < up) {
                        dp[i][j] = left+1;
                    }
                    else if (ul < up && left >= up) {
                        dp[i][j] = up;
                    }
                    else {
                        dp[i][j] = left +1;
                    }
                }
            }
        }
    }
    int sol = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sol = max(sol, dp[i][j]);
        }
    }
    
    ofstream fout;
    fout.open("bigbrn.out");
    
    fout << sol << endl;
    
    fout.close();
    
    return 0;
}







































