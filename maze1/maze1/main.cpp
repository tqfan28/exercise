//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: maze1
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>


using namespace std;
int W;
int H;
const int MAXW = 38;
const int MAXH = 100;
bool board[2*MAXH+1][2*MAXW+1] = {};
bool edges[MAXH][MAXW][4] = {};
bool visited[MAXH][MAXW] = {};
int pathx[MAXH][MAXW] = {};
int pathy[MAXH][MAXW] = {};
bool computed[MAXH][MAXW] = {};

struct xy {
    int x;
    int y;
    int d;

};


bool isout(xy ele, queue<xy> out) {
    queue<xy> tmp = out;
    while(!tmp.empty()) {
        if (tmp.front().x == ele.x && tmp.front().y == ele.y) {
            //cout << tmp.front().x << tmp.front().y;
            return true;
        }
        tmp.pop();
    }
    return false;
}

void setComputed(xy start, xy end) {
    while (end.x != start.x || end.y != start.y) {
        computed[end.x][end.y] = true;
        int x = pathx[end.x][end.y];
        int y = pathy[end.x][end.y];
        end.x = x;
        end.y = y;
        //cout << end.x << end.y << endl;
    }
}

int bfs(xy start, queue<xy> out) {
    
    if (isout(start, out))
        return 0;
    
    queue<xy> lines;
    visited[start.x][start.y] = true;
    lines.push(start);
    
    while(!lines.empty()) {
        xy next;
        cout << lines.front().x << ' ' << lines.front().y << ' ' << lines.front().d << endl;

        
        if (edges[lines.front().x][lines.front().y][0]) {
            next.x = lines.front().x-1;
            next.y = lines.front().y;
            next.d = lines.front().d+1;

            if (isout(next, out)) {
                setComputed(start, lines.front());
                return next.d;
            }
            
            if (!visited[next.x][next.y]) {
                pathx[next.x][next.y] = lines.front().x;
                pathy[next.x][next.y] = lines.front().y;
                visited[next.x][next.y] = true;
                lines.push(next);
 
            }
        }
        if (edges[lines.front().x][lines.front().y][1]) {
            next.x = lines.front().x;
            next.y = lines.front().y+1;
            next.d = lines.front().d+1;
            if (isout(next, out)) {
                setComputed(start, lines.front());
                return next.d;
            }
            if (!visited[next.x][next.y]) {
                pathx[next.x][next.y] = lines.front().x;
                pathy[next.x][next.y] = lines.front().y;
                visited[next.x][next.y] = true;
                lines.push(next);
            }

        }
        if (edges[lines.front().x][lines.front().y][2]) {
            next.x = lines.front().x+1;
            next.y = lines.front().y;
            next.d = lines.front().d+1;
            if (isout(next, out)) {
                setComputed(start, lines.front());
                return next.d;
            }
            if (!visited[next.x][next.y]) {
                pathx[next.x][next.y] = lines.front().x;
                pathy[next.x][next.y] = lines.front().y;
                visited[next.x][next.y] = true;
                lines.push(next);
  
            }
        }
        if (edges[lines.front().x][lines.front().y][3]) {
            next.x = lines.front().x;
            next.y = lines.front().y-1;
            next.d = lines.front().d+1;
            if (isout(next, out)) {
                setComputed(start, lines.front());
                return next.d;
            }
            if (!visited[next.x][next.y]) {
                pathx[next.x][next.y] = lines.front().x;
                pathy[next.x][next.y] = lines.front().y;
                visited[next.x][next.y] = true;
                lines.push(next);
            }
        }
        lines.pop();
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("maze1.in");
    fin >> W >> H;
    
    string tmp;
    getline(fin, tmp);
    
    for (int i = 0; i < 2*H+1; ++i) {
        getline(fin, tmp);
        
        if (tmp.length() < 2*W+1) {
            int init = tmp.length();
            for (int k = 0; k < 2*W+1-init; ++k) {
                tmp += " ";
            }
        }
        
        for (int j = 0; j < 2*W+1; ++j) {
            //cout << tmp[j] << (tmp[j] == ' ');
            if (tmp[j] == ' ')
                board[i][j] = true;
            else
                board[i][j] = false;
        }
        //cout << endl;
    }
    
    //     i = 0 ... H-1;
    //     j = 0 ... W-1;
    //     the index for square is (2i+1, 2j+1);
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            // up
            if (board[2*i][2*j+1]) {
                edges[i][j][0] = true;
            }
            //right
            if (board[2*i+1][2*j+2]) {
                edges[i][j][1] = true;
            }
            //down
            if (board[2*i+2][2*j+1]) {
                edges[i][j][2] = true;
            }
            //left
            if (board[2*i+1][2*j]) {
                edges[i][j][3] = true;
            }
        }
    }
    
    //test for edges
//    for (int i = 0; i< H; ++i) {
//        for (int j = 0; j < W; ++j) {
//            for (int k = 0; k < 4; ++k) {
//                cout << edges[i][j][k];
//            }
//            cout << ' ';
//        }
//        cout << endl;
//    }
    
    
    queue<xy> out;
    
    for (int i = 0; i < H; ++i) {
        xy square;
        // first col
        if (edges[i][0][3]) {
            square.x = i;
            square.y = 0;
            out.push(square);
        }
        // last col
        if (edges[i][W-1][1]) {
            square.x = i;
            square.y = W-1;
            out.push(square);
        }
    }
    
    for (int j = 0; j < W; ++j) {
        xy square;
        // first row
        if (edges[0][j][0]) {
            square.x = 0;
            square.y = j;
            out.push(square);
        }
        // last col
        if (edges[H-1][j][2]) {
            square.x = H-1;
            square.y = j;
            out.push(square);
        }
    }
    
    //test for out
//    while(!out.empty()) {
//        cout << out.front().x << ' '<< out.front().y << endl;
//        out.pop();
//    }
    
    
    int result = 1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (!computed[i][j]) {
                xy current;
                current.x = i;
                current.y = j;
                current.d = 0;
                result = max(result, bfs(current, out)+1);
                memset(visited, false, sizeof(visited));
//                for (int i = 0; i < H; ++i) {
//                    for (int j = 0; j < W; ++j) {
//                        cout << pathx[i][j] << ' '<< pathy[i][j] << "  ";
//                    }
//                    cout << endl;
//                }
                memset(pathx, 0, sizeof(pathx));
                memset(pathy, 0, sizeof(pathy));
//                for (int a = 0; a < H; ++a) {
//                    for (int b = 0; b < W; ++b) {
//                        cout << computed[a][b];
//                    }
//                    cout << endl;
//                }
            }
            //cout <<"here" << i << ' ' << j << ' ' << result << endl;
        }
    }

    
    
    ofstream fout ("maze1.out");
 
    cout << result << endl;
    
    fout.close();
    
    return 0;
}


























