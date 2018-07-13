//
//  main.cpp
//  USACO4
//
//  Created by TFAN on 2017/8/13.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: beads
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//w
//wr
//rw
//rwr
//rwb

struct sketch {
    char color;
    int number;
};


int main(int argc, const char * argv[]) {
    //std::cout << "Hello, World!\n";
    
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
    
    int n = 0;
    fin >> n;
    string input;
    fin >> input;
    vector<sketch> result;
    
    for (int i = 0; i < n; ++i) {
        sketch one;
        int j = i;

        one.color = input[i];
        one.number = 0;
        while (j != n && input[j] == input[i]) {
            one.number = one.number +1;
            ++j;
        }
        result.push_back(one);
        i = j-1;
        //cout << one.color << ' ' << one.number << endl;
    }

    if (result.size() < 3) {
        fout << n << endl;
    }
    else {
        vector<int> compute;
        for (vector<sketch>::iterator i = result.begin(); i < result.end(); ++i) {
            vector<sketch>::iterator j = i;
            int m;
            if ((*j).color == 'w') m = 0;
            else m = 1;
            char prev = (*i).color;
            while (j != result.end() && m < 2) {
                if ((*j).color != 'w' && (*j).color != prev) {
                    ++m;
                    prev = (*j).color;
                }
                ++j;
            }
            while (j != result.end() && (*j).color == 'w') {
                ++j;
            }
            
            if (m < 2) {
                j = result.begin();
                while (j != i && m < 2) {
                    if ((*j).color != 'w' && (*j).color != prev) {
                        ++m;
                        prev = (*j).color;
                    }
                    ++j;
                }
                while (j != i && (*j).color == 'w') {
                    ++j;
                }
                int x = 0;
                for (vector<sketch>::iterator k = i; k < result.end(); ++k) {
                    x += (*k).number;
                }
                for (vector<sketch>::iterator k = result.begin(); k < j; ++k) {
                    x += (*k).number;
                }
                compute.push_back(x);
            }
            else if (j == result.end()) {
                j = result.begin();
                while (j !=i && ((*j).color == prev || (*j).color == 'w')) {
                    ++j;
                }
                int x = 0;
                for (vector<sketch>::iterator k = i; k < result.end(); ++k) {
                    x += (*k).number;
                }
                for (vector<sketch>::iterator k = result.begin(); k < j; ++k) {
                    x += (*k).number;
                }
                compute.push_back(x);
            }
            else {
                int x = 0;
                for (vector<sketch>::iterator k = i; k < j; ++k) {
                    x = x + (*k).number;
                }
                compute.push_back(x);
            }
        }
        /*
        for (vector<int>::iterator i = compute.begin(); i < compute.end(); ++i) {
            cout << (*i) << endl;
        }
        */
        fout << *(max_element(compute.begin(), compute.end())) << endl;
    }
    
    return 0;
}
