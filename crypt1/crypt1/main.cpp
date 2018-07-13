//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: crypt1
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool valid (int * digits, int N, int num){
    while  (num != 0) {
        int digit = num % 10;
        if ( find (digits, digits + N, digit) == digits + N)
            return false;
        num = (num - digit)/10;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");
    
    int N;
    fin >> N;
    
    int digits [N];
    for (int i = 0; i < N; ++i) {
        fin >> digits[i];
    }
    
    int result = 0;
    
    for (int a = 0; a < N; ++a) {
        for (int b = 0; b < N; ++b) {
            for (int c = 0; c < N; ++c) {
                for (int d = 0; d < N; ++d) {
                    for (int e = 0; e < N; ++e) {
                        int first = (digits[a]*100 + digits[b]*10 + digits[c])*digits[d];
                        int second = (digits[a]*100 + digits[b]*10 + digits[c])*digits[e];
                        int last = first*10 + second;
                        if (first < 1000 && second < 1000 && last < 10000 && valid(digits, N, first) && valid(digits, N, second) && valid(digits, N, last)) {
                            ++result;
                            //cout << last << endl;
                        }
                    }
                }
            }
        }
    }
    
    fout << result << endl;
    //std::cout << "Hello, World!\n";
    return 0;
}




