//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: castle
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int N;
int M;
int edges [2*50][50] = {};
int vertexes [50][50] = {};
int components [50][50] = {};
int room_nums [50*50] = {};

int * checkWalls (int input) {
    static int result [4] = {};
    for (int i = 0; i <4; ++i) {
        result[i] = input % 2;
        input = (input - result[i])/2;
    }
    return result;
}

void DFS (int j, int i, int component) {
    vertexes[j][i] = 1;
    components[j][i] = component;
    //room_num ++;
    if ( (j != 0) &&  (edges[2*(j-1)+1][i] == 1) && (vertexes[j-1][i] ==0) ) {
        //up
        DFS (j-1, i, component);
    }
    if ((j != N-1) && (edges[2*j+1][i] == 1) && (vertexes[j+1][i] ==0)) {
        //down
        DFS(j+1, i, component);
    }
    if ((i != 0) && (edges[2*j][i-1] == 1) && (vertexes[j][i-1] ==0)) {
        //left
        DFS(j, i-1,component);
    }
    if ((i != M-1) && (edges[2*j][i] == 1) && (vertexes[j][i+1] ==0)) {
        //right
        DFS(j, i+1, component);
    }
}

int connected_components () {
    int component = 0;
    for (int j = 0; j < N; ++j ) {
        for (int i = 0; i < M; ++i) {
            if (vertexes[j][i] == 0) {
                DFS(j, i, component);
                component ++;
            }
        }
    }
    return component;
}

bool myfn(int i, int j) { return i<j; }

int main(int argc, const char * argv[]) {
    
    ifstream fin ("castle.in");
//test function checkWalls

    //    int * result = checkWalls(11);
    //    for (int i = 0; i < 4; ++i) {
    //        cout << result[i] << endl;
    //    }
    fin >> M >> N;
    //edge connecting vertex(j, i) and vertex(j, i+1) is represented by edges[2*j][i] = 1;
    //edge connecting vertex(j, i) and vertex(j+1, i) is represented by edges[2*j+1][i] = 1;
    
    int * walls;
    int wall;
    //add edges
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < M; ++i) {
            fin >>wall;
            walls = checkWalls(wall);
            //east
            if (walls[2] == 0) {
                edges[2*j][i] = 1;
            }
            //south
            if (walls[3] == 0) {
                edges[2*j+1][i] = 1;
            }
        }
    }
//test add edges
//    for (int j = 0; j < 2*N; ++j) {
//        for (int i = 0; i < M; ++i){
//            cout << edges[j][i] << " ";
//        }
//        cout << endl;
//    }
    
    
    ofstream fout ("castle.out");
    
    int num_components = connected_components();
    fout << num_components << endl;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < M; ++i) {
            room_nums[components[j][i]] ++;
            //cout << components[j][i] << " " << room_nums[components[j][i]] << endl;
        }
    }
    int largest = *max_element(room_nums, room_nums + num_components, myfn);
    fout << largest << endl;
    int combined_largest = 0;
    int current_combined_size = 0;
    int I;
    int J;
    char direction;

    for (int i = 0; i < M; ++i) {
        for (int j = N-1; j > -1; --j) {
            // north
            if ((j != 0) && (edges[2*(j-1)+1][i] == 0) && (components[j][i] != components[j-1][i])) {
                current_combined_size = room_nums[components[j][i]] + room_nums[components[j-1][i]];
                if ( current_combined_size >  combined_largest) {
                    combined_largest = current_combined_size;
                    I = (i+1);
                    J = (j+1);
                    direction = 'N';
                }
            }
            //east
            if ( (i != M-1) && (edges[2*j][i] == 0) && (components[j][i] != components[j][i+1])) {
                current_combined_size = room_nums[components[j][i]] + room_nums[components[j][i+1]];
                if ( current_combined_size >  combined_largest) {
                    combined_largest = current_combined_size;
                    I = (i+1);
                    J = (j+1);
                    direction = 'E';
                }
            }
        }
    }
    fout << combined_largest << endl;
    fout << J << ' ' << I << ' ' << direction << endl;
    fout.close();
    
    return 0;
}











