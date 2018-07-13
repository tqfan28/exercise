//
//  main.cpp
//  USACO3
//
//  Created by TFAN on 2017/8/12.
//  Copyright © 2017年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: friday
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// compute a given date is Monday or Tuesday or ... in a given month
// 0--Monday
int Day(int start, int date) {
    return (((date -1) % 7) + start)%7;
}

void compute(int (&result)[7], int& next, int leap) {
    for (int j = 1; j < 13; ++j) {
        //cout << next << endl;
        if (j == 4 || j == 6 || j == 9 || j == 11) {
            result[Day(next,13)] += 1;
            next = (Day(next, 30) + 1) % 7;
        }
        else if (j == 2) {
            result[Day(next,13)] += 1;
            next = (Day(next, leap) + 1) % 7;
        }
        else {
            result[Day(next,13)] += 1;
            next = (Day(next, 31) + 1) % 7;
        }
    }
}

int main(int argc, const char * argv[]) {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
    //cout << "Hello"<< endl;
    
    int n;
    int result [7] = {0, 0, 0, 0, 0, 0, 0};
    fin >> n;

    int next = 0;
    
    for (int i = 0; i < n; ++i) {
        // leap year
        if ( ((1900 + i) % 100 != 0 && (1900 + i) % 4 == 0) || ((1900 + i) % 100 == 0 && (1900 + i) % 400 == 0)) {
            //cout << 1900+i << endl;
            compute(result, next, 29);
        }
        else {
            compute(result, next, 28);
        }
    }
    
    for (int i = 0; i < 7; ++i) {
        if (i != 6) {
            fout << result[((i+5)%7)] << ' ';
        }
        else {
            fout << result[((i+5)%7)] << '\n';
        }
    }
    
    return 0;
}
