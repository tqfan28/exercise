//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: wormhole
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int wormholes_x [13];
int wormholes_y [13];
int pairs [13];
int N;
int right_next[13];

bool check_cycle() {
    for (int i = 1; i < N+1; ++i) {
        int position = pairs[i];
        for (int j = 1; j < N; ++j) {
            position = right_next[position];
            position = pairs[position];
        }
        if (position != 0)
            return true;
    }
    return false;
}

int partitionTwo() {
    int result = 0;
    int i = 0;
    
    for (i = 1; i < N+1; ++i) {
        if (pairs[i] == 0)
            break;
    }
    
    if (i == N+1) {
        if (check_cycle())
            return 1;
        else
            return 0;
    }
    
    for (int j = i+1; j < N+1; ++j) {
        if (pairs[j] == 0) {
            pairs[i] = j;
            pairs[j] = i;
            result += partitionTwo();
            pairs[i] = 0;
            pairs[j] = 0;
        }
    }
    return result;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin ("wormhole.in");
    fin >> N;
    for (int i = 1; i < N+1; ++i) {
        fin >> wormholes_x[i] >> wormholes_y[i];
    }
    fin.close();
    
    for (int i = 1; i < N+1; ++i) {
        for (int j = 1; j < N+1; ++j) {
            if (i != j
                && wormholes_y[i] == wormholes_y[j]
                && wormholes_x[j] > wormholes_x[i]) {
                if (right_next[i] == 0)
                    right_next[i] = j;
                else if (wormholes_x[right_next[i]] > wormholes_x[j])
                    right_next[i] = j;
            }
        }
    }
    
    ofstream fout ("wormhole.out");
    //cout << partitionTwo();
    fout << partitionTwo() << endl;
    fout.close();
    return 0;
}






