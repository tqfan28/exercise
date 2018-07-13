//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: runround
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
unsigned int M;
int digits[9] = {};

// 1 2 4
// 0 1 2

int to_digits(unsigned int n) {
    
    int len = 0;
    int temp[9] = {};
    while(n > 0) {
        temp[len] = n % 10;
        n = (n - temp[len])/10;
        len ++;
    }
    for (int i = 0; i < len; ++i) {
        digits[i] = temp[len-1-i];
    }
    return len;
}

bool is_runround (int len) {
    bool visits[9] = {};
    int num = 0;
    int start = digits[0];
    int index = 0;
    while (num != len) {
        index = (index + start) % len;
        start = digits[index];
        if (!visits[index]) {
            visits[index] = true;
            num ++;
        }
        else break;
    }
    if (num == len && index == 0)
        return true;
    else
        return false;
}

bool is_unique (int len) {
    int tmp[10] = {};
    for (int i = 0; i < len; ++i) {
        if (tmp[digits[i]]!= 0) {
            return false;
        }

        else {
            tmp[digits[i]] ++;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("runround.in");
    fin >> M;

    unsigned int search = M+1;
    int len = to_digits(search);
    while(true) {
        if (is_unique(len) && is_runround(len)) {
            break;
        }
        else {
            search ++;
            len = to_digits(search);
        }
        
    }
    ofstream fout ("runround.out");
    fout << search<< endl;
    fout.close();
    
    return 0;
}


















