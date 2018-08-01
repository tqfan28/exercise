//
//  main.cpp
//  fence6
//
//  Created by TFAN on 2018/7/14.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: fence6
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
#include <sstream>

using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 100;
int adj[2*MAXN][2*MAXN] = {};

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

string listToStr(vector<int> vertexes) {
    string s;
    for (vector<int>::iterator itr = vertexes.begin(); itr != vertexes.end(); ++itr) {
        s = s + " " + IntToString(*itr);
    }
    return s;
}

void init() {
    for (int i = 0; i < 2*MAXN; ++i) {
        for (int j = 0; j < 2*MAXN; ++j) {
            adj[i][j] = infty;
        }
        adj[i][i] = 0;
    }
}

int mindist(int dist[], bool visited[], int counter) {
    int mind = infty;
    int mini;
    for (int i = 0; i < counter; ++i) {
        if (!visited[i] && dist[i] < mind) {
            mind = dist[i];
            mini = i;
        }
    }
    return mini;
}

int dijkstra(int weight[2*MAXN][2*MAXN], int src, int tail, int counter) {
    int dist[2*MAXN];
    bool visited[2*MAXN] = {};
    for (int i = 0; i < counter; ++i) {
        dist[i] = infty;
    }
    dist[src] = 0;
    for (int i = 0; i < counter-1; ++i) {
        int u = mindist(dist, visited, counter);
        visited[u] = true;
        for (int j = 0; j < counter; ++j) {
            if (!visited[j] && dist[u] != infty && weight[u][j] != infty && dist[u] + weight[u][j] < dist[j]) {
                dist[j] = dist[u] + weight[u][j];
            }
        }
    }
    return dist[tail];
}

int main(int argc, const char * argv[]) {
    
    
    init();
    
    ifstream fin ("fence6.in");
    fin >> N;
    int counter = 0;
    map<string, int> encode;

    
    for (int i = 0; i < N; ++i) {
        
        int id, len;
        fin >> id >> len;
        int l1, l2;
        fin >> l1 >> l2;
        vector<int> vertexes;
        vertexes.push_back(id);
        int v;
        for (int j = 0; j < l1; ++j) {
            fin >> v;
            vertexes.push_back(v);
        }
        sort(vertexes.begin(), vertexes.end());
        string s = listToStr(vertexes);
        map<string, int>::iterator itr = encode.find(s);
        if (itr == encode.end()) {
            encode[s] = counter;
            counter ++;
        }
        int v1 = encode[s];
        
        vector<int> vertexes2;
        vertexes2.push_back(id);
        for (int j = 0; j < l2; ++j) {
            fin >> v;
            vertexes2.push_back(v);
        }
        sort(vertexes2.begin(), vertexes2.end());
        s = listToStr(vertexes2);
        itr = encode.find(s);
        if (itr == encode.end()) {
            encode[s] = counter;
            counter ++;
        }
        int v2 = encode[s];
        adj[v1][v2] = len;
        adj[v2][v1] = len;
    }
    int sol = infty;
    for (int i = 0; i < counter; ++i) {
        for (int j = i+1; j < counter; ++j) {
            if (adj[i][j] < infty) {
                int weight[2*MAXN][2*MAXN] = {};
                for (int s = 0; s < counter; ++s) {
                    for (int t = 0; t < counter; ++t) {
                        weight[s][t] = adj[s][t];
                    }
                }
                weight[i][j] = infty;
                weight[j][i] = infty;
                int tmp = dijkstra(weight, i, j, counter);
                if (tmp < infty)
                    sol = min(sol, adj[i][j]+ dijkstra(weight, i, j, counter));
            }
        }
    }
    
    
    ofstream fout ("fence6.out");
    fout << sol << endl;
    fout.close();
    return 0;
}



























