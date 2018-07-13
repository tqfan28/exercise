//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: sort3
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
const int MAX = 1000;
int Array[MAX] = {};

void flip(int i, int j) {
    int k = Array[i];
    Array[i] = Array[j];
    Array[j] = k;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("sort3.in");
    
    fin >> N;
    int one = 0;
    int two = 0;
    int flips = 0;
    
    for (int i = 0; i < N; ++i) {
        fin >> Array[i];
        if (Array[i] == 1) {
            one++;
        }
        else if (Array[i] == 2) {
            two++;
        }
    }
    bool fliped = false;

    for (int i = one; i < N; ++i) {
        if (Array[i] == 1) {
            // 1 is in two-slot
            fliped = false;
            if (i < one + two) {
                for (int j = 0; j < one; ++j) {
                    if (Array[j] == 2) {
                        flip(i, j);
                        flips++;
                        fliped = true;
                        break;
                    }
                }
                // no 2 in one-slot, so there must be a 2 in three-slot
                if (!fliped) {
                    for (int j = one + two; j < N; ++j) {
                        if (Array[j] == 2) {
                            flip(i, j);
                            flips++;
                            break;
                        }
                    }
                }
            }
            // 1 is in three-slot, and no 1 is in two-slot
            else {
                for (int j = 0; j < one; ++j) {
                    if (Array[j] != 1) {
                        flip(i, j);
                        flips++;
                        break;
                    }
                }
            }
        }
    }
    
//    for (int i = 0; i < N; ++i) {
//        cout << "test1" << Array[i] << endl;
//    }
    
    for (int i = one + two; i < N; ++i) {
        if (Array[i] == 2) {
            for (int j = one; j < one + two; ++j) {
                if (Array[j] == 3) {
                    flip(i, j);
                    flips ++;
                    break;
                }
            }
        }
    }

//    for (int i = 0; i < N; ++i) {
//        cout << "test2" << Array[i] << endl;
//    }
//

    
    ofstream fout ("sort3.out");
    fout << flips << endl;
    fout.close();
    
    return 0;
}













