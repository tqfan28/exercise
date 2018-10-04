//
//  main.cpp
//  rect1
//
//  Created by TFAN on 2018/9/24.
//  Copyright © 2018年 TFAN. All rights reserved.
//




/*
 ID: tfan0328
 PROG: rect1
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
//#include <math.h>
//#include <iomanip>



using namespace std;
const int infty = 0x7fffffff;
int N;
int A;
int B;

struct rectangle {
    int y1;
    int x1;
    int y2;
    int x2;
    int color;
};

rectangle pictures[1002];
int ans[2502] = {};

int area (rectangle w, int level) {
    if (w.y1 >= w.y2 || w.x1 >= w.x2) {
        return 0;
    }
    for (int i = level; i < N+1; ++i) {
        if (!
            (w.y2 <= pictures[i].y1 || pictures[i].y2 <= w.y1
             || w.x2 <= pictures[i].x1 || pictures[i].x2 <= w.x1)) {
                rectangle  a;
                a.y1 = w.y1;
                a.x1 = w.x1;
                a.y2 = w.y2;
                a.x2 = pictures[i].x1;
                
                rectangle  b;
                b.y1 = w.y1;
                b.x1 = pictures[i].x2;
                b.y2 = w.y2;
                b.x2 = w.x2;
                
                rectangle  c;
                c.y1 = w.y1;
                c.x1 = max (w.x1, pictures[i].x1);
                c.y2 = pictures[i].y1;
                c.x2 = min (pictures[i].x2, w.x2);
                
                rectangle  d;
                d.y1 = pictures[i].y2;
                d.x1 = max (w.x1, pictures[i].x1);
                d.y2 = w.y2;
                d.x2 = min (pictures[i].x2, w.x2);
                return area(a, i+1)+ area (b, i+1) + area (c, i+1) + area (d, i+1);
            }
    }
    return ((w.y2 - w.y1) * (w.x2 - w.x1));
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("rect1.in");
    
    fin >> A >> B >> N;
    pictures[0].x1 = 0;
    pictures[0].y1 = 0;
    pictures[0].x2 = A;
    pictures[0].y2 = B;
    pictures[0].color = 1;
    
    for (int i = 1; i < N+1; ++i) {
        fin >> pictures[i].x1 >> pictures[i].y1 >> pictures[i].x2 >> pictures[i].y2 >> pictures[i].color;
    }
    
    fin.close();
    
    for (int i = 0; i < N+1; ++i) {
        ans[pictures[i].color] += area(pictures[i], i+1);
    }
    
    ofstream fout;
    fout.open("rect1.out");
    
    for (int i = 1; i < 2052; ++i) {
        if (ans[i] != 0) {
            fout << i << ' ' << ans[i] << endl;
        }
    }
    
    fout.close();
    
    return 0;
}





























































