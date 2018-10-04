//
//  main.cpp
//  fence3
//
//  Created by TFAN on 2018/9/28.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: fence3
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
#include <math.h>
#include <iomanip>

using namespace std;
ofstream fout;

int F;
const int MAXF = 151;
int fences[MAXF][4];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
double ans = 999999;
int x = 0;
int y = 0;


double total_dist(int x, int y) {
    double result = 0.0;
    for (int i = 0; i < F; ++i) {
        if (fences[i][1] == fences[i][3]) {
            int xmin = min(fences[i][0], fences[i][2]);
            int xmax = max(fences[i][0], fences[i][2]);
            if (x >= xmin && x <= xmax) {
                result += abs(y - fences[i][1]);
            }
            else if (x < xmin) {
                result += sqrt( pow(x - xmin, 2) + pow(y - fences[i][1], 2));
            }
            else {
                result += sqrt( pow(x - xmax, 2) + pow(y - fences[i][1], 2));
            }
        }
        else {
            int ymin = min(fences[i][1], fences[i][3]);
            int ymax = max(fences[i][1], fences[i][3]);
            if (y >= ymin && y <= ymax) {
                result += abs(x - fences[i][0]);
            }
            else if (y < ymin) {
                result += sqrt( pow(x - fences[i][0], 2) + pow(y - ymin, 2));
            }
            else {
                result += sqrt( pow(x - fences[i][0], 2) + pow(y - ymax, 2));
            }
        }
    }
    return result;
}

void SA() {
    int T = 40;
    int itrs = 200;
    x = fences[0][0];
    y = fences[0][1];
    ans = total_dist(x, y);
    
    while(T--) {
        for (int i = 0; i < itrs; ++i) {
            for (int j = 0; j < 4; ++j) {
                int d = rand() % 5;
                int cur_x = x + dx[j]*d*T;
                int cur_y = y + dy[j]*d*T;
                if (cur_x >= 0 && cur_x <= 1000 && cur_y >= 0 && cur_y <= 1000) {
                    double dist = total_dist(cur_x, cur_y);
                    if (dist < ans) {
                        ans = dist;
                        x = cur_x;
                        y = cur_y;
                    }
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("fence3.in");
    
    fin >> F;
    for (int i = 0; i < F; ++i) {
        fin >> fences[i][0] >> fences[i][1] >> fences[i][2] >> fences[i][3];
        for (int j = 0; j < 4; ++j) {
            fences[i][j] *= 10;
        }
    }
    
    fin.close();
    
    SA();
    
    fout.open("fence3.out");
    
    fout << setprecision(1) << fixed << double(x)/10 << ' '<< double(y)/10 << ' '<< ans/10 << endl;
    
    fout.close();
    
    return 0;
}



































































