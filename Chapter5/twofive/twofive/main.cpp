//
//  main.cpp
//  twofive
//
//  Created by TFAN on 2018/8/15.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: twofive
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
char current[6][6];
int N;
char target[6][6];
int dp[6][6][6][6][6] = {};


//void dfs(int row1, int row2, int row3, int row4, int row5) {
//    int total = row1 + row2 + row3 + row4 + row5;
//    cout << row1 << ' '<< row2 << ' ' << row3 << ' ' << row4 << ' ' << row5 << ' '<< endl;
//    char curchar = char(65 + total);
//    if (total == 25) {
//        cout << numsol << endl;;
//        for (int i = 0; i < 5; ++i) {
//            for (int j = 0; j < 5; ++j) {
//                cout << current[i][j];
//            }
//            cout << endl;
//        }
//        numsol ++;
//        cout << endl;
//        return ;
//    }
//    if (row1 < 5) {
//        current[0][row1] = curchar;
//        dfs(row1+1, row2, row3, row4, row5);
//    }
//    if (row1 != 0 && row2 < row1 && row2 < 5) {
//        current[1][row2] = curchar;
//        dfs(row1, row2+1, row3, row4, row5);
//    }
//    if (row2 != 0 && row3 < row2 && row3 < 5) {
//        current[2][row3] = curchar;
//        dfs(row1, row2, row3+1, row4, row5);
//    }
//    if (row3 != 0 && row4 < row3 && row4 < 5) {
//        current[3][row4] = curchar;
//        dfs(row1, row2, row3, row4+1, row5);
//    }
//    if (row4 != 0 && row5 < row4 && row5 < 5) {
//        current[4][row5] = curchar;
//        dfs(row1, row2, row3, row4, row5+1);
//    }
//}
//
//string output;
//
//
//void dfs_N(int row1, int row2, int row3, int row4, int row5, int n) {
//    int total = row1 + row2 + row3 + row4 + row5;
//    char curchar = char(65 + total);
//    if (total == 25) {
//        for (int i = 1; i < 6; ++i) {
//            for (int j = 1; j < 6; ++j) {
//                output += current[i][j];
//            }
//        }
//        return ;
//    }
//    int prev = 0;
//    if (row1 < 5) {
//        if (n <= dp[row1+1][row2][row3][row4][row5]) {
//            current[1][row1+1] = curchar;
//            dfs_N(row1+1, row2, row3, row4, row5, n);
//            return ;
//        }
//        else {
//            prev += dp[row1+1][row2][row3][row4][row5];
//        }
//    }
//    if (row1 != 0 && row2 < row1 && row2 < 5) {
//        if (n - prev <= dp[row1][row2+1][row3][row4][row5]) {
//            current[2][row2+1] = curchar;
//            dfs_N(row1, row2+1, row3, row4, row5, n-prev);
//            return ;
//        }
//        else {
//            prev += dp[row1][row2+1][row3][row4][row5];
//        }
//
//    }
//    if (row2 != 0 && row3 < row2 && row3 < 5) {
//        if (n - prev <= dp[row1][row2][row3+1][row4][row5]) {
//            current[3][row3+1] = curchar;
//            dfs_N(row1, row2, row3+1, row4, row5, n-prev);
//            return ;
//        }
//        else {
//            prev += dp[row1][row2][row3+1][row4][row5];
//        }
//    }
//    if (row3 != 0 && row4 < row3 && row4 < 5) {
//        if (n - prev <= dp[row1][row2][row3][row4+1][row5]) {
//            current[4][row4+1] = curchar;
//            dfs_N(row1, row2, row3, row4+1, row5, n-prev);
//            return ;
//        }
//        else {
//            prev += dp[row1][row2][row3][row4+1][row5];
//        }
//    }
//    if (row4 != 0 && row5 < row4 && row5 < 5) {
//        if (n - prev <= dp[row1][row2][row3][row4][row5+1]) {
//            current[5][row5+1] = curchar;
//            dfs_N(row1, row2, row3, row4, row5+1, n-prev);
//            return ;
//        }
//        else {
//            prev += dp[row1][row2][row3][row4][row5+1];
//        }
//    }
//
//}
//
//int sol = 0;
//
//void dfs_W(int row1, int row2, int row3, int row4, int row5) {
//    int total = row1 + row2 + row3 + row4 + row5;
//    char curchar = char(65 + total);
//    if (total == 25) {
//        sol ++;
//        return ;
//    }
//
//    if (row1 < 5) {
//        if (target[1][row1+1] == curchar) {
//            dfs_W(row1+1, row2, row3, row4, row5);
//            return ;
//        }
//        else {
//            sol += dp[row1+1][row2][row3][row4][row5];
//        }
//    }
//    if (row1 != 0 && row2 < row1 && row2 < 5) {
//        if (target[2][row2+1] == curchar) {
//            dfs_W(row1, row2+1, row3, row4, row5);
//            return ;
//        }
//        else {
//            sol += dp[row1][row2+1][row3][row4][row5];
//        }
//
//    }
//    if (row2 != 0 && row3 < row2 && row3 < 5) {
//        if (target[3][row3+1] == curchar) {
//            dfs_W(row1, row2, row3+1, row4, row5);
//            return ;
//        }
//        else {
//            sol += dp[row1][row2][row3+1][row4][row5];
//        }
//    }
//    if (row3 != 0 && row4 < row3 && row4 < 5) {
//        if (target[4][row4+1] == curchar) {
//            dfs_W(row1, row2, row3, row4+1, row5);
//            return ;
//        }
//        else {
//            sol += dp[row1][row2][row3][row4+1][row5];
//        }
//    }
//    if (row4 != 0 && row5 < row4 && row5 < 5) {
//        if (target[5][row5+1] == curchar) {
//            dfs_W(row1, row2, row3, row4, row5+1);
//            return ;
//        }
//        else {
//            sol += dp[row1][row2][row3][row4][row5+1];
//        }
//    }
//
//}


int dfs(int a, int b, int c, int d, int e) {
    int total = a+b+c+d+e;
    
    if (total == 25)
        return 1;
    
    if (dp[a][b][c][d][e] != 0)
        return dp[a][b][c][d][e];
    char curchar = char(65+total);
    
    if (a < 5 && (current[1][a+1] == '?' || current[1][a+1] == curchar)) {
        dp[a][b][c][d][e] += dfs(a+1, b, c, d, e);
    }
    if (b < a && (current[2][b+1] == '?' || current[2][b+1] == curchar)) {
        dp[a][b][c][d][e] += dfs(a, b+1, c, d, e);
    }
    if (c < b && (current[3][c+1] == '?' || current[3][c+1] == curchar)) {
        dp[a][b][c][d][e] += dfs(a, b, c+1, d, e);
    }
    if (d < c && (current[4][d+1] == '?' || current[4][d+1] == curchar)) {
        dp[a][b][c][d][e] += dfs(a, b, c, d+1, e);
    }
    if (e < d && (current[5][e+1] == '?' || current[5][e+1] == curchar)) {
        dp[a][b][c][d][e] += dfs(a, b, c, d, e+1);
    }
    //cout << curchar << ' ' << dp[a][b][c][d][e] << endl;
    return dp[a][b][c][d][e];
}

void Nsolver(int n) {
    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            for (int k = 0; k < 25; ++k) {
                current[i][j] = char(k+65);
                memset(dp, 0, sizeof(dp));
                int tmp = dfs(0, 0, 0, 0, 0);
                if (n <= tmp)
                    break;
                n -= tmp;
            }
        }
    }
}

int Wsolver() {
    
    int sol = 0;
    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            for (int k = 0; k < 25; ++k) {
                if (char(k+65) < target[i][j]) {
                    current[i][j] = char(k+65);
                    memset(dp, 0, sizeof(dp));
                    sol += dfs(0, 0, 0, 0, 0);
                }
            }
            current[i][j] = target[i][j];
        }
    }
    return sol+1;
}

void init() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            current[i][j] = '?';
        }
    }
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("twofive.in");
    
    char pre;
    fin >> pre;
    if (pre == 'N') {
        fin >> N;
    }
    else if (pre == 'W') {
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                fin >> target[i][j];
            }
        }
    }
    
    fin.close();
    
    init();

    
    ofstream fout;
    fout.open("twofive.out");
    
    if (pre == 'N') {
        Nsolver(N);
        
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                fout << current[i][j];
            }
        }
        fout << endl;
    }
    
    else if (pre == 'W') {
        fout << Wsolver() << endl;
    }
    
    fout.close();
    
    return 0;
}


























































