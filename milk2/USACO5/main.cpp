//
//  main.cpp
//  USACO5
//
//  Created by TFAN on 2017/9/6.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: milk2
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


struct farmer {
    int start;
    int end;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    
    int cows [1000000];
    int N = 0;
    fin >> N;
    int min = 0;
    int max = 0;
    
    for (int i = 1; i < N+1; ++i) {
        int start;
        int end;
        fin >> start >> end;
        for (int j = start; j < end; ++j) {
            cows[j] = 1;
        }
        if ( i == 1) {
            min = start;
            max = end;
        }
        else {
            if (start < min) {
                min = start;
            }
            if (max < end) {
                max = end;
            }
        }
    }
    //cout << max << ' ' << min << endl;
    
    vector<int> milk;
    vector<int> milkc;
    
    /*
    for (int i = min; i < max +1; ++i) {
        cout << cows[i];
    }
     */
    
    for (int i = min; i < max; ++i) {
        int j = i + 1;
        if (cows[i] == 1) {
            while (j < max && cows[j] == 1) {
                ++j;
            }
            //cout << j -i-1 << endl;
            milk.push_back(j -i);
        }
        else {
            while (j < max && cows[j] == 0) {
                ++j;
            }
            milkc.push_back(j -i);
        }
        i = j-1;
    }
    
    vector<int>::iterator milk_max = max_element(milk.begin(), milk.end());
    vector<int>::iterator milkc_max = max_element(milkc.begin(), milkc.end());
    
    if (milkc.size() == 0) {
        fout << (*milk_max) <<' ' << 0 << endl;
    }
    else {
        fout << (*milk_max) <<' ' << (*milkc_max) << endl;
    }
    
    //std::cout << "Hello, World!\n";
    return 0;
}
