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
bool candidates[2000001] = {};
bool candidates1[2000001] = {};
int largest = 0;

void generator(int k) {
    if (k == 0)
        return;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < largest*i + 1; ++j) {
            if (candidates[j]) {
                for (int s = 0; s < N; ++s) {
                    candidates1[j+values[s]] = true;
                }
                candidates1[j] = true;
            }
        }
        copy(candidates1, candidates1+largest*(i+1)+1, candidates);
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("stamps.in");
    fin >> K >> N;
    for (int i = 0; i < N; ++i) {
        fin >> values[i];
    }
    largest = *max_element(values, values+N);
    candidates[0] = true;
    candidates1[0] = true;
    generator(K);
    
//    for (int i = 0; i < largest*K+1; ++i) {
//        if (candidates[i])
//            cout << i << endl;
//    }
    
    int connected = 1;
    int start = *min_element(values, values+N);
    int end = start+1;
    
    while(start < largest*K+1) {
        while (!candidates[start]) {
            start++;
        }
        if (start < largest*K+1) {
            end = start+1;
        }
        else {
            break;
        }
        while (end < largest*K+1 && candidates[end]) {
            end++;
        }
        connected = max(connected, end - start);
        start = end;
        end = start+1;
    }
    
    ofstream fout ("stamps.out");
    cout << connected<< endl;
    fout.close();
    return 0;
}




































