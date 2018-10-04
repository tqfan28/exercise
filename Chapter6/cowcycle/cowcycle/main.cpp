//
//  main.cpp
//  cowcycle
//
//  Created by TFAN on 2018/9/26.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: cowcycle
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
//#include <string>
#include <stdio.h>
//#include <ctype.h>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
#include <math.h>
//#include <iomanip>

using namespace std;
int F, F1, F2;
int R, R1, R2;
int cntr = 0;
int cntf = 0;
int feasibleF[81] = {};
int feasibleR[41] = {};
double ratios[56*36] = {};
double diff[56*36] = {};
double minvar = 99999;
int ansf[81] = {};
int ansr[41] = {};

void check() {

    
    int cnt = 0;

    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < R; ++j) {
                ratios[cnt] = double(feasibleF[i])/double(feasibleR[j]);
                cnt++;
        }
    }
    
    sort(ratios, ratios+cnt);
    
    if (ratios[cnt-1] < ratios[0]*3)
        return ;
    
    for (int i = 1; i < cnt; ++i) {
        diff[i] = ratios[i] - ratios[i-1];
    }
    
    sort(diff+1, diff+cnt);
    
    double mean = 0.0;
    for (int i = 1; i < cnt; ++i) {
        mean += diff[i];
    }
    mean = mean/(cnt-1);
    
    double var = 0.0;
    for (int i = 1; i < cnt; ++i) {
        var += pow((diff[i]-mean),2);
    }
    var = var/(cnt-1);

    if (var < minvar) {
        minvar = var;
        for(int i = 0; i < F; ++i) {
            ansf[i] = feasibleF[i];
        }
        for (int j = 0; j < R; ++j) {
            ansr[j] = feasibleR[j];
        }
    }
}

void chooseR(int r, int b) {
    if (r == R) {
        check();
        return ;
    }
    if (R2-b+1 < R-r) {
        return ;
    }
    for (int i = b; i <= R2; ++i) {
        feasibleR[cntr] = i;
        cntr ++;
        chooseR(r+1, i+1);
        cntr --;
    }
}

void chooseF(int f, int b) {
    
    if (f == F) {
        chooseR(0, R1);
        return ;
    }
    if (F2-b+1 < F-f)
        return ;
    for (int i = b; i <= F2; ++i) {
        feasibleF[cntf] = i;
        cntf ++;
        chooseF(f+1, i+1);
        cntf --;
    }
}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("cowcycle.in");
    
    fin >> F >> R;
    fin >> F1 >> F2 >> R1 >> R2;
    
    fin.close();
    
    chooseF(0, F1);
    
    ofstream fout;
    fout.open("cowcycle.out");
    
    
    for (int i = 0; i < F; ++i) {
        if (i == 0) {
            fout << ansf[i];
        }
        else {
            fout << ' ' << ansf[i];
        }
    }
    fout << endl;
    
    for (int j = 0; j < R; ++j) {
        if (j == 0) {
            fout << ansr[j];
        }
        else {
            fout << ' ' << ansr[j];
        }
    }
    fout << endl;
    
    fout.close();
    
    return 0;
}

































































