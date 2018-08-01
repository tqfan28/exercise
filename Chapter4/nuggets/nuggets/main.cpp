//
//  main.cpp
//  nuggets
//
//  Created by TFAN on 2018/7/14.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: nuggets
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



using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 10;
int numbers[MAXN] = {};

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else {
        return gcd(b, a % b);
    }
}

int dp[MAXN][65025] = {};

bool check(int n, int i) {
    if (n == 0) {
        if (i % numbers[0] == 0) {
            dp[0][i] = 1;
            return true;
        }
        else {
            dp[0][i] = -1;
            return false;
        }
    }
    
    int j = 0;
    while(j*numbers[n] <= i) {
        if (dp[n-1][i-j*numbers[n]] == 0) {
            if ( check(n-1, i-j*numbers[n])) {
                dp[n][i] = 1;
                return true;
            }
        }
        else if (dp[n-1][i-j*numbers[n]] == 1) {
            dp[n][i] = 1;
            return true;
        }
        ++j;
    }
    
    dp[n][i] = -1;
    return false;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin ("nuggets.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> numbers[i];
    }
    bool cd = false;
    int upper = infty;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            int tmp = gcd(numbers[i], numbers[j]);
            if (tmp == 1) {
                upper = min(upper, numbers[i]*numbers[j] - numbers[i]-numbers[j]);
                cd = true;
            }
        }
    }
    
    ofstream fout ("nuggets.out");
    
    if (!cd) {
        fout << 0 << endl;
        return 0;
    }
    
    for (int i = 0; i < N; ++i) {
        dp[i][0] = 1;
    }

    
    for (int i = upper; i > 0; --i) {
        if (!check(N-1, i)) {
            fout << i << endl;
            return 0;
        }
    }
    
    fout << 0 << endl;
    
    fout.close();
    return 0;
}


























