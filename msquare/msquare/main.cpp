
//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: msquare
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>


using namespace std;
int target;
bool visited[40320];
const int infty = 0x7fffffff;
int dist[40320];
int parent[40320];
int square[8];
char action[40320];

int toInt (const int (&square)[8]) {
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        result = result*10 + square[i];
    }
    return result;
}

int A() {
    int nextA[8];
    for (int i = 0; i < 8; ++i) {
        nextA[i] = square[7-i];
    }
    return toInt(nextA);
}

int B() {
    int nextB[8];
    nextB[0] = square[3];
    nextB[1] = square[0];
    nextB[2] = square[1];
    nextB[3] = square[2];
    nextB[4] = square[5];
    nextB[5] = square[6];
    nextB[6] = square[7];
    nextB[7] = square[4];
    return toInt(nextB);
}

int C() {
    int nextC[8];
    nextC[0] = square[0];
    nextC[7] = square[7];
    nextC[3] = square[3];
    nextC[4] = square[4];
    nextC[1] = square[6];
    nextC[2] = square[1];
    nextC[5] = square[2];
    nextC[6] = square[5];
    return toInt(nextC);
}


void init() {
    for (int i = 0; i < 40320; ++i) {
        dist[i] = infty;
        parent[i] = -1;
        visited[i] = false;
    }
}

void ToArray(int value) {
    for (int i = 0; i < 8; ++i) {
        square[7-i] = value % 10;
        value = (value - value % 10)/10;
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("msquare.in");
    
    for (int i = 0; i < 8; ++i) {
        fin >> square[i];
    }
    target = toInt(square);
    for (int i = 0; i < 8; ++i) {
        square[i] = i+1;
    }
    const int source = toInt(square);
    
    map<int,int> toIndex;
    map<int,int> toValue;
    int i = 0;
    do {
        toValue[i] = toInt(square);
        toIndex[toValue[i]] = i;
        ++i;
    } while (next_permutation(square, square+8));
    
    //bfs
    init();
    dist[toIndex[source]] = 0;
    queue<int> lines;
    lines.push(toIndex[source]);
    visited[toIndex[source]] = true;
    
    while(!lines.empty()) {
        int index = lines.front();
        
        ToArray(toValue[index]);
   
        int neighbor = A();
        
        if (!visited[toIndex[neighbor]]) {
            visited[toIndex[neighbor]] = true;
            dist[toIndex[neighbor]] = dist[index] + 1;
            parent[toIndex[neighbor]]= index;
            action[toIndex[neighbor]] = 'A';
            if (neighbor == target)
                break;
            lines.push(toIndex[neighbor]);
        }
        neighbor = B();
        
        if (!visited[toIndex[neighbor]]) {
            visited[toIndex[neighbor]] = true;
            dist[toIndex[neighbor]] = dist[index] + 1;
            parent[toIndex[neighbor]]= index;
            action[toIndex[neighbor]] = 'B';
            if (neighbor == target)
                break;
            lines.push(toIndex[neighbor]);
        }
        neighbor = C();
        
        if (!visited[toIndex[neighbor]]) {
            visited[toIndex[neighbor]] = true;
            dist[toIndex[neighbor]] = dist[index] + 1;
            parent[toIndex[neighbor]]= index;
            action[toIndex[neighbor]] = 'C';
            if (neighbor == target)
                break;
            lines.push(toIndex[neighbor]);
        }
        lines.pop();
    }
    string path;
    int index = toIndex[target];
    while(index != 0) {
        path = action[index] + path;
        index = parent[index];
    }
    ofstream fout ("msquare.out");
    fout << dist[toIndex[target]] << endl;
    for (int i = 0; i < path.length(); ++i) {
        if (i!=0 && i%60 ==0 && i != path.length()-1)
            fout << endl;
        fout << path[i];
    }
    fout << endl;
    fout.close();
    
    return 0;
}

















