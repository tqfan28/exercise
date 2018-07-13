
//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: butter
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
//const int infty = 0x7fffffff;
const int infty = 999999;
int N;
int P;
int C;
const int MAXP = 800;
bool visited[MAXP+1] = {};
//int adj[MAXP+1][MAXP+1];

int dist[MAXP+1][MAXP+1];
queue<int> cows;

//void init() {
//    for (int i = 0; i < MAXP+1; ++i) {
//        for (int j = 0; j < MAXP+1; ++j) {
//            adj[i][j] = infty;
//        }
//        adj[i][i] = 0;
//    }
//}

//int main(int argc, const char * argv[]) {
//    queue<int> cows;
//    ifstream fin ("butter.in");
//    fin >> N >> P >> C;
//    int tmp;
//    for (int i = 0; i < N; ++i) {
//        fin >> tmp;
//        cows.push(tmp);
//    }
//
//    init();
//
//    int start, end;
//    for (int i = 0; i < C; ++i) {
//        fin >> start >> end;
//        fin >> adj[start][end];
//        adj[end][start] = adj[start][end];
//    }
//
//    for (int i = 1; i < P+1; ++i) {
//        for (int j = 1; j < P+1; ++j) {
//            dist[i][j] = adj[i][j];
//        }
//    }
//
//    for (int k = 1; k < P+1; ++k) {
//        for (int i = 1; i < P+1; ++i) {
//            for (int j = 1; j < P+1; ++j) {
//                if (dist[i][k] + dist[k][j] < dist[i][j]) {
//                    dist[i][j] = dist[i][k] + dist[k][j];
//                }
//            }
//        }
//    }
//
//    int result = infty;
//    for (int i = 1; i < P+1; ++i) {
//        queue<int> line = cows;
//        int tmp = 0;
//        while (!line.empty()) {
//            tmp += dist[i][line.front()];
//            line.pop();
//        }
//        result = min(result, tmp);
//    }
//    ofstream fout ("butter.out");
//    fout << result << endl;
//    fout.close();
//
//    return 0;
//}

void init() {
    for (int i = 0; i < MAXP+1; ++i) {
        for (int j = 0; j < MAXP+1; ++j) {
            dist[i][j] = infty;
        }
        dist[i][i] = 0;
    }
}

struct node {
    int i;
    int d;
    int operator<(const node& rhs)const{
        return d > rhs.d;
    }
};

struct edge {
    int n;
    int w;
};

queue<edge> edges[MAXP+1];

int dijkstra(int vertex) {
    priority_queue<node> line;
    for (int i = 1; i < P + 1; ++ i) {
        visited[i] = false;
    }
    line.push(node{vertex, 0});
    
    while (!line.empty()) {
        int i = line.top().i;
        line.pop();
        if (visited[i])
            continue;
        visited[i] = true;
        queue<edge> line3 = edges[i];
        while(!line3.empty()) {
            int j = line3.front().n;
            int w = line3.front().w;
            if (!visited[j] && dist[vertex][j] > (dist[vertex][i] + w)) {
                dist[vertex][j] = dist[vertex][i] + w;
                line.push(node{j, dist[vertex][j]});
            }
            line3.pop();
        }
    }
    // 67 338 212
    int total = 0;
    queue<int> line2 = cows;
    while(!line2.empty()) {
        total += dist[vertex][line2.front()];
        line2.pop();
    }
    return total;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("butter.in");
    fin >> N >> P >> C;
    int tmp;
    for (int i = 0; i < N; ++i) {
        fin >> tmp;
        cows.push(tmp);
    }
    
    init();
    
    int start, end, weight;
    for (int i = 0; i < C; ++i) {
        fin >> start >> end >> weight;
        edges[start].push(edge{end,weight});
        edges[end].push(edge{start,weight});
    }
    
    int result = infty;
    
    for (int i = 1; i < P+1; ++i) {
        result = min(result, dijkstra(i));
    }
    ofstream fout ("butter.out");
    fout << result << endl;
    fout.close();
    
    return 0;
}

















