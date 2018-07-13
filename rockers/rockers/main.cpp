//
//  main.cpp
//  rockers
//
//  Created by TFAN on 2018/7/13.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: rockers
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
int T;
int M;
const int MAXN = 20;
int songLen[MAXN] = {};

int main(int argc, const char * argv[]) {
    
    ifstream fin ("rockers.in");
    fin >> N >> T >> M;
    for (int i = 0; i< N; ++i) {
        fin >> songLen[i];
    }
    
    int sol = 0;
    for (int i = 1; i < (1<<N); ++i) {
        int current = 0;
        int m = 1;
        int t = T;
        for (int j = 0; j < N; ++j) {
            if ((1<<j)&i) {
                if (songLen[j] <= t) {
                    t = t-songLen[j];
                    current++;
                }
                else if (songLen[j] > T) {
                    current = 0;
                    break;
                }
                else {
                    if (m+1>M) {
                        current = 0;
                        break;
                    }
                    else {
                        t = T-songLen[j];
                        m++;
                        current++;
                    }
                }
            }
        }
        sol = max(current, sol);
    }
    
    ofstream fout ("rockers.out");
    fout << sol << endl;
    fout.close();
    return 0;
}

























