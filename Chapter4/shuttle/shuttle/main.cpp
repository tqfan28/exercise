//
//  main.cpp
//  shuttle
//
//  Created by TFAN on 2018/7/30.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: shuttle
 LANG: C++
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>


using namespace std;
//const int infty = 0x7fffffff;
int N;
const int diff[91] = {
    -1,
    2, 1,
    -2, -2, -1,
    2, 2, 2, 1,
    -2, -2 ,-2, -2, -1,
    2, 2, 2, 2, 2, 1,
    -2, -2 ,-2, -2, -2, -2, -1,
    2, 2, 2, 2, 2, 2, 2, 1,
    -2, -2 ,-2, -2, -2, -2, -2, -2, -1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
    -2, -2 ,-2, -2, -2, -2, -2, -2, -2, -2, -1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
    -2, -2 ,-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1
};

int main(int argc, const char * argv[]) {
    


    ifstream fin;
    fin.open("shuttle.in");
    fin >> N;
    fin.close();
    int len = N*N+2*N;
    int arr[168];
    arr[0] = N+1;
    int mid = len/2;
    
    for (int i = 1; i < mid+1; ++i) {
        arr[i] = arr[i-1]+diff[i-1];
    }

    
    for (int i = mid+1; i < len+1; ++i) {
        if (len % 2 != 0)
            arr[i] = arr[i-1]+diff[2*mid-i+1];
        else
            arr[i] = arr[i-1]+diff[2*mid-i];
        
    }

    
    ofstream fout;
    fout.open("shuttle.out");
    int counter = 0;
    for (int i = 1; i < len+1; ++i) {
        if (i == len || counter == 19) {
            fout << arr[i] << endl;
            counter = 0;
        }
        else {
            fout << arr[i] << ' ';
            counter++;
        }
        
    }
    fout.close();
    
    return 0;
}
































