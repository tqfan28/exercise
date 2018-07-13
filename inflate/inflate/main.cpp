//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: inflate
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
int M;
int N;
const int MAXN = 10000;
const int MAXM = 10000;
int points[MAXN] = {};
int mins[MAXN] = {};
int states[MAXM+1] = {};



//int solver(int n, int m) {
//    if (n == 0) {
//        return 0;
//    }
//
//    int result = 0;
//    int xn = 0;
//    while(mins[n-1]*xn <= m) {
//        result = max(result, solver(n-1, m - mins[n-1]*xn) + points[n-1]*xn);
//        xn ++;
//    }
//    return result;
//}

int main(int argc, const char * argv[]) {
    
//    clock_t t1,t2;
//    t1=clock();
    ifstream fin;
    fin.open("inflate.in");
    fin >> M >> N;
    
    for (int i = 0; i < N; ++i) {
        fin >> points[i] >> mins[i];
    }
    // x_0*mins[0] + x_1*mins[1] + ... + x_{N-1}*mins[N-1] <= M
    // maximize (x_0*points[0] + x_1*points[1] + ... + x_{N-1}*points[N-1])
    

//    bool tracker = 0;
//    for (int i = 0; i< N; ++i) {
//        for (int m = 1; m < M+1; ++m) {
//            int x = 0;
//            int result = 0;
//            while(mins[i]*x <= m) {
//                result = max(result, states[tracker][m - mins[i]*x] + points[i]*x);
//                x++;
//            }
//            states[!tracker][m] = result;
//        }
//        tracker = !tracker;
//    }
    
    for (int i = 0; i< N; ++i) {
        for (int m = mins[i]; m < M+1; ++m) {
            states[m] = max(states[m], states[m - mins[i]] + points[i]);
        }
    }

    
    ofstream fout ("inflate.out");
    fout << states[M] << endl;
    fout.close();
    
//    t2=clock();
//    float diff ((float)t2-(float)t1);
//    cout<<diff<<endl;

    return 0;
}
































