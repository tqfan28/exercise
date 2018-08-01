//
//  main.cpp
//  buylow_v2
//
//  Created by TFAN on 2018/7/28.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: buylow
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
#include <utility>


using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 5000;
int prices[MAXN] = {};
int dp1[MAXN] = {};
int dp2[MAXN] = {};


int main(int argc, const char * argv[]) {
    
    ifstream fin ("buylow.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> prices[i];
    }
    for (int i = 0; i < N; ++i) {
        dp1[i] = 1;
        dp2[i] = 1;
        
        for (int j = 0; j < i; ++j) {
            if (prices[j] == prices[i]) {
                dp2[i] = 0;
            }
        }
    }
    
    
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (prices[i] < prices[j]) {
                dp1[i] = max(dp1[i], dp1[j]+1);
            }
        }
        bool check = false;
        int tmp = dp2[i];
        for (int j = 0; j < i; ++j) {
            if (prices[i] < prices[j] && dp1[i] == dp1[j]+1) {
                dp2[i] += dp2[j];
                check = true;
            }
            
        }
        
        if (dp2[i] > 0) {
            for (int j = 0; j < i; ++j) {
                if (prices[i] == prices[j] && dp1[i] == dp1[j]) {
                    dp2[i] -= dp2[j];
                }
            }
        }
        
        if (check && tmp != 0) {
            dp2[i]--;
        }
        cout << i<< ' '<< prices[i] << ' ' << dp1[i] << ' ' << dp2[i] << endl;
    }
    
    int a = 0;
    int b = 0;
    for (int i = 0; i < N; ++i) {
        if (a < dp1[i]) {
            a = dp1[i];
        }
    }
    
    for (int i = 0; i < N; ++i) {
        if (a == dp1[i]) {
            b += dp2[i];
        }
    }
    
    ofstream fout ("buylow.out");
    cout << a << ' ' << b << endl;
    fout.close();
    return 0;
}































