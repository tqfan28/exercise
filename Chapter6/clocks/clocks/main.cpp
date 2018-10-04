//
//  main.cpp
//  clocks
//
//  Created by TFAN on 2018/10/3.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: clocks
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
//#include <algorithm>
//#include <math.h>
//#include <iomanip>

using namespace std;
int board1[10] = {};
int board2[10] = {};
int moves[9][6] = {};

void init() {
    moves[0][0] = 4;
    moves[0][1] = 1;
    moves[0][2] = 2;
    moves[0][3] = 4;
    moves[0][4] = 5;
    
    moves[1][0] = 3;
    moves[1][1] = 1;
    moves[1][2] = 2;
    moves[1][3] = 3;
    
    moves[2][0] = 4;
    moves[2][1] = 2;
    moves[2][2] = 3;
    moves[2][3] = 5;
    moves[2][4] = 6;
    
    moves[3][0] = 3;
    moves[3][1] = 1;
    moves[3][2] = 4;
    moves[3][3] = 7;
    
    moves[4][0] = 5;
    moves[4][1] = 2;
    moves[4][2] = 4;
    moves[4][3] = 5;
    moves[4][4] = 6;
    moves[4][5] = 8;
    
    moves[5][0] = 3;
    moves[5][1] = 3;
    moves[5][2] = 6;
    moves[5][3] = 9;
    
    moves[6][0] = 4;
    moves[6][1] = 4;
    moves[6][2] = 5;
    moves[6][3] = 7;
    moves[6][4] = 8;
    
    moves[7][0] = 3;
    moves[7][1] = 7;
    moves[7][2] = 8;
    moves[7][3] = 9;
    
    moves[8][0] = 4;
    moves[8][1] = 5;
    moves[8][2] = 6;
    moves[8][3] = 8;
    moves[8][4] = 9;

}

void reset() {
    for (int i = 1; i <= 9; ++i) {
        board2[i] = board1[i];
    }
}

int possible[9] = {};
int ans[9] = {};
int total = 9999999;

void move(int id) {
    for (int i = 1; i <= moves[id][0]; ++i) {
        board2[moves[id][i]] += 3;
        board2[moves[id][i]] = board2[moves[id][i]] % 12;
    }
}

bool check() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < possible[i]; ++j) {
            move(i);
        }
    }
    
    for (int i = 1; i <= 9; ++i) {
        if (board2[i] != 0) {
            return false;
        }
    }
    
    return true;
}

void pset(int depth) {
    if (depth == 9) {
        if (check()) {
            int steps = 0;
            for (int i = 0; i < 9; ++i) {
                steps += possible[i];
            }
            if (total > steps) {
                total = steps;
                for (int i = 0; i < 9; ++i) {
                    ans[i] = possible[i];
                }
            }
        }
        
        reset();
        return ;
    }
    for (int i = 0; i < 4; ++i) {
        possible[depth] = i;
        pset(depth+1);
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("clocks.in");
    
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            fin >> board1[j + 3*(i-1)];
            board1[j + 3*(i-1)] = board1[j + 3*(i-1)] % 12;
        }
    }
    
    fin.close();
    
    init();
    reset();
    pset(0);
    
    ofstream fout;
    fout.open("clocks.out");
    
    int cnt = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < ans[i]; ++j) {
            if (cnt == 0) {
                fout << i+1;
                cnt ++;
            }
            else {
                fout << ' ' << i+1;
            }
        }
    }
    fout << endl;
    
    fout.close();
    
    return 0;
}





































































