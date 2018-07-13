//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: fracdec
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

using namespace std;
int N;
int D;
const int MAXN = 100000;
int state[10*MAXN+1] = {};
int digits[10*MAXN+1] = {};

int count_digits (int n) {
    if (n == 0)
        return 1;
    int result = 0;
    while(n != 0) {
        n = n/10;
        result ++;
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("fracdec.in");
    fin >> N >> D;

    int counter = 0;
    bool clear;
    
    while(true) {
        digits[counter] = N/D;
        N -= digits[counter]*D;
        //cout << N << ' '<< counter << endl;
        counter ++;
        if (N == 0) {
            state[N] = counter;
            clear = true;
            break;
        }
        
        N *= 10;
        if (state[N] != 0) {
            clear = false;
            break;
        }
        
        state[N] = counter;
    }
    //cout << state[10] << endl;
    
    ofstream fout ("fracdec.out");
    
    fout << digits[0] << '.';
    int changeline = count_digits(digits[0]);
    changeline = (changeline + 1) % 76;
    if (counter == 1) {
        fout << 0 << endl;
    }
    else {
        for (unsigned int i = 1; i < state[N]; ++i) {
            if (changeline == 0)
                fout << endl;
            fout << digits[i];
            changeline = (changeline + 1) % 76;
        }
        if (!clear) {
            if (changeline == 0)
                fout << endl;
            fout << '(';
            changeline = (changeline + 1) % 76;
            for (unsigned int i = state[N]; i < counter; ++i) {
                if (changeline == 0)
                    fout << endl;
                fout << digits[i];
                changeline = (changeline + 1) % 76;
            }
            if (changeline == 0)
                fout << endl;
            fout << ')';
            changeline = (changeline + 1) % 76;
        }
        fout << endl;
    }
    
    fout.close();
    
    return 0;
}






























