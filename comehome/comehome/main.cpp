//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: comehome
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

using namespace std;
int P;
int edges[52][52] = {};
int dist[52][52] = {};

// A B ... Z
// 0 1 ... 25
// a b ... z
// 26 27 ... 51

int findindex(int c) {
    if (c <= 91) {
        return c-65;
    }
    else {
        return c-97+26;
    }
}



int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("comehome.in");

    
    fin >> P;
    char c1;
    char c2;
    int d;
    
    for (int i = 0; i < 52; ++i) {
        for (int j = 0; j < 52; ++j) {
            if (i == j)
                edges[i][i] = 0;
            else
                edges[i][j] = 999999;
        }
        
    }
    
    for (int i = 0; i < P; ++i) {
        fin >> c1 >> c2;
        int a1 = findindex(int(c1));
        int a2 = findindex(int(c2));
        fin >> d;
        edges[a1][a2] = min(d, edges[a1][a2]);
        edges[a2][a1] = edges[a1][a2];
        //cout << a1 <<' ' << a2 << ' ' << edges[a1][a2]<< endl;
    }
    
//    for (int i = 0; i < 52; ++i) {
//        for (int j = 0; j < 52; ++j) {
//            cout << edges[i][j]<< ' ';
//        }
//        cout << endl;
//    }
    
    
    for (int i = 0; i < 52; ++i) {
        for (int j = 0; j < 52; ++j) {
            dist[i][j] = edges[i][j];
        }
    }
    
    for (int k = 0; k < 52; ++k) {
        for (int i = 0; i < 52; ++i) {
            for (int j = 0; j < 52; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    int shortest = 999999;
    int index;
    for (int i = 0; i < 25; ++i) {
        if (dist[25][i] < shortest) {
            shortest = dist[25][i];
            index = i;
        }
    }
    
    char cow = index+65;
    ofstream fout ("comehome.out");
    fout << cow << ' ' << shortest << endl;
    
    fout.close();
    
    return 0;
}





























