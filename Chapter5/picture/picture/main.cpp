//
//  main.cpp
//  picture
//
//  Created by TFAN on 2018/8/13.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: picture
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
const int MAXN = 5000;
int N;


//struct rectangle {
//    int y1;
//    int x1;
//    int y2;
//    int x2;
//};
//
//rectangle pictures[5000];

//int area (rectangle w, int level)
//{
//    if (w.y1 >= w.y2 || w.x1 >= w.x2) {
//        return (0);
//    }
//    for (int i = level; i < N; ++i) {
//        if (!
//            (w.y2 <= pictures[i].y1 || pictures[i].y2 <= w.y1
//            || w.x2 <= pictures[i].x1 || pictures[i].x2 <= w.x1)) {
//                rectangle  a;
//                a.y1 = w.y1;
//                a.x1 = w.x1;
//                a.y2 = w.y2;
//                a.x2 = pictures[i].x1;
//
//                rectangle  b;
//                b.y1 = w.y1;
//                b.x1 = pictures[i].x2;
//                b.y2 = w.y2;
//                b.x2 = w.x2;
//
//                rectangle  c;
//                c.y1 = w.y1;
//                c.x1 = max (w.x1, pictures[i].x1);
//                c.y2 = pictures[i].y1;
//                c.x2 = min (pictures[i].x2, w.x2);
//
//                rectangle  d;
//                d.y1 = pictures[i].y2;
//                d.x1 = max (w.x1, pictures[i].x1);
//                d.y2 = w.y2;
//                d.x2 = min (pictures[i].x2, w.x2);
//            return (area (a, i+1) + area (b, i+1) + area (c, i+1) + area (d, i+1));
//        }
//    }
//    return ((w.y2 - w.y1) * (w.x2 - w.x1));
//}

struct line {
    int b;
    int e;
    int p;
    bool up;
    bool operator<(const line & rhs) const{
        if (p == rhs.p && up && !rhs.up) {
            return true;
        }
        return p < rhs.p;
    }
};

int sol = 0;
line Xs[MAXN*2];
line Ys[MAXN*2];


void scan (line* arr) {
    int visits[20002] = {};
    for (int i = 0; i < 2*N; ++i) {
        if (arr[i].up) {
            for (int j = arr[i].b+10000; j < arr[i].e+10000; ++j) {
                visits[j] ++;
                if (visits[j] == 1) {
                    sol ++;
                }
            }
        }
        else {
            for (int j = arr[i].b+10000; j < arr[i].e+10000; ++j) {
                visits[j] --;
                if (visits[j] == 0) {
                    sol ++;
                }
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("picture.in");
    
    fin >> N;

    int xmin;
    int ymin;
    int xmax;
    int ymax;
    for (int i = 0; i < N; ++i) {
        fin >> xmin >> ymin >> xmax >> ymax;
        Xs[2*i].b = xmin;
        Xs[2*i].e = xmax;
        Xs[2*i].p = ymin;
        Xs[2*i].up = true;
        Xs[2*i+1].b = xmin;
        Xs[2*i+1].e = xmax;
        Xs[2*i+1].p = ymax;
        Xs[2*i+1].up = false;
        
        Ys[2*i].b = ymin;
        Ys[2*i].e = ymax;
        Ys[2*i].p = xmin;
        Ys[2*i].up = true;
        Ys[2*i+1].b = ymin;
        Ys[2*i+1].e = ymax;
        Ys[2*i+1].p = xmax;
        Ys[2*i+1].up = false;
    }
    
    fin.close();

    
    sort(Xs, Xs+2*N);
    sort(Ys, Ys+2*N);
    
    scan(Xs);
    scan(Ys);
    
    ofstream fout;
    fout.open("picture.out");
    
    fout << sol << endl;
    
    fout.close();
    
    return 0;
}



















































