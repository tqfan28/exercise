//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: dualpal
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> numToDigits(int number, int base) {
    vector<char> digits;
    while(number != 0) {
        int digit = number % base;
        if (digit > 9) {
            digits.push_back(65 + digit - 10);
        }
        else {
            digits.push_back('0' + digit);
        }
        number = (number - (number % base))/base;
    }
    return digits;
}

bool isPalsquare(vector<char> digits) {
    for (int i = 0; i < digits.size(); ++i) {
        if (digits[i] != digits[digits.size() -i-1]) {
            return false;
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");
    
    int N;
    int S;
    fin >> N >> S;
    
    int count = 0;
    int start = S+1;
    while(count < N) {
        int ways = 0;
        int base = 2;
        while(ways < 2 && base < 11) {
            if (isPalsquare(numToDigits(start, base))) {
                ++ways;
            }
            ++base;
        }
        if (ways > 1) {
            fout << start <<endl;
            ++count;
        }
        ++start;
    }
    //std::cout << "Hello, World!\n";
    return 0;
}

