//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: milk3
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int capacity[3]={};
int milk_in_c[21] = {};
int milk[3] = {};
int pattern[103000] = {};


void milk_left(int start_pos, int end_pos) {
    if (pattern[(start_pos*10000+ end_pos*1000 + milk[0]*100 + milk[1])] == 1) {
        return;
    }
    else {
        pattern[(start_pos*10000+ end_pos*1000 + milk[0]*100 + milk[1])] = 1;
        int a = milk[end_pos] + milk[start_pos];
        if ( a > capacity[end_pos]) {
            milk[end_pos] = capacity[end_pos];
            milk[start_pos] = a - capacity[end_pos];
        }
        else {
            milk[end_pos] = a;
            milk[start_pos] = 0;
        }
        if (milk[0] == 0) {
            milk_in_c[(milk[2])] = 1;
        }
        //cout << milk[0] << ' ' << milk[1] << ' ' << milk[2] << endl;
        int x = milk[0];
        int y = milk[1];
        int z = milk[2];
        if (milk[0] != 0) {
            milk_left( 0, 1);
            milk[0] = x;
            milk[1] = y;
            milk[2] = z;
            milk_left( 0, 2);
        }
        if (milk[1] != 0) {
            milk[0] = x;
            milk[1] = y;
            milk[2] = z;
            milk_left( 1, 0);
            milk[0] = x;
            milk[1] = y;
            milk[2] = z;
            milk_left( 1, 2);
        }
        if (milk[2] != 0) {
            milk[0] = x;
            milk[1] = y;
            milk[2] = z;
            milk_left( 2, 0);
            milk[0] = x;
            milk[1] = y;
            milk[2] = z;
            milk_left( 2, 1);
        }
        return;
    }
}


int main(int argc, const char * argv[]) {
    
    ifstream fin ("milk3.in");
    fin >> capacity[0] >> capacity[1] >> capacity[2];
    milk[2] = capacity[2];
    
    milk_left(2, 0);
    milk_left(2, 1);
    
    ofstream fout ("milk3.out");
    int count = 0;
    for (int i = 0; i < 21; ++i) {
        if (milk_in_c[i] == 1)
            if (count == 0) {
                fout << i ;
                count ++;
            }
            else {
                fout << ' ' << i;
            }
    }
    fout << endl;
    fout.close();
    

    return 0;
}









