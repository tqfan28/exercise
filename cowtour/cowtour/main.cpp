//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: cowtour
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
int N;
const int MAXN = 150;
bool adj[MAXN][MAXN] = {};
double dist[MAXN][MAXN] = {};
int components[MAXN] = {};
double dia[MAXN] = {};

struct xy {
    int x;
    int y;
    int d;
};

xy pastures[MAXN];

double norm(int x1, int y1, int x2, int y2) {
    double result = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    result = sqrt(result);
    return result;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("cowtour.in");

    fin >> N;

    for (int i = 0; i < N; ++i) {
        fin >> pastures[i].x >> pastures[i].y;
        //cout << pastures[i].x << ' ' << pastures[i].y << endl;
    }
    
    string get;
    getline(fin, get);
    for (int i = 0; i < N; ++i) {
        getline(fin, get);
        //cout << get << endl;
        for (int j = 0; j < N; ++j) {
            if (get[j] == '0')
                adj[i][j] = false;
            else
                adj[i][j] = true;
            //cout << adj[i][j];
        }
        //cout << endl;
    }
    

    //Floyd-Warshall
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else if (!adj[i][j]) {
                dist[i][j] = 999999;
            }
            else {
                dist[i][j] = norm(pastures[i].x, pastures[i].y,  pastures[j].x, pastures[j].y);
            }
        }
    }
    
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            cout << dist[i][j] << ' ';
//        }
//        cout << endl;
//    }
    
    
    double ans = 999999;
    memset(components, -1, sizeof(components));
    
    int counter = 0;
    for (int i = 0; i < N; ++i) {
        if (components[i] == -1)
            components[i] = counter;
        for (int j = 0; j < N; ++j) {
            if (dist[i][j] < 999999) {
                components[j] = counter;
            }
        }
        counter ++;
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (components[j] == components[i]) {
                for (int k = 0; k < N; ++k) {
                    if (components[k] == components[j]) {
                        dia[i] = max(dia[i], dist[j][k]);
                    }
                }
            }
        
        }
    }

    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (dist[i][j] == 999999) {
                double result = 0;
                result += norm(pastures[i].x, pastures[i].y,  pastures[j].x, pastures[j].y);
                //cout << result << endl;
                double tmp = 0;
                for (int k = 0; k < N; ++k) {
                    if (dist[i][k] < 999999)
                        tmp = max(tmp, dist[i][k]);
                }
                result += tmp;
                tmp = 0;
                for (int k = 0; k < N; ++k) {
                    if (dist[k][j] < 999999)
                        tmp = max(tmp, dist[k][j]);
                }
                result += tmp;
                double diameters = max(dia[i], dia[j]);
                result = max(diameters, result);
                ans = min(ans, result);
                //cout << i << ' ' <<j << ' ' << result << endl;
            }
        }
    }
    
    ofstream fout ("cowtour.out");
    
    fout << fixed << setprecision(6) << ans<< endl;
    
    fout.close();
    
    return 0;
}




























