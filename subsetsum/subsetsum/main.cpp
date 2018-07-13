//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: subsetsum
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
int m;
const int MAXN = 39;
int A[MAXN] = {};
const int MAXS = 100;

//For many sets of consecutive integers from 1 through N (1 <= N <= 39), one can partition the set into two sets whose sums are identical. Given N, your program should print the number of ways a set containing the integers from 1 through N can be partitioned into two sets whose sums are identical. Print 0 if there are no such ways.
// the inputs are non-negative integers



int main(int argc, const char * argv[]) {

    cin >> N;
    int total = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        total += A[i];
    }
    if (total % 2 != 0) {
        cout << false << endl;
        return 0;
    }
    for (int i = 0; i < N; ++i) {
        A[i] -= (total/2);
    }
    int mins = 0;
    int maxs = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] < 0) {
            mins += A[i];
        }
        else {
            maxs += A[i];
        }
    }
    //Q(n, s) = there is a nonempty subset of x1, ..., xn+1 which sums to s
    bool Q[MAXN][MAXS] = {};
    for (int s = mins; s < maxs+1; ++s) {
        for (int i = 0; i < N; ++i) {
            Q[0][s] = (A[i] == s);
        }
    }

    for (int s = mins; s < maxs+1; ++s) {
        for (int i = 0; i < N; ++i) {
            Q[i][s] = (Q[i-1][s] || (A[i] == s) || Q[i-1][s - A[i]]);
        }
    }
    
    cout << Q[N-1][0] << endl;
    return 0;
}
















