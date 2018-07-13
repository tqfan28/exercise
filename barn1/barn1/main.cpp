//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: barn1
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare (int a, int b) {
    return (a > b);
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    
    int M;
    int S;
    int C;
    fin >> M >> S >> C;
    
    int stalls [S];
    int index;
    
    for (int i = 0; i < S; ++i) {
        stalls[i] = 0;
    }
    
    int begin = S-1;
    int end = 0;
    
    for (int i = 0; i < C; ++i) {
        fin >> index;
        stalls[index-1] = 1;
        if (index-1 < begin) {
            begin = index-1;
        }
        if (index -1 > end) {
            end = index -1;
        }
    }
    //cout << begin<<endl;
    //cout << end << endl;
    
    vector<int> empty;
    int i = begin;
    while (i < end) {
        while (stalls[i] == 1) {
            ++i;
        }
        if (i < end) {
            int j = i;
            while (stalls[j] == 0) {
                ++j;
            }
            empty.push_back(j-i);
            i = j;
        }
    }
    
    sort( empty.begin(), empty.end(), compare);
    
    int result = end - begin + 1;
    for (int j = 0; j < M-1; ++j) {
        if (j < empty.size()){
            result -= empty[j];
        }
    }
    
    fout << result << endl;
    //std::cout << "Hello, World!\n";
    return 0;
}



