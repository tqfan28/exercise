//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: zerosum
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
const int MAXN = 9;
int possible[52488];


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("zerosum.in");
    fin >> N;
    // 0 black 1 + 2 -
    int i = 0;
    for (int a = 0; a < 3; ++a) {
        for (int b = 0; b < 3; ++b) {
            for (int c = 0; c < 3; ++c) {
                for (int d = 0; d < 3; ++d) {
                    for (int e = 0; e < 3; ++e) {
                        for (int f = 0; f < 3; ++f) {
                            for (int g = 0; g < 3; ++g) {
                                for (int h = 0; h < 3; ++h) {
                                    possible[i] = a;
                                    ++i;
                                    possible[i] = b;
                                    ++i;
                                    possible[i] = c;
                                    ++i;
                                    possible[i] = d;
                                    ++i;
                                    possible[i] = e;
                                    ++i;
                                    possible[i] = f;
                                    ++i;
                                    possible[i] = g;
                                    ++i;
                                    possible[i] = h;
                                    ++i;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    ofstream fout ("zerosum.out");
    
    int jump = pow(3, 9-N);
    
    for (int j = 0; j < 52488; j = j+8*jump) {
        //cout << j << endl;
        int numbers[9] = {};
        int counter = 0;
        bool ops[8];
        int left = 1;
        for (int k = 0; k < N-1; ++k) {
            if (possible[j+k] == 0) {
                left = left*10+k+2;
            }
            else {
                numbers[counter] = left;
                left = k+2;
                if (possible[j+k] == 1) {
                    ops[counter] = true;
                }
                else {
                    ops[counter] = false;
                }
                counter ++;
            }
        }
        numbers[counter] = left;
        
        int result = numbers[0];
        for (int s = 0; s < counter; ++s) {
            if (ops[s]) {
                result += numbers[s+1];
            }
            else {
                result -= numbers[s+1];
            }
        }
        
        if (result == 0) {
            for (int k = 0; k < N-1; ++k) {
                fout << k+1;
                if (possible[j+k] == 0) {
                    fout << ' ';
                }
                else if (possible[j+k] == 1) {
                    fout << '+';
                }
                else {
                    fout << '-';
                }
            }
            fout << N<< endl;
        }
    }
    
    fout.close();
    
    return 0;
}






















