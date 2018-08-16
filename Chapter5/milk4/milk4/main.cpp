//
//  main.cpp
//  milk4
//
//  Created by TFAN on 2018/8/5.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: milk4
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
#include <math.h>
//#include <iomanip>


using namespace std;
//const int infty = 0x7fffffff;
const int MAXP = 100;
const int MAXQ = 20000;
int pails[MAXP] = {};
int Q;
int P;
bool use[MAXP] = {};
bool stop = false;

bool check() {
    bool dp[MAXQ+1] = {};
    dp[0] = true;
    for (int i = 0; i < Q+1; ++i) {
        if (dp[i]) {
            for (int j = 0; j < P; ++j) {
                if (use[j]) {
                    if (i + pails[j] <= Q) {
                        dp[i+ pails[j]] = true;
                    }
                }
            }
        }
    }
    return dp[Q];
}

void solver(int p, int d) {
    
    if (d == 0) {
        if (check()) {
            stop = true;
            return ;
        }
        return ;
    }
    if (p == P) {
        return ;
    }
    
    use[p] = true;
    solver(p+1, d-1);
    if (stop) {
        return ;
    }
    use[p] = false;
    
    if (p+d <= Q) {
        solver(p+1, d);
    }
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("milk4.in");
    
    fin >> Q >> P;
    for (int i = 0; i < P; ++i) {
        fin >> pails[i];
    }
    
    fin.close();
    
    sort(pails, pails+P);
    
    int d = 1;
    
    while (d < P+1) {
        solver(0, d);
        if (stop)
            break;
        ++d;
    }
    
    ofstream fout;
    fout.open("milk4.out");
    
    fout << d;
    for (int i = 0; i < P; ++i) {
        if (use[i]) {
            fout << ' ' << pails[i];
        }
    }
    fout << endl;
    
    fout.close();
    
    return 0;
}



































