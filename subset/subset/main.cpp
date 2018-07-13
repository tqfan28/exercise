//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: subset
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>


using namespace std;
int N;
const int MAXN = 40;
const int MAXS = 780+1;


int main(int argc, const char * argv[]) {
    
    ifstream fin ("subset.in");
    fin >> N;
    
    ofstream fout ("subset.out");
    if ( (1+N)*N/2 % 2 != 0) {
        fout << 0 << endl;
        return 0;
    }
    
    int mins = 1;
    int maxs = (1+N)*N/4;
    //State(n, s) = # of different nonempty subsets of 1, 2, ..., n which sum to s
    
    unsigned int State[MAXN][MAXS] = {};
    State[1][1] = 1;
    
    for (int s = mins; s < maxs+1; ++s) {
        for (int i = 2; i < N+1; ++i) {
            if (State[i-1][s] > 0) {
                State[i][s] += State[i-1][s];
            }
            if (i == s) {
                State[i][s] ++;
            }
            if (State[i-1][s-i] > 0) {
                State[i][s] += State[i-1][s-i];
            }
        }
    }
    
    fout << State[N][maxs]/2 << endl;
    fout.close();
    
    return 0;
}

















