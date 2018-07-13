//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: combo
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int LCS(int * as, int * bs, int length) {
    int c [length+1][length+1];
    for (int i = 1; i < length+1; ++i) {
        c[i][0] = 0;
    }
    for (int j = 0; j < length+1; ++j) {
        c[0][j] = 0;
    }
    for (int i = 1; i < length + 1; ++i) {
        for (int j = 1; j < length + 1; ++j) {
            if (as[i-1] == bs[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
            }
            else {
                c[i][j] = c[i][j-1];
            }
        }
    }
    return c[length][length];
}

int five_intersection(int a, int b, int N) {
    if (N < 5)
        return N;
    else {
        int as [5];
        int bs [5];
        for (int i = 0; i < 5; ++i) {
            as[i] = (a + i - 2 + N) % N;
            bs[i] = (b + i - 2 + N) % N;
        }
        return LCS(as, bs, 5);
    }
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");
    
    int N;
    fin >> N;
    
    int farmer [3];
    int master [3];
    for (int i = 0; i < 3; ++i) {
        fin >> farmer[i];
    }
    for (int i = 0; i < 3; ++i) {
        fin >> master[i];
    }
    
    int a = five_intersection(farmer[0], master[0], N);
    int b = five_intersection(farmer[1], master[1], N);
    int c = five_intersection(farmer[2], master[2], N);
    
    int total;
    if (N < 5) {
        total = N*N*N;
    }
    else {
        total = 125;
    }
    
    fout << total*2 - a*b*c << endl;
    //std::cout << "Hello, World!\n";

    
    return 0;
}





