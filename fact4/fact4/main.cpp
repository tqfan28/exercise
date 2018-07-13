//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: fact4
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <time.h>

using namespace std;
int N;

int count_five(int i) {
    int result = 0;
    while(i > 1 && i % 5 == 0) {
        result ++;
        i = i/5;
    }
    return result;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("fact4.in");
    fin >> N;
    
    int five = 0;
    
    for (int i = 5; i < N+1; ++i) {
        five += count_five(i);
    }
    //cout << five << endl;
    int two = five;
    int ans = 1;
    for (int i = 2; i < N+1; ++i) {
        int n = i;
        if (two > 0) {
            while(two > 0 && n > 1 && n % 2 == 0) {
                n = n/2;
                two --;
            }
        }
        if (five > 0) {
            while(five > 0 && n > 1 && n % 5 == 0) {
                n = n/5;
                five --;
            }
        }
        //cout << n << endl;
        ans = ((ans*n) % 10);
    }
    ofstream fout ("fact4.out");
    fout << ans << endl;
    fout.close();
    return 0;
}






































