//
//  main.cpp
//  charrec
//
//  Created by TFAN on 2018/8/10.
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
// mat[i][j] match between i-th row of font and j-th row of chars
int Less[MAXN+1] = {};
char lesschar[MAXN+1];
// less[i] max match row i and row i+19
// lesschar[i] the char corresponds to the max match
int more[MAXN+1] = {};
char morechar[MAXN+1];
int Equal[MAXN+1] = {};
char equalchar[MAXN+1];
int dp[MAXN+1] = {};
int N;
const string az = " abcdefghijklmnopqrstuvwxyz?";
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
                if (font[j][k] == chars[i][k]) {
                    mat[i][j] ++;
                }
            }
        }
    }


    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= 26; ++j) {
            
            int lesstmp = 0;
            if (i + 18 <= N) {
                for (int l = 0; l < 20; ++l) {
                    int lesstmpl = 0;
                    for (int k = 0; k < l; ++k) {
                        lesstmpl += mat[i+k][j*20+k+1];
                    }
                    for (int k = l+1; k < 20; ++k) {
                        lesstmpl += mat[i+k-1][j*20+k+1];
                    }
                    
                    lesstmp = max(lesstmp, lesstmpl);
                }
                if (lesstmp > Less[i]) {
                    Less[i] = lesstmp;
                    if (Less[i] < 280) {
                        lesschar[i] = az[27];
                    }
                    else {
                        lesschar[i] = az[j];
                    }
                }
            }

            
            int moretmp = 0;
            
            if (i + 20 <= N) {
                for (int l = 0; l < 21; ++l) {
                    int moretmpl = 0;
                    for (int k = 0; k < l; ++k) {
                        moretmpl += mat[i+k][j*20+k+1];
                    }
                    //moretmpl += mat[i+l][j*20+l+1];
                    for (int k = l+1; k < 21; ++k) {
                        moretmpl += mat[i+k-1][j*20+k+1];
                    }
                    
                    moretmp = max(moretmp, moretmpl);
                }
                if (moretmp > more[i]) {
                    more[i] = moretmp;
                    if (more[i] < 280) {
                        morechar[i] = az[27];
                    }
                    else {
                        morechar[i] = az[j];
                    }
                }
            }
            
            
            int equaltmp = 0;
            
            if (i + 19 <= N) {
                for (int k = 0; k < 20; ++k) {
                    equaltmp += mat[i+k][j*20+k+1];
                }
                if (equaltmp > Equal[i]) {
                    Equal[i] = equaltmp;
                    if (Equal[i] < 280) {
                        equalchar[i] = az[27];
                    }
                    else {
                        equalchar[i] = az[j];
                    }
                }
            }
        }
    }
    

    for (int i = 19; i <= N; ++i) {
        dp[i] = dp[i-19] + Less[i-18];
        sol[i] = sol[i-19] + lesschar[i-18];
        
        if (i >= 20) {
            if (dp[i] < dp[i-20] + Equal[i-19]) {
                dp[i] = dp[i-20] + Equal[i-19];
                sol[i] = sol[i-20] + equalchar[i-19];
            }
        }
        
        
        if (i >= 21) {
            if (dp[i] < dp[i-21] + more[i-20]) {
                dp[i] = dp[i-21] + more[i-20];
                sol[i] = sol[i-21] + morechar[i-20];
            }
        }
    
        
        //cout << i << ' '<< dp[i] <<' ' << sol[i] << endl;
    }

    
    ofstream fout;
    fout.open("charrec.out");
    
    fout << sol[N] << endl;
    
    fout.close();
    
    return 0;
}










































