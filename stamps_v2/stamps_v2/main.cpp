//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: stamps
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <time.h>

using namespace std;
int K;
int N;
const int MAXN = 50;
int values[MAXN] = {};
int states[2000002] = {};
int largest = 0;


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("stamps.in");
    fin >> K >> N;
    for (int i = 0; i < N; ++i) {
        fin >> values[i];
    }
    largest = *max_element(values, values+N);
    // states[i] minimal number of stamps needed to express i
    // states[i] = min(i, states[i-values[j]]+1)
    for (int i = 1; i < 2000002; ++i) {
        states[i] = i;
    }
    
    for (int i = 1; i < largest*K+1; ++i) {
        int tmp = i;
        for (int j = 0; j < N; ++j) {
            if (i >= values[j]) {
                tmp = min(tmp, states[i-values[j]]+1);
            }
        }
        states[i] = tmp;
        //cout << i << ' '<< states[i] << endl;
    }
   
    ofstream fout ("stamps.out");
    int i = 1;
    while(states[i] <= K) {
        ++i;
    }
    fout << i-1 << endl;
    fout.close();
    return 0;
}





































