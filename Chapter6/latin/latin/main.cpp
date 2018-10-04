//
//  main.cpp
//  latin
//
//  Created by TFAN on 2018/9/30.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: latin
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
//#include <string>
//#include <stdio.h>
//#include <ctype.h>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>

using namespace std;
int N;
const int MAXN = 7;
int board[MAXN+1][MAXN+1] = {};
int dp[MAXN+1] = {};
bool col[MAXN+1][MAXN+1] = {};
bool row[MAXN+1][MAXN+1] = {};
long long ans = 0;
int len = 0;

int cycle_decomp() {
    int long_cycle = 2;
    bool visited[MAXN+1] = {};
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            int id = i;
            int tmp = 0;
            do {
                visited[id] = true;
                id = board[2][id];
                tmp ++;
            } while(!visited[id]);
            
            if (tmp > long_cycle) {
                long_cycle = tmp;
            }
        }
    }
    return long_cycle;
}


void dfs(int x, int y) {
    
//    for (int i = 1; i <= N; ++i) {
//        for (int j = 1; j<= N; ++j) {
//            cout << board[i][j] << ' ';
//        }
//        cout << endl;
//    }
//    cout << endl;
    
    
    for (int i = 1; i <= N; ++i) {
        if (row[x][i] && col[y][i]) {
            board[x][y] = i;
            if (x == 2 && y == N) {
                len = cycle_decomp();
                if (dp[len]) {
                    ans += dp[len];
                    return ;
                }
            }
            
            row[x][i] = false;
            col[y][i] = false;
            if (y == N) {
                if (x == N-1 || x == N) {
                    dp[len] ++;
                    ans ++;
                }
                else {
                    dfs(x+1, 2);
                }
            }
            else {
                dfs(x, y+1);
            }
            board[x][y] = 0;
            row[x][i] = true;
            col[y][i] = true;
        }
    }
}

void init() {
    
    for (int i = 1; i <= N; ++i) {
        board[1][i] = i;
        board[i][1] = i;
    }
    
    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            row[i][j] = true;
            col[i][j] = true;
        }
    }
    for (int i = 1; i <= N; ++i) {
        row[i][i] = false;
        col[i][i] = false;
    }
}

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return factorial(n-1)*n;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("latin.in");
    
    fin >> N;
    
    fin.close();
    
    
    init();
    dfs(2, 2);
    
    ofstream fout;
    fout.open("latin.out");
    
    fout << ans*factorial(N-1) << endl;
    
    fout.close();
    
    return 0;
}




































































