//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: concom
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>


using namespace std;
int N;
const int n = 100;
int shares[101][101] = {};
int percentage[101] =  {};
bool owned[101] = {};

void reach(int i) {
    if (owned[i])
        return;
    owned[i] = true;
    for (int j = 1; j < n+1; ++j) {
        percentage[j] += shares[i][j];
    }
    for (int j = 1; j < n+1; ++j) {
        if (percentage[j] > 50) {
            reach(j);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("concom.in");
    fin >> N;
    
    for (int i = 0; i < N; ++i) {
        int a;
        int b;
        fin >> a >> b;
        fin >> shares[a][b];
    }
    bool found = false;
    
    ofstream fout ("concom.out");
    
    for (int i = 1; i < n+1; ++i) {
        percentage[i] = 100;
        reach(i);
        for (int j = 1; j < n+1; ++j) {
            if (owned[j] && j!=i) {
                found = true;
                fout << i << ' ' << j << endl;
            }
        }
        memset(percentage, 0, sizeof(percentage));
        memset(owned, 0, sizeof(owned));
    }
    
    if (!found)
        fout << 0 << endl;
    
    fout.close();
    
    return 0;
}
























