//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: palsquare
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

int digitsToNum(vector<int> digits) {
    int number = 0;
    for (int i = 0; i < digits.size(); ++i) {
        number = number*10 + digits[digits.size() -i-1];
    }
    return number;
}

void print_digits(vector<char> digits, ofstream & fout) {
    for (int i = 0; i < digits.size(); ++i) {
        cout << digits[digits.size() -i -1];
    }
}

int main(int argc, const char * argv[]) {
    
    //ofstream fout ("palsquare.out");
    //ifstream fin ("palsquare.in");
    
    int base;
    int N = 300;
    cin >> base;
    
    
    for (int i = 1; i < N+1; ++i) {
        vector<char> result = numToDigits(i*i, base);        
        if (isPalsquare(result)) {
            print_digits(numToDigits(i, base), fout);
            cout << ' ';
            print_digits(result, fout);
            cout << endl;
        }
    }
    //std::cout << "Hello, World!\n";
    return 0;
}
