//
//  main.cpp
//  checker
//
//  Created by TFAN on 2018/10/3.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: checker
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
const int MAXN = 13;
int N;
int sol[MAXN+1] = {};
int ans = 0;
int check[MAXN+1][MAXN+1] = {};
ofstream fout;


void mark(int x, int y) {
    check[x][y] ++;
    for (int i = x+1; i <= N; ++i) {
        check[i][y] ++;
        if (y-(i-x) > 0) {
            check[i][y-(i-x)] ++;
        }
        if (y+(i-x) <= N) {
            check[i][y+(i-x)]++;
        }
    }
}

void unmark(int x, int y) {
    check[x][y] --;
    for (int i = x+1; i <= N; ++i) {
        check[i][y] --;
        if (y-(i-x) > 0) {
            check[i][y-(i-x)] --;
        }
        if (y+(i-x) <= N) {
            check[i][y+(i-x)] --;
        }
    }
}

void dfs(int depth) {
    if (depth == N+1) {
        ans ++;
        if (ans <= 3) {
            for (int i = 1; i < N; ++i) {
                fout << sol[i] << ' ';
            }
            fout << sol[N] << endl;
        }
        return ;
    }
    for (int i = 1; i <= N; ++i) {
        if (check[depth][i] == 0) {
            sol[depth] = i;
            mark(depth, i);
            dfs(depth+1);
            unmark(depth, i);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("checker.in");
    
    fin >> N;
    
    fin.close();
    
    
    fout.open("checker.out");
    
    dfs(1);
    fout << ans << endl;
    
    fout.close();
    
    return 0;
}






































































