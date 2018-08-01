//
//  main.cpp
//  job
//
//  Created by TFAN on 2018/7/16.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: job
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>


using namespace std;
const int infty = 0x7fffffff;
int N;
int M1;
int M2;
const int MAXN = 1000;
const int MAXM = 30;
int A_total[MAXN] = {};
int B_total[MAXN] = {};
int A_process[MAXM] = {};
int A_wait[MAXM] = {};
int B_process[MAXM] = {};
int B_wait[MAXM] = {};

int main(int argc, const char * argv[]) {
    
    ifstream fin ("job.in");
    fin >> N >> M1 >> M2;
    for (int i = 0; i < M1; ++i) {
        fin >> A_process[i];
    }
    for (int i = 0; i < M2; ++i) {
        fin >> B_process[i];
    }
    
    for (int i = 0; i < N; ++i) {
        int tmp = infty;
        int index = 0;
        for (int j = 0; j < M1; ++j) {
            if (A_process[j]+A_wait[j] < tmp) {
                index = j;
                tmp = A_process[j]+A_wait[j];
            }
        }
        A_total[i] = tmp;
        A_wait[index] = A_total[i];
    }
    
    int a = A_total[N-1];
    
    for (int i = 0; i < N; ++i) {
        int tmp = infty;
        int index = 0;
        for (int j = 0; j < M2; ++j) {
            if (B_process[j]+B_wait[j] < tmp) {
                index = j;
                tmp = B_process[j]+B_wait[j];
            }
        }
        B_total[i] = tmp;
        B_wait[index] = B_total[i];
    }
    
    int b = 0;
    
    for (int i = 0; i < N; ++i) {
        b = max(b, A_total[i] + B_total[N-i-1]);
    }
    
    ofstream fout ("job.out");
    fout << a << ' ' << b << endl;
    fout.close();
    return 0;
}






























