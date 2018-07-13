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


struct xy {
    int x;
    int y;
    int d;
    
};


int** bfs(xy start) {
    
    int** search = 0;
    search = new int*[H];
    for (int i= 0; i < H; ++i) {
        search[i] = new int[W];
    }

    queue<xy> lines;
    visited[start.x][start.y] = true;
    lines.push(start);

    while(!lines.empty()) {
        xy next;
        //cout << lines.front().x << ' ' << lines.front().y << ' ' << lines.front().d << endl;
        
        if (lines.front().x > 0 && edges[lines.front().x][lines.front().y][0]) {
            next.x = lines.front().x-1;
            next.y = lines.front().y;
            
            if (!visited[next.x][next.y]) {
                next.d = lines.front().d+1;
                visited[next.x][next.y] = true;
                lines.push(next);
            }
        }
        if (lines.front().y < W-1 && edges[lines.front().x][lines.front().y][1]) {
            next.x = lines.front().x;
            next.y = lines.front().y+1;
            
            if (!visited[next.x][next.y]) {
                next.d = lines.front().d+1;
                visited[next.x][next.y] = true;
                lines.push(next);
            }
            
        }
        if (lines.front().x < H-1 && edges[lines.front().x][lines.front().y][2]) {
            next.x = lines.front().x+1;
            next.y = lines.front().y;
            
            if (!visited[next.x][next.y]) {
                next.d = lines.front().d+1;
                visited[next.x][next.y] = true;
                lines.push(next);
            }
                
        }
        if (lines.front().y > 0 && edges[lines.front().x][lines.front().y][3]) {
            next.x = lines.front().x;
            next.y = lines.front().y-1;
            if (!visited[next.x][next.y]) {
                next.d = lines.front().d+1;
                visited[next.x][next.y] = true;
                lines.push(next);
            }
        }
        //counter ++;
        //cout << lines.front().x << ' ' << lines.front().y << ' ' << lines.front().d << endl;
        search[lines.front().x][lines.front().y] = lines.front().d;
        lines.pop();
    }
    
    return search;
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
            square.d = 0;
            out.push(square);
        }
        // last col
        if (edges[i][W-1][1]) {
            square.x = i;
            square.y = W-1;
            square.d = 0;
            out.push(square);
        }
    }
    
    for (int j = 0; j < W; ++j) {
        xy square;
        // first row
        if (edges[0][j][0]) {
            square.x = 0;
            square.y = j;
            square.d = 0;
            out.push(square);
        }
        // last col
        if (edges[H-1][j][2]) {
            square.x = H-1;
            square.y = j;
            square.d = 0;
            out.push(square);
        }
    }
    
    //test for out
//        while(!out.empty()) {
//            cout << out.front().x << ' '<< out.front().y << endl;
//            out.pop();
//        }
    
    
//    out.pop();
//    cout << bfs(out.front())+1;

    int** solution = bfs(out.front());
    out.pop();
    int** matrix;
   
    while(!out.empty()) {
        memset(visited, false, sizeof(visited));
        //cout << out.front().x << ' ' << out.front().y << bfs(out.front())+1 << endl;
        matrix = bfs(out.front());
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (matrix[i][j] < solution[i][j])
                    solution[i][j] = matrix[i][j];
            }
        }
        out.pop();
    }
    
    int result = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (result < solution[i][j])
                result = solution[i][j];
        }
    }
    
    ofstream fout ("maze1.out");
    
    fout << result+1 << endl;
    
    fout.close();
    
    return 0;
}



























