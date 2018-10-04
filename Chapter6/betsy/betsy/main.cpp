//
//  main.cpp
//  betsy
//
//  Created by TFAN on 2018/10/2.
//  Copyright © 2018年 TFAN. All rights reserved.
//




/*
 ID: tfan0328
 PROG: betsy
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
//#include <algorithm>
//#include <math.h>
//#include <iomanip>

using namespace std;
const int MAXN = 7;
int N;
bool board[MAXN+2][MAXN+2] = {};
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int ans = 0;

int nbhd(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (!board[x + dx[i]][y + dy[i]]) {
            cnt ++;
        }
    }
    return cnt;
}

void dfs(int x, int y, int steps) {
    
    if (x == 1 && y == N) {
        if (steps == N*N) {
            ans ++;
            return ;
        }
        else {
            return ;
        }
    }
    if (board[x+1][y] && board[x-1][y] && !board[x][y+1] && !board[x][y-1]) {
        return ;
    }
    if (!board[x+1][y] && !board[x-1][y] && board[x][y+1] && board[x][y-1]) {
        return ;
    }
    
    for (int i = 0; i < 4; ++i) {
        int next_x = x + dx[i];
        int next_y = y + dy[i];
        
        if (!board[next_x][next_y]) {
            
            if (next_x != 1 || next_y != N) {
                int n = nbhd(next_x, next_y);
                if ( n == 0) {
                    return ;
                }
                else if (n == 1) {
                    board[next_x][next_y] = true;
                    dfs(next_x, next_y, steps+1);
                    board[next_x][next_y] = false;
                    return ;
                }
            }
            
            board[next_x][next_y] = true;
            dfs(next_x, next_y, steps+1);
            board[next_x][next_y] = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("betsy.in");
    
    fin >> N;
    
    fin.close();
    
    for (int i = 0; i <= N+1; ++i) {
        board[0][i] = true;
        board[i][0] = true;
        board[N+1][i] = true;
        board[i][N+1] = true;
    }
    
    board[1][1] = true;
    dfs(1, 1, 1);
    
    ofstream fout;
    fout.open("betsy.out");
    
    fout << ans << endl;
    
    fout.close();
    
    return 0;
}





































































