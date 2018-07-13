//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: humble
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
const int MAXN = 100000;
int primes[100] = {};
const int infty = 2147483647;
int humble[MAXN] = {};
int indexes[100] = {};


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("humble.in");
    fin >> K >> N;
    
    for (int i = 0; i < K; ++i) {
        fin >> primes[i];
    }
    // find minimal prod_i primes[i]^xi that > humble[N-1]
    int index = 1;
    humble[0] = 1;
    
    while(index < N+1) {
        humble[index] = infty;
        int tmp = 0;
        for (int k = 0; k < K; ++k) {
            while (humble[indexes[k]]*primes[k] <= humble[index-1]) {
                indexes[k]++;
            }
            if (humble[indexes[k]]*primes[k] < humble[index]) {
                humble[index] = humble[indexes[k]]*primes[k];
                tmp = k;
            }
            //cout << humble[indexes[k]]*primes[k] << ' '<< index << ' '<< humble[index] << endl;
        }
        //cout << index << ' '<< humble[index] << endl;
        indexes[tmp]++;
        index++;
    }
    
    ofstream fout ("humble.out");
    fout << humble[N] << endl;
    
    return 0;
}


































