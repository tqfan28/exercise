//
//  main.cpp
//  frameup
//
//  Created by TFAN on 2018/8/1.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: frameup
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
#include <cmath>
#include <utility>



using namespace std;
const int infty = 0x7fffffff;
const int MAXH = 30;
int H;
int W;
char board[MAXH][MAXH];
const int LETTER = 26;
int depth = 0;
vector<string> ansPrint;


struct xy {
    int x;
    int y;
};

list<xy> letters[LETTER];

struct frame {
    char letter;
    int xmax;
    int xmin;
    int ymax;
    int ymin;
};

frame frames [LETTER];

bool walk_v(int i, int s, int e, char c, bool mask[LETTER]) {
    for (int j = s; j < e+1; ++j) {
        if (board[i][j] == c || !mask[int(board[i][j]-65)]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

bool walk_h(int j, int s, int e, char c, bool mask[LETTER]) {
    for (int i = s; i < e+1; ++i) {
        if (board[i][j] == c || !mask[int(board[i][j]-65)]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

void dfs(bool mask[LETTER], int d, string s) {
    if (d == depth) {
        ansPrint.push_back(s);
    }
    else {
        for (int i = 0; i < LETTER; ++i) {
            if (mask[i]) {
                char c = i+65;
                if ( walk_v(frames[i].xmin, frames[i].ymin, frames[i].ymax, c, mask)
                    && walk_v(frames[i].xmax, frames[i].ymin, frames[i].ymax, c, mask)
                    && walk_h(frames[i].ymin, frames[i].xmin, frames[i].xmax, c, mask)
                    && walk_h(frames[i].ymax, frames[i].xmin, frames[i].xmax, c, mask)
                    ) {
                    bool maskCopy[LETTER];
                    for (int j = 0; j < LETTER; ++j) {
                        maskCopy[j] = mask[j];
                    }
                    maskCopy[i] = false;
                    dfs(maskCopy, d+1, c+s);
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("frameup.in");
    fin >> H >> W;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            fin >>board[i][j];
        }
    }
    fin.close();
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (board[i][j] != '.') {
                xy tmp;
                tmp.x = i;
                tmp.y = j;
                letters[int(board[i][j]-65)].push_back(tmp);
            }
        }
    }
    
    bool mask[LETTER] = {};
    
    for (int i = 0; i < LETTER; ++i) {
        if (!letters[i].empty()) {
            frame aFrame;
            aFrame.xmax = -1;
            aFrame.xmin = infty;
            aFrame.ymax = -1;
            aFrame.ymin = infty;
            for (list<xy>::iterator itr = letters[i].begin(); itr != letters[i].end(); ++itr) {
                aFrame.xmax = max((*itr).x, aFrame.xmax);
                aFrame.xmin = min((*itr).x, aFrame.xmin);
                aFrame.ymax = max((*itr).y, aFrame.ymax);
                aFrame.ymin = min((*itr).y, aFrame.ymin);
            }
            aFrame.letter = i+65;
            frames[i] = aFrame;
            mask[i] = true;
            depth ++;
        }
    }
    

    string s;
    dfs(mask, 0, s);
    
    ofstream fout;
    fout.open("frameup.out");
    sort(ansPrint.begin(), ansPrint.end());
    for (vector<string>::iterator i = ansPrint.begin(); i != ansPrint.end(); ++i) {
        fout << *i << endl;
    }
    
    fout.close();
    
    return 0;
}
































