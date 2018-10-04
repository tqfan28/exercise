//
//  main.cpp
//  wissqu
//
//  Created by TFAN on 2018/9/29.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: wissqu
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
#include <string>
//#include <stdio.h>
//#include <ctype.h>
#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>

using namespace std;
ofstream fout;
char board[5][5];
int dx[9] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
int dy[9] = {0, -1, 0, 1, -1, 1, -1, 0, 1};
// A B C D E
// 1 2 3 4 5
int state[5][5][5] = {};
int ans[3][17] = {};
int cnt = 0;
bool visited[5][5] = {};
int cnts[5] = {3, 3, 3, 4, 3};

void count(int x, int y) {
    for (int i = 0; i < 9; ++i) {
        if (x + dx[i] >= 1 && x + dx[i] <=4
            && y + dy[i] >= 1 && y + dy[i] <= 4) {
            state[x + dx[i]][y + dy[i]][int(board[x][y]-65)] ++;
        }
    }
}

void in(int x, int y , int cow) {
    board[x][y] = char(cow+65);
    count(x, y);
}
void out(int x, int y, int cow) {
    for (int i = 0; i < 9; ++i) {
        if (x + dx[i] >= 1 && x + dx[i] <=4
            && y + dy[i] >= 1 && y + dy[i] <= 4) {
            state[x + dx[i]][y + dy[i]][cow] --;
        }
    }
}


// cow is moving to board[x][y]
void dfs(int x, int y, int cow, int depth) {
    ans[0][depth] = x;
    ans[1][depth] = y;
    ans[2][depth] = cow;
    
    if (depth == 16) {
        if (cnt == 0) {
            for (int i = 1; i <= 16; ++i) {
                fout << char(ans[2][i] + 65) << ' ' << ans[0][i] << ' ' << ans[1][i] << endl;
            }
        }
        cnt ++;
        return ;
    }
    int old_cow = int(board[x][y]-65);
    out(x, y, old_cow);
    in(x, y, cow);
    visited[x][y] = true;
    
    for (int type = 0; type < 5; ++type) {
        if (cnts[type] > 0) {
            for (int i = 1; i < 5; ++i) {
                for (int j = 1; j < 5; ++j) {
                    if (state[i][j][type] == 0 && !visited[i][j]) {
                        cnts[type] --;
                        dfs(i, j, type, depth+1);
                        cnts[type] ++;
                    }
                }
            }
        }
    }
    
    out(x, y, cow);
    in(x, y, old_cow);
    visited[x][y] = false;

}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("wissqu.in");
    for (int i = 1; i < 5; ++i) {
        for (int j = 1; j < 5; ++j) {
            fin >> board[i][j];
        }
    }
    
    
    for (int i = 1; i < 5; ++i) {
        for (int j = 1; j < 5; ++j) {
            count(i, j);
        }
    }
    
    
    fout.open("wissqu.out");
    
    for (int i = 1; i < 5; ++i) {
        for (int j = 1; j < 5; ++j) {
            if (state[i][j][3] == 0) {
                dfs(i, j, 3, 1);
            }
        }
    }
    fout << cnt << endl;
    
    fout.close();
    
    return 0;
}



































































