//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: money
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
int V;
int N;
const int MAXV = 25;
const int MAXN = 10000;
int values[MAXV+1] = {};
long long state[MAXV+1][MAXN+1] = {};

// sum_i values[i]*select[i] = N
// state[v][n] #of solutions that first v values sums to n;

long long solver(int v, int n) {
    long long result = 0;
    if (n == 0)
        return 1;
    
    if (v == 1) {
        if (n % values[v] == 0) {
            state[v][n] = 1;
            return 1;
        }
        else
            return 0;
    }
    
    if (state[v][n] != -1)
        return state[v][n];
    
    for (int i = 0; i*values[v] <= n; ++i) {
        result += solver(v-1, n-i*values[v]);
    }
    //cout << v << ' ' << n << ' ' << result << endl;
    state[v][n] = result;
    return result;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("money.in");
    fin >> V >> N;
    
    for (int i = 1; i < V+1; ++i) {
        fin >> values[i];
    }

    memset(state, -1, sizeof(state));
    ofstream fout ("money.out");
    
    fout << solver(V, N) << endl;
    
    fout.close();
    
    return 0;
}























