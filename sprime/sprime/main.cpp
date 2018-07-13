//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: sprime
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int N;
int result[8][100] = {};
int possible[4] = {1, 3, 7, 9};


int getLength(int a) {
    int Length = 1;
    while(a > 9) {
        Length ++;
        a /= 10;
    }
    return Length;
}

int Exp(int i) {
    if (i == 0)
        return 1;
    else
        return 10*Exp(i-1);
}



bool check_prime(int n) {
    //cout << n << endl;
    if (n == 1)
        return false;
    if (n == 2) {
        return true;
    }
    else if (n == 3) {
        return true;
    }
    else if (n % 2 == 0)
        return false;
    else if (n % 3 == 0)
        return false;
    int i = 5;
    int w = 2;
    while (i* i <= n) {
        if (n % i == 0)
            return false;
        i += w;
        w = 6 - w;
    }
    return true;
}

int sprime(int N) {
    int length = 0;
    if(N == 0) {
        result[N][0] = 2;
        result[N][1] = 3;
        result[N][2] = 5;
        result[N][3] = 7;
        length = 4;
    }
    else {
        int pre_length = sprime(N -1);
        for (int i = 0; i < pre_length; i++) {
            for (int j = 0; j < 4; j++) {
                int tmp = 10*result[N-1][i] + possible[j];
                if (check_prime(tmp) ) {
                    //cout << N << " " << tmp << endl;
                    result[N][length] = tmp;
                    length ++;
                }
            }
        }
    }
    return length;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("sprime.in");
    fin >> N;
    
    int length = sprime(N-1);
    sort(result[N-1], result[N-1]+length);
    
    ofstream fout ("sprime.out");
    for (int i = 0; i < length; ++i) {
        fout << result[N-1][i] << endl;
    }
    fout.close();
    
    return 0;
}










