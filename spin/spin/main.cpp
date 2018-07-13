
//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: spin
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct wedge {
    int start;
    int end;
};

struct wheel {
    int speed;
    int number;
    wedge wedges[5];
};

wheel wheels[5];

bool config[5][360] = {};

int gcd (int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd (b, a % b);
}

int lcm (int a, int b) {
    return a*b/gcd(a, b);
}

void configuration(int i, int n) {
    for (int j = 0; j < wheels[i].number; ++j) {
        int start = (wheels[i].wedges[j].start + n*wheels[i].speed) % 360 ;
        int length = wheels[i].wedges[j].end;
        //cout << i << ' '<< start << " "<< start+length << endl;
        for (int k = 0; k < length+1; ++k) {
            config[i][(start + k) % 360] = true;
        }
    }
}

bool align() {
    for (int j = 0; j < 360; ++j) {
        bool did_break = false;
        for (int i = 0; i < 5; ++i) {
            if (!config[i][j]) {
                did_break = true;
                break;
            }
        }
        if (!did_break) {
             return true;
        }
    }
    return false;
}

void reset() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 360; ++j) {
            config[i][j] = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("spin.in");
    for (int i = 0; i < 5; ++i) {
        fin >> wheels[i].speed >> wheels[i].number;
        for (int j = 0; j < wheels[i].number; ++j) {
            fin >> wheels[i].wedges[j].start >> wheels[i].wedges[j].end;
        }
    }

    
    int periods[5];
    for (int i = 0; i < 5; ++i) {
        periods[i] = 360/gcd(360, wheels[i].speed);
    }
    
    int period = periods[0];
    for (int i = 1; i < 5; ++i) {
        period = lcm(period, periods[i]);
    }
    
    ofstream fout ("spin.out");
    
    for (int n = 0; n < period; ++n) {
        reset();
        for (int i = 0; i < 5; ++i) {
            configuration(i, n);
        }
        if (align()) {
            fout << n << endl;
            return 0;
        }
    }
    fout << "none" << endl;
    
    fout.close();
    
    return 0;
}















