//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: ttwo
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>


using namespace std;
int N;
const int n = 10;
bool board[n][n];
bool config[n][n][4][n][n][4] = {};

void move(int& x, int& y, int& orientation) {
    if (orientation == 0) {
        // want to move up but facing the top wall
        if (x == 0) {
            orientation ++;
        }
        else {
            if (board[x-1][y]) {
                x = x-1;
            }
            else {
                orientation++;
            }
        }
    }
    else if (orientation == 1) {
        // want to move right but facing the rightmost wall
        if (y == 9) {
            orientation ++;
        }
        else {
            if (board[x][y+1]) {
                y = y+1;
            }
            else {
                orientation++;
            }
        }
    }
    else if (orientation == 2) {
        // want to move down but facing the bottom wall
        if (x == 9) {
            orientation ++;
        }
        else {
            if (board[x+1][y]) {
                x = x+1;
            }
            else {
                orientation++;
            }
        }
    }
    else {
        // want to move left but facing the leftmost wall
        if (y == 0) {
            orientation = 0;
        }
        else {
            if (board[x][y-1]) {
                y = y-1;
            }
            else {
                orientation = 0;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("ttwo.in");
    int Fx;
    int Fy;
    int F = 0;
    int Cx;
    int Cy;
    int C = 0;
    char tmp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >>tmp;
            if (tmp =='*') {
                board[i][j] = false;
            }
            else {
                board[i][j] = true;
                if (tmp == 'F') {
                    Fx = i;
                    Fy = j;
                }
                else if (tmp == 'C') {
                    Cx = i;
                    Cy = j;
                }
            }
        }
    }
    
    
    // up 0 right 1 down 2 left 3
    int mins = 0;
    bool did_break = false;
    
    while(!config[Fx][Fy][F][Cx][Cy][C]) {
        config[Fx][Fy][F][Cx][Cy][C] = true;
        move(Fx, Fy, F);
        //cout << Fx << ' '<< Fy << ' ' << F << endl;
        move(Cx, Cy, C);
        //cout << Cx << ' '<< Cy << ' ' << C << endl;
        mins ++;
        if (Fx == Cx && Fy == Cy) {
            did_break = true;
            break;
        }
    }
    
    ofstream fout ("ttwo.out");
    if (did_break)
        fout << mins << endl;
    else
        fout << 0 << endl;
 
    fout.close();
    
    return 0;
}

























