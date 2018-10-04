//
//  main.cpp
//  fence4
//
//  Created by TFAN on 2018/10/1.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: fence4
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
#include <math.h>
#include <iomanip>

using namespace std;
int N;
const int MAXN = 200;
const double epsilon = 1e-3;

struct point {
    double x;
    double y;
};

point eye;
point corners[MAXN+1];
bool ans[MAXN+1] = {};
int cnt = 0;

double cross_z(point p1, point p2) {
    return p1.x*p2.y - p1.y*p2.x;
}

// if p3 and p4 are on different sides of the line p2p1
bool diffside(const point& p1, const point& p2, const point& p3, const point& p4) {
    point v1;
    v1.x = p2.x - p1.x;
    v1.y = p2.y - p1.y;
    point v2;
    v2.x = p3.x - p1.x;
    v2.y = p3.y - p1.y;
    point v3;
    v3.x = p4.x - p1.x;
    v3.y = p4.y - p1.y;
    double z1 = cross_z(v1, v2);
    double z2 = cross_z(v1, v3);

    if (z1 == 0 && z2 == 0) {
        return false;
    }
    if (z1*z2 <= 0) {
        // p3 is on the line p2-p1
        if (z1 == 0) {
            if ( (p3.x == p2.x && p3.y == p2.y) ||  (p3.x == p1.x && p3.y == p1.y)) {
                return false;
            }
            else {
                return true;
            }
        }
        // p4 is on the line p2-p1
        else if (z2 == 0) {
            if ( (p4.x == p2.x && p4.y == p2.y) ||  (p4.x == p1.x && p4.y == p1.y)) {
                return false;
            }
            else {
                return true;
            }
        }
        return true;
    }
    return false;
}

// if the segment p2-p1 intersects with p4-p3 properly
bool intersect(const point& p1, const point& p2, const point& p3, const point& p4) {
    return diffside(p1, p2, p3, p4) && diffside(p3, p4, p1, p2);
}

bool valid() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (intersect(corners[i], corners[i+1], corners[j], corners[j+1])) {
                return false;
            }
        }
    }
    return true;
}

bool see_left(const point& p1, const point& p2, bool right, int id);

bool see_right(const point& p1, const point& p2, bool left, int id) {
    
    if ( abs(p1.x - p2.x) < epsilon &&  abs(p1.y - p2.y) < epsilon) {
        return false;
    }
    
    bool seeRight = true;
    if ( left ) {
        for (int i = 0; i < N; ++i) {
            if (i != id) {
                if(intersect(eye, p2, corners[i], corners[i+1])) {
                    seeRight = false;
                    break;
                }
            }
        }
        if (seeRight)
            return true;
    }
    
    point mid;
    mid.x = (p1.x + p2.x)/2;
    mid.y = (p1.y + p2.y)/2;
    
    return see_right(p1, mid, left, id) || see_left(mid, p2, seeRight, id);
}

bool see_left(const point& p1, const point& p2, bool right, int id) {
    
    if ( abs(p1.x - p2.x) < epsilon &&  abs(p1.y - p2.y) < epsilon) {
        return false;
    }
    
    bool seeLeft = true;
    
    if ( right ) {
        for (int i = 0; i < N; ++i) {
            if (i != id) {
                if(intersect(eye, p1, corners[i], corners[i+1])) {
                    seeLeft = false;
                    break;
                }
            }
        }
        if (seeLeft)
            return true;
    }
    
    point mid;
    mid.x = (p1.x + p2.x)/2;
    mid.y = (p1.y + p2.y)/2;
    
    return see_right(p1, mid, seeLeft, id) || see_left(mid, p2, right, id);
}


bool see(const point& p1, const point& p2, int id) {
    
    if ( abs(p1.x - p2.x) < epsilon &&  abs(p1.y - p2.y) < epsilon) {
        return false;
    }
    
    point mid;
    mid.x = (p1.x + p2.x)/2;
    mid.y = (p1.y + p2.y)/2;
    bool seeTwoEnds = true;
    for (int i = 0; i < N; ++i) {
        if (i != id) {
            seeTwoEnds = seeTwoEnds && !(intersect(eye, p1, corners[i], corners[i+1]) || intersect(eye, p2, corners[i], corners[i+1]));
        }
        if (!seeTwoEnds) {
            break;
        }
    }
    if (seeTwoEnds) {
        return true;
    }
    
    return (see(p1, mid, id) || see(mid, p2, id));

}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("fence4.in");
    fin >> N;
    fin >> eye.x >> eye.y;
    
    for (int i = 0; i < N; ++i) {
        fin >> corners[i].x >> corners[i].y;
    }
    corners[N].x = corners[0].x;
    corners[N].y = corners[0].y;
    
    fin.close();
    
    
    ofstream fout;
    fout.open("fence4.out");
    
    if (valid()) {
        for (int i = 0; i < N; ++i) {
            if (see_left(corners[i], corners[i+1], false, i)) {
                ans[i] = true;
                cnt ++;
            }
        }
        
        fout << cnt << endl;
        
        for (int i = 0; i < N-2; ++i) {
            if (ans[i]) {
                fout << corners[i].x << ' ' << corners[i].y << ' ' << corners[i+1].x << ' ' << corners[i+1].y << endl;
            }
        }
        if (ans[N-1]) {
            fout << corners[N].x << ' ' << corners[N].y << ' ' << corners[N-1].x << ' ' << corners[N-1].y << endl;
        }
        if (ans[N-2]) {
            fout << corners[N-2].x << ' ' << corners[N-2].y << ' ' << corners[N-1].x << ' ' << corners[N-1].y << endl;
        }

    }
    
    else {
        fout << "NOFENCE" << endl;
    }
    
    
    fout.close();
    
    return 0;
}





































































