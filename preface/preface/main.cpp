//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: preface
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
const int MAXN = 3500;

struct romandata_t {
    int value;
    char const* numeral;
};

int main(int argc, const char * argv[]) {
    
    ifstream fin ("preface.in");
    fin >> N;
    // I V X L C D M
    // 0 1 2 3 4 5 6
    int result[MAXN][7] = {};
    
    static romandata_t const romandata[] = {
        1000, "M",
        900, "CM",
        500, "D",
        400, "CD",
        100, "C",
        90, "XC",
        50, "L",
        40, "XL",
        10, "X",
        9, "IX",
        5, "V",
        4, "IV",
        1, "I",
        0, NULL
    };
    
//    string test;
//    int value = N;
    
//    for (romandata_t const* current = romandata; current->value > 0; ++current) {
//        while (value >= current->value) {
//            test += current->numeral;
//            value  -= current->value;
//        }
//    }
//    cout << test;

    
    for (int i = 1; i < N+1; ++i) {
        int value = i;
        int counter = 0;
        for (romandata_t const* current = romandata; current->value > 0; ++current) {
            if (value >= current->value) {
                if (counter == 0) {
                    result[i][6] ++;
                }
                else if (counter == 1) {
                    result[i][6] ++;
                    result[i][4] ++;
                }
                else if (counter == 2) {
                    result[i][5] ++;
                }
                else if (counter == 3) {
                    result[i][5] ++;
                    result[i][4] ++;
                }
                else if (counter == 4) {
                    result[i][4] ++;
                }
                else if (counter == 5) {
                    result[i][2] ++;
                    result[i][4] ++;
                }
                else if (counter == 6) {
                    result[i][3] ++;
                }
                else if (counter == 7) {
                    result[i][3] ++;
                    result[i][2] ++;
                }
                else if (counter == 8) {
                    result[i][2] ++;
                }
                else if (counter == 9) {
                    result[i][0] ++;
                    result[i][2] ++;
                }
                else if (counter == 10) {
                    result[i][1] ++;
                }
                else if (counter == 11) {
                    result[i][0] ++;
                    result[i][1] ++;
                }
                else if (counter == 12) {
                    result[i][0] ++;
                }
                value -= current->value;
                for (int j = 0; j < 7; ++j) {
                    result[i][j] += result[value][j];
                }
                break;
            }
            counter ++;
        }
    }

    ofstream fout ("preface.out");
    for (int i = 0; i < 7; ++i) {
        int current = 0;
        for (int j = 1; j < N+1; ++j) {
            current += result[j][i];
        }
        if (current != 0) {
            if (i == 0)
                fout << 'I' << ' ' << current << endl;
            else if (i == 1)
                fout << 'V' << ' ' << current << endl;
            else if (i == 2)
                fout << 'X' << ' ' << current << endl;
            else if (i == 3)
                fout << 'L' << ' ' << current << endl;
            else if (i == 4)
                fout << 'C' << ' ' << current << endl;
            else if (i == 5)
                fout << 'D' << ' ' << current << endl;
            else if (i == 6)
                fout << 'M' << ' ' << current << endl;
        }
        
    }
    fout.close();
    
    return 0;
}
















