//
//  main.cpp
//  fc
//
//  Created by TFAN on 2018/8/2.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: fc
 LANG: C++
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <math.h>
#include <iomanip>




using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 10000;

double p0x = 0;
double p0y = 0;

struct xy {
    double x;
    double y;
    
    bool operator < (const xy & rhs) const {
        return ( ((x - p0x)*(rhs.y - p0y) - (rhs.x - p0x)*(y - p0y)) >= 0);
    }
};

xy grazing [MAXN];
xy sol[MAXN];

double crossZ(xy o, xy a, xy b) {
    return (a.x - o.x)*(b.y - o.y) - (b.x - o.x)*(a.y - o.y);
}

double l2(const xy& a, const xy& b) {
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
}

void swap(int a, int b) {
    xy tmp = grazing[a];
    grazing[a] = grazing[b];
    grazing[b] = tmp;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("fc.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> grazing[i].x >> grazing[i].y;
    }
    fin.close();
    
    xy start;
    start.y = infty;
    start.x = infty;
    int index = -1;
    
    for (int i = 0; i < N; ++i) {
        if (start.x > grazing[i].x
            || (start.x == grazing[i].x && start.y > grazing[i].y)
            ) {
            index = i;
            start.x = grazing[i].x;
            start.y = grazing[i].y;
        }
    }
    swap(0, index);
    p0x = grazing[0].x;
    p0y = grazing[0].y;
    sort(grazing+1,grazing+N);
    
    sol[0] = grazing[0];
    sol[1] = grazing[1];
    int hullpos = 2;
    
    for (int i = 1; i < N-1; ++i) {
        sol[hullpos] = grazing[i+1];
        while(crossZ(sol[hullpos-2], sol[hullpos-1], sol[hullpos]) <= 0) {
            hullpos--;
            sol[hullpos] = grazing[i+1];
        }
        hullpos ++;
    }
    
    ofstream fout;
    fout.open("fc.out");
    double dist = 0;
    for (int i = 1; i < hullpos; ++i) {
        dist += l2(sol[i-1], sol[i]);
    }
    dist += l2(sol[0], sol[hullpos-1]);
    
    fout << setiosflags(ios::fixed) << setprecision(2)<< dist << endl;
    
    fout.close();
    
    return 0;
}
































