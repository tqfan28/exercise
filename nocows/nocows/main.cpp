//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: nocows
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
const int MAXN = 200;
int K;
const int MAXK = 100;
int state[MAXN+1][MAXK+1] = {};

unsigned int pick(unsigned int k, unsigned int n) {
    if (k > n)
        return 0;
    if (k*2 > n)
        k = n-k;
    if (k == 0)
        return 1;
    
    int d = n;
    for( int i = 2; i <= k; ++i ) {
        d *= (n-i+1);
        d /= i;
    }
    return d;
}

//left_n + right_n + 1 = n
int subtrees(int n, int k) {
    if (k == 0 || n % 2 == 0) {
        state[n][k] = 0;
        return 0;
    }
    
    if (n == 1) {
        state[n][k] = 1;
        return 1;
    }
    
    if (n > pow(2, k)-1) {
        state[n][k] = 0;
        return 0;
    }
    
    if (state[n][k] != -1)
        return state[n][k];
    
    int result = 0;
    
    for (int i = 1; i < n-1; i=i+2) {
        int left = 0;
        int right = 0;
        
        if (state[i][k-1] != -1)
            left = state[i][k-1];
        else
            left = subtrees(i,k-1);
        
        if (state[n-1-i][k-1] != -1)
            right = state[n-1-i][k-1];
        else
            right = subtrees(n-1-i,k-1);
        
        result += (left*right % 9901);
    }
    
    result = result % 9901;
    state[n][k] = result;
    //cout << n << ' ' << k << ' '<< result << endl;
    return result;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("nocows.in");
    fin >> N >> K;
    
    // state[n][k] number of different trees with height at most k, nodes n.
    // full i = 1 + 2 + 2^2+ ... + 2^{j-1} = 2^j-1
    // l 1 2 3  i = 2l-1
    // i 1 3 5
    
    memset(state, -1, sizeof(state));
    
 
    ofstream fout ("nocows.out");
    fout << (9901 + subtrees(N, K) - subtrees(N, K-1)) % 9901 << endl;
    fout.close();
    
    return 0;
}





















