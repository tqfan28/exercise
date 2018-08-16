//
//  main.cpp
//  hidden_v2
//
//  Created by TFAN on 2018/8/15.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: hidden
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
int L;
int dL;


const int MAXL = 100000*2+1;
char input[MAXL];
int Prev[MAXL] = {};
int Next[MAXL] = {};
int head = 0;

int dp[MAXL] = {};

//dp[i]=k means input[i...i+k-1] is the smallest subsequence of length k

void init() {
    for (int i = 0; i < dL; ++i) {
        Prev[i] = i-1;
        Next[i] = i+1;
    }
    Next[dL-1] = -1;
}

void dlt(int val) {
    if (head == val) {
        head = Next[val];
    }
    if (Next[val] != -1) {
        Prev[Next[val]] = Prev[val];
    }
    if (Prev[val] != -1) {
        Next[Prev[val]] = Next[val];
    }
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("hidden.in");
    
    fin >> L;
    dL = L*2;
    
    for (int i = 0; i < L; ++i) {
        fin >> input[i];
        input[L+i] = input[i];
    }
    
    
    fin.close();
    
    init();
    
    bool change = true;
    
    
    while(change) {
        change = false;
        char minchar = '{';
        
        for (int i = head; i != -1; i = Next[i]) {
            if (input[i+dp[i]] < minchar) {
                minchar = input[i+dp[i]];
            }
        }
        
        for (int i = head; i != -1; i = Next[i]) {
            if (i+dp[i] < dL) {
                
                if ( dp[i+dp[i]] > 0) {
                    dlt(i+dp[i]);
                    dp[i] += dp[i+dp[i]];
                    change = true;
                }
                else if ( minchar == input[i+dp[i]]) {
                    dp[i] ++;
                    change = true;
                }
            }
            
        }
        
        int maxdp = -1;
        for (int i = head; i != -1; i = Next[i]) {
            if (dp[i] > maxdp) {
                maxdp = dp[i];
            }
        }
        
        for (int i = head; i != -1; i = Next[i]) {
            if (dp[i] < maxdp) {
                dlt(i);
            }
        }
        if (maxdp >= L)
            break;
    }
    
    
    ofstream fout;
    fout.open("hidden.out");
    
    fout << head << endl;
    
    fout.close();
    
    return 0;
}























































