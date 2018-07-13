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
//bool humble[2147483647] = {};
int humble[MAXN] = {};

bool inHumble(int n, int end) {
    int start = 0;
    while(start <= end) {
        int middle = start + (end - start)/2;
        
        if (humble[middle] == n)
            return true;
        else if (humble[middle] < n){
            start = middle+1;
        }
        else {
            end = middle-1;
        }
    }
    return false;
}

bool isHumble(int n, int index) {
    for (int k = 0; k < K; ++k) {
        if (n % primes[k] == 0) {
            n = n/primes[k];
            if (inHumble(n, index)) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("humble.in");
    fin >> K >> N;
    
    for (int i = 0; i < K; ++i) {
        fin >> primes[i];
    }
    // find minimal prod_i primes[i]^xi that > humble[N-1]
    int index = 1;
    int n = 2;
    humble[0] = 1;

    while(index < N+1) {
        if (isHumble(n, index-1)) {
            humble[index] = n;
            //cout << index << ' '<< n << endl;
            index++;
        }
        n++;
    }
    
    ofstream fout ("humble.out");
    fout << n-1 << endl;
    
    return 0;
}

































