//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: numtri
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int R;
const int height = 1000;
int ourArray[height][height];
int dpArray[height][height];

//struct node {
//    int data;
//    struct node* left;
//    struct node* right;
//};
//
//struct node* newNode(int data) {
//    struct node* node = (struct node*)malloc(sizeof(struct node));
//    node->data = data;
//    node->left = NULL;
//    node->right = NULL;
//    return node;
//}

int DFS (int i, int j) {
    if (dpArray[i][j] != -1) {
        return dpArray[i][j];
    }
    else if (i != R-1) {
        return  dpArray[i][j] = ourArray[i][j] + max( DFS(i+1, j), DFS(i+1, j+1));
    }
    else
        return dpArray[i][j] = ourArray[i][j];
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin ("numtri.in");
    fin >> R;
    memset (dpArray, -1 , sizeof dpArray);
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j <= i; ++j) {
            fin >> ourArray[i][j];
        }
    }
    
    ofstream fout ("numtri.out");
    fout << DFS(0, 0) << endl;
    fout.close();
    
    return 0;
}










