//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: hamming
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int N;
int B;
int D;
const int MAXN = 64;
const int MAXB = 8;
const int MAXD = 7;
int result[MAXN] = {};

struct node {
    int state;
    int level;
    bool feasible;
    node * left;
    node * right;
};


//BFS
int hamming_dist (int a, int b) {
    int c = a^b;
    int dist = 0;
    while (c != 0) {
        if (c % 2 == 1)
            dist ++;
        c = (c - (c % 2))/2;
    }
    return dist;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("hamming.in");
    fin >> N >> B >> D;

    int num = 0;
    int attempt = 0;
    while (num < N) {
        bool checker = true;
        for (int i = 0; i < num; ++i) {
            if (hamming_dist(attempt, result[i]) < D) {
                checker = false;
                break;
            }
        }
        if (checker) {
            result[num] = attempt;
            num++;
        }
        attempt++;
    }
    ofstream fout ("hamming.out");
    int counter = 0;
    for (int i = 0; i< N; ++i) {
        if (i == N-1 || counter == 9) {
            fout << result[i] <<endl;
            counter = 0;
        }
        else {
            counter ++;
            fout << result[i] << ' ';
        }
    }
    fout.close();
    
    return 0;
}















