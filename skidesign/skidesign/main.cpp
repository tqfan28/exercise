//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: skidesign
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;

int compute_diff(int mark, int hills []) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        if (hills[i] > mark + 17) {
            result += (hills[i] - mark - 17)*(hills[i] - mark - 17);
        }
        else if (hills[i] < mark) {
            result += (mark - hills[i])*(mark - hills[i]);
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("skidesign.in");
    fin >> N;
    int hills[N];
    for (int i = 0; i < N; ++i) {
        fin>> hills[i];
    }
    fin.close();
    
    sort(hills, hills+N);
    
    int result = 0;
    bool first = true;
    for (int mark = hills[0]; mark <= hills[N-1]; ++mark) {
        if (first) {
            result = compute_diff(mark, hills);
            first = false;
        }
        else {
            int current = compute_diff(mark, hills);
            if (result > current) {
                result = current;
            }
        }
    }
    
    ofstream fout ("skidesign.out");
    fout << result << endl;
    fout.close();
    return 0;
}







