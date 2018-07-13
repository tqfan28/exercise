//
//  main.cpp
//  fence9
//
//  Created by TFAN on 2018/7/12.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: fence9
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>


//using namespace std;
//const int infty = 0x7fffffff;
//float n;
//float m;
//float p;
//
//int cross_z(float p1, float p2, float q1, float q2) {
//    float det = p1*q2 - p2*q1;
//    if (det > 0)
//        return 1;
//    else if (det < 0)
//        return -1;
//    else
//        return 0;
//}
//
//bool sameSide(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2) {
//    int z1 = cross_z(b1-a1, b2-a2, c1-a1, c2-a2);
//    int z2 = cross_z(b1-a1, b2-a2, d1-a1, d2-a2);
//    if (z1 == z2)
//        return true;
//    else
//        return false;
//}
//
//bool in(float c1, float c2, float d1, float d2) {
//    if ( sameSide(0, 0, n, m, c1, c2, d1, d2) &&
//         sameSide(0, 0, p, 0, c1, c2, d1, d2) &&
//         sameSide(p, 0, n, m, c1, c2, d1, d2)
//        )
//        return true;
//    else
//        return false;
//}
//
//int main(int argc, const char * argv[]) {
//
//    ifstream fin ("fence9.in");
//    fin >> n >> m >> p;
//
//    float c1 = (n+p)/3;
//    float c2 = m/3;
//
//    int sol = 0;
//
//    for (int i = 0; i < max(n, p); ++i) {
//        for (int j = 0; j < m; ++j) {
//            if (in(i, j, c1, c2)) {
//                sol++;
//            }
//        }
//    }
//
//    ofstream fout ("fence9.out");
//    fout << sol << endl;
//    fout.close();
//    return 0;
//}


using namespace std;
const int infty = 0x7fffffff;
int n;
int m;
int p;

int twoArea(int a1, int a2, int b1, int b2, int c1, int c2) {
    int u1 = b1-a1;
    int u2 = b2-a2;
    int v1 = c1-a1;
    int v2 = c2-a2;
    return abs(u1*v2 - u2*v1);
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int latticeLine(int a1, int a2, int b1, int b2) {
    return gcd(abs(b1-a1), abs(b2-a2)) + 1;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("fence9.in");
    fin >> n >> m >> p;
    
    int sol = (twoArea(0, 0, n, m, p, 0) - latticeLine(0, 0, n, m) - latticeLine(n, m, p, 0) - latticeLine(0, 0, p, 0) + 5)/2;
    
    ofstream fout ("fence9.out");
    fout << sol << endl;
    fout.close();
    return 0;
}

























