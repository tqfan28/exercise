//
//  main.cpp
//  fence8
//
//  Created by TFAN on 2018/9/24.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: fence8
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
//#include <string>
//#include <stdio.h>
//#include <ctype.h>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
int N;
int minN = 1;
const int MAXN = 50;
int R;
const int MAXR = 1023;
int boards[MAXN+1] = {};
int rails[MAXR+1] = {};

int empt;
int dead_space = 0;

bool dls(int r, int b) {

    if (dead_space > empt || empt < 0)
        return false;
    if (r < 1)
        return true;
    
    bool tmp = false;
    for (int i = b; i < N+1; ++i) {
        if (boards[i] >= rails[r]) {
            boards[i] -= rails[r];
            bool happen = false;
            if (boards[i] < rails[1]) {
                dead_space += boards[i];
                happen = true;
            }
            if (r > 1 && rails[r-1] == rails[r]) {
                tmp = dls(r-1, i);
            }
            else {
                tmp = dls(r-1, minN);
            }
            if (happen) {
                dead_space -= boards[i];
            }
            boards[i] += rails[r];
        }
        if (tmp)
            return tmp;
    }
    
    return false;
}


int main(int argc, const char * argv[]) {
    
    int total_space = 0;
    ifstream fin;
    fin.open("fence8.in");
    
    fin >> N;
    for (int i = 1; i < N+1; ++i) {
        fin >> boards[i];
        total_space += boards[i];
    }
    fin >> R;
    for (int i = 1; i < R+1; ++i) {
        fin >> rails[i];
    }
    
    fin.close();
    
    sort(rails+1, rails+R+1);
    sort(boards+1, boards+N+1);
    
    for (int i = R; i > 0; --i) {
        if (rails[i] > boards[N]) {
            R--;
        }
    }
    
    for (int i = 1; i < N+1; ++i) {
        if (rails[1] > boards[i]) {
            minN++;
        }
    }
    
    int railsum[MAXR+1] = {};
    for (int i = 1; i < R+1; ++i) {
        railsum[i] = railsum[i-1] + rails[i];
    }
    
    int ans = 0;
    
    int l = 1;
    int r = R;
    int mid = (l+r)/2;
    
    while(l <= r) {
        mid = (l+r)/2;
        empt = total_space - railsum[mid];
        dead_space = 0;
        if (dls(mid, minN)) {
            l = mid+1;
            ans = max(mid, ans);
        }
        else {
            r = mid-1;
        }
    }
    
//    for (int i = 1; i < R+1; ++i) {
//        empt = total_space - railsum[i];
//        dead_space = 0;
//        if (dls(i, minN)) {
//            ans = max(ans, i);
//        }
//        else {
//            break;
//        }
//    }
    
    ofstream fout;
    fout.open("fence8.out");
    
    fout << ans << endl;
    
    fout.close();
    
    return 0;
}






























































