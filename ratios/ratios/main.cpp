
//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: ratios
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;
int goal[3];
int mixtures[3][3];

int det(int matrix[3][3]) {
    return matrix[0][0]*matrix[1][1]*matrix[2][2] +
    matrix[1][0]*matrix[2][1]*matrix[0][2] +
    matrix[2][0]*matrix[0][1]*matrix[1][2] -
    (matrix[2][0]*matrix[1][1]*matrix[0][2] +
     matrix[0][1]*matrix[1][0]*matrix[2][2] +
     matrix[0][0]*matrix[1][2]*matrix[2][1]);
}

int gcd (int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("ratios.in");
    fin >> goal[0] >> goal[1] >> goal[2];
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 3; ++i) {
            fin >> mixtures[i][j];
        }
    }
    
    ofstream fout ("ratios.out");
    
    int detA = det(mixtures);
    if (detA == 0) {
        fout << "NONE" << endl;
        return 0;
    }

    
    int detx[3][3];
    int dety[3][3];
    int detz[3][3];
    
    for (int i = 0; i < 3; ++i) {
        detx[i][0] = goal[i];
        detx[i][1] = mixtures[i][1];
        detx[i][2] = mixtures[i][2];
        
    }
    for (int i = 0; i < 3; ++i) {
        dety[i][1] = goal[i];
        dety[i][0] = mixtures[i][0];
        dety[i][2] = mixtures[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        detz[i][2] = goal[i];
        detz[i][1] = mixtures[i][1];
        detz[i][0] = mixtures[i][0];
    }
    int det1 = det(detx);
    int det2 = det(dety);
    int det3 = det(detz);
    
    if (detA > 0) {
        if (det1 < 0 || det2 < 0 || det3 < 0) {
            fout << "NONE" << endl;
            return 0;
        }
    }
    
    else {
        if (det1 > 0 || det2 > 0 || det3 > 0) {
            fout << "NONE" << endl;
            return 0;
        }
        else {
            detA = -detA;
            det1 = -det1;
            det2 = -det2;
            det3 = -det3;
            
        }
    }
    
    int divisor = gcd(detA, det1);
    if (divisor != 1)
        divisor = gcd(divisor, det2);
    if (divisor != 1)
        divisor = gcd(divisor, det3);
    fout << det1/divisor << ' '<< det2/divisor << ' '<< det3/divisor << ' '<< detA/divisor << endl;
    
    fout.close();
    
    return 0;
}
















