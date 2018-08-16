//
//  main.cpp
//  charrec_v2
//
//  Created by TFAN on 2018/8/12.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: charrec
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>


using namespace std;
//const int infty = 0x7fffffff;
char font[541][21];
const int MAXN = 1200;
char chars[MAXN+1][21];
int M;
int mat[MAXN+1][541] = {};
// mat[i][j] mismatch between i-th row of font and j-th row of chars
int Less[MAXN+1] = {};
char lesschar[MAXN+1];
// less[i] min mismatch row i and row i+19
// lesschar[i] the char corresponds to the min mismatch
int More[MAXN+1] = {};
char morechar[MAXN+1];
int Equal[MAXN+1] = {};
char equalchar[MAXN+1];
int dp[MAXN+1] = {};
int N;
const string az = " abcdefghijklmnopqrstuvwxyz";
string sol[MAXN+1];

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    
    fin.open("font.in");
    
    fin >> M;
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= 20; ++j) {
            fin >> font[i][j];
        }
    }
    
    
    fin.close();
    
    fin.open("charrec.in");
    
    fin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= 20; ++j) {
            fin >> chars[i][j];
        }
    }
    
    fin.close();
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            for (int k = 1; k <= 20; ++k) {
                if (font[j][k] != chars[i][k]) {
                    mat[i][j] ++;
                }
            }
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        Equal[i] = 401;
        More[i] = 401;
        Less[i] = 401;
    }
    
    for (int k = 1; k <= M; k += 20)
    {
        for (int i = 1; i <= N; ++i)
        {
            if (i + 19 <= N)
            {
                int tmp = 0;
                for (int l = 1; l <= 20; ++l) {
                     tmp += mat[i + l - 1][k + l - 1];
                }

                if (tmp < Equal[i])
                {
                    equalchar[i] = (tmp > 120 ? '?' : az[k / 20]);
                    Equal[i] = tmp;
                }
            }
            for (int j = 1; j <= 21; ++j)
            {
                if (j < 21 && i + 18 <= N)
                {
                    int tmp = 0;
                    for (int l = 1; l < j; ++l) {
                        tmp += mat[i + l - 1][k + l - 1];
                    }
                    for (int l = j; l <= 19; ++l) {
                        tmp += mat[i + l - 1][k + l];
                    }
                    if (tmp < Less[i])
                    {
                        lesschar[i] = (tmp > 120 ? '?' : az[k / 20]);
                        Less[i] = tmp;
                    }
                }
                
                if (i + 20 <= N)
                {
                    int tmp = 0;
                    for (int l = 1; l < j; ++l) {
                        tmp += mat[i + l - 1][k + l - 1];
                    }
                    for (int l = j; l <= 21; ++l) {
                        tmp += mat[i + l][k + l - 1];
                    }
                    if (tmp < More[i])
                    {
                        morechar[i] = (tmp > 120 ? '?' : az[k / 20]);
                        More[i] = tmp;
                    }
                }
            }
        }
    }
    
    for (int i = 1; i < 19; ++i) {
        dp[i] = 401;
    }

    
    for (int i = 19; i <= N; ++i) {
        dp[i] = dp[i-19] + Less[i-18];
        sol[i] = sol[i-19] + lesschar[i-18];
        
        if (i >= 20) {
            if (dp[i] > dp[i-20] + Equal[i-19]) {
                dp[i] = dp[i-20] + Equal[i-19];
                sol[i] = sol[i-20] + equalchar[i-19];
            }
        }
        
        if (i >= 21) {
            if (dp[i] > dp[i-21] + More[i-20]) {
                dp[i] = dp[i-21] + More[i-20];
                sol[i] = sol[i-21] + morechar[i-20];
            }
        }
        //cout << dp[i] << ' ' << sol[i] << endl;
    }
    
    
    ofstream fout;
    fout.open("charrec.out");
    
    fout << sol[N] << endl;
    
    fout.close();
    
    return 0;
}












































