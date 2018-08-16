//
//  main.cpp
//  theme
//
//  Created by TFAN on 2018/8/3.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: theme
 LANG: C++
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <math.h>
#include <iomanip>


using namespace std;
const int infty = 0x7fffffff;
const int MAXN = 5000;
int N = 0;
int melody[MAXN] = {};
int diff[MAXN] = {};

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("theme.in");
    
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> melody[i];
    }
    
    fin.close();
    
    for (int i = 1; i < N; ++i) {
        diff[i] = melody[i] - melody[i-1];
    }
    
    int ans = 1;
    
    for (int i = 1; i < N-ans; ++i) {
        for (int j = i + ans; j < N-ans; ++j) {
            if (diff[i] == diff[j]) {
                int k = 1;
                while(diff[i+k] == diff[j+k] && i+k+1 < j) {
                    k++;
                }
                if (k > ans) {
                    ans = k;
                }
            }
        }
    }
    
    ofstream fout;
    fout.open("theme.out");
    
    if (ans < 4)
        fout << 0 << endl;
    else
        fout << ans+1 << endl;
    
    fout.close();
    
    return 0;
}


































