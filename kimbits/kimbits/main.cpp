//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: kimbits
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
int N;
int L;
unsigned int I;
unsigned int states[33][33];



int main(int argc, const char * argv[]) {
    
    ifstream fin;
    
    fin.open("kimbits.in");
    fin >> N >> L >> I;

    // states[n][l] length n, total number of 1 == l
    
    for (int i = 0; i < 33; ++i) {
        states[i][0] = 1;
    }

    for (int n = 1; n < 33; ++n) {
        for (int l = 1; l < 33; ++l) {
            states[n][l] = states[n-1][l] + states[n-1][l-1];
        }
    }
    
    
    ofstream fout ("kimbits.out");
    for (int n = N-1; n >= 0; --n) {

        //cout <<n << " "<<L << " " << I << endl;
        unsigned int tmp = 0;
        for (int j = 0; j <=L; ++j) {
            tmp += states[n][j];
        }
        if (I <= tmp) {
            fout << 0;
        }
        else {
            fout << 1;
            I -= tmp;
            --L;
        }
        
    }
    fout << endl;
    fout.close();
    return 0;
}

