//
//  main.cpp
//  rectbarn
//
//  Created by TFAN on 2018/8/20.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: rectbarn
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
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
int R;
int C;
int P;
const int MAX = 3000;
bool occ[MAX+1][MAX+1] = {};
int up[MAX+1] = {};
int Left[MAX+1] = {};
int Right[MAX+1] = {};


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("rectbarn.in");
    
    fin >> R >> C >> P;
    for (int i = 0; i < P; ++i) {
        int y, x;
        fin >> y >> x;
        occ[y][x] = true;
    }
    
    fin.close();
    
    int sol = 0;
    
    for (int i = 1; i <= R; ++i) {
        int l = 0;
        int r = 0;
        
        for (int j = 1; j <= C; ++j) {
            if (!occ[i][j]) {
                up[j]++;
            }
            else {
                up[j] = 0;
            }
        }
        
        for (int j = 1; j <= C; ++j) {
            
            if (!occ[i][j]) {
                l++;
                if (Left[j] == 0)
                    Left[j] = l;
                else {
                    Left[j] = min(Left[j], l);
                }
            }
            else {
                Left[j] = 0;
                l = 0;
            }
        }
        
        for (int j = C; j >= 1; --j) {
            
            if (!occ[i][j]) {
                r++;
                if (Right[j] == 0)
                    Right[j] = r;
                else
                    Right[j] = min(Right[j], r);
            }
            else {
                Right[j] = 0;
                r = 0;
            }
        }
        
        for (int j = 1; j <= C; ++j) {
            int tmp = up[j]*(Left[j]+Right[j]-1);
            if (sol < tmp) {
                sol = tmp;
            }
        }
        
//        for (int j = 1; j <= C; ++j) {
//            cout << Right[j] << ' ';
//        }
//        cout << endl;
    }
    
    ofstream fout;
    fout.open("rectbarn.out");
    
    fout << sol << endl;
    
    fout.close();
    
    return 0;
}




























































