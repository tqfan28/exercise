//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: holstein
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int V;
const int MAXV = 25;
int Vitamins[MAXV] = {};
int G;
const int MAXG = 15;
int Feeds[MAXG][MAXV] = {};
int zero_one[MAXG] = {};
int optimal[MAXG] = {};

struct node {
    int state;
    int level;
    bool feasible;
    node * left;
    node * right;
};

struct node* newNode(int data, int level)
{
    struct node* temp = (struct node*) malloc(sizeof( struct node ));
    temp->state = data;
    temp->level = level;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void prune (node * root, int * path, int path_length) {
    path[path_length+1] = root->state;
    bool did_break = false;
    int v = 0;
    for (int j = 0; j < V; ++j) {
        v = 0;
        for (int i = 0; i < path_length+2; ++i) {
            v += (path[i]*Feeds[i][j]);
            //cout << Feeds[i][j]<< endl;
        }
        //cout << 'v' << v << endl;
        if (v < Vitamins[j]) {
            did_break = true;
            break;
        }
        if (did_break)
            break;
    }
    if (!did_break) {
        root->feasible = true;
        root->left = NULL;
        root->right = NULL;
    }
    else if (root->left != NULL) {
        root->feasible = false;
        prune(root->left, path, path_length+1);
        prune(root->right, path, path_length+1);
    }
    else {
        root->feasible = false;
    }
}

int dfs(node* root, int* path, int path_length) {
    //cout << path_length << ' ' << root->state << endl;
    path[path_length+1] = root->state;
    if (root->left == NULL) {
        if (root->feasible == true){
            return (root->state);
        }
        else
            return (G+1);
    }
    else {
        int temp[MAXG] = {};
        int left = dfs (root->left, path, path_length+1);
        copy(optimal, optimal+G, temp);
        int right = dfs(root->right, path, path_length+1);
        if (right <= left) {
            //cout << "left"<< left << "right" << right << endl;
            optimal[path_length+2] = 1;
        }
        else {
            copy(temp, temp+G, optimal);
            optimal[path_length+2] = 0;
        }
        return (min(left, right) + root->state);
    }
}

void Create_tree (node* root, int depth, int prev_level) {
    if (depth == 0)
        return;
    else {
        node* one = newNode(1, prev_level+1);
        node* zero = newNode(0, prev_level+1);
        root->left = zero;
        root->right = one;
        Create_tree(zero, depth-1, prev_level+1);
        Create_tree(one, depth-1, prev_level+1);
    }
}

//BFS
void print_tree(node*root) {
    queue<node*> line;
    line.push(root);
    int level = 0;
    while (!line.empty()) {
        if ((line.front())->level != level) {
            cout << endl;
            level = (line.front())->level;
        }
        cout << (line.front())->state << ' ';
        //cout << "level" << (line.front())->level << ' ';
        cout << "feasible" << (line.front())->feasible << ' ';

        if ((line.front())->left != NULL)
            line.push((line.front())->left);
        if ((line.front())->right != NULL)
            line.push((line.front())->right);
        line.pop();
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("holstein.in");
    
    fin >> V;
    for (int i = 0; i < V; ++i) {
        fin >> Vitamins[i];
    }

    fin >> G;
    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < V; ++j) {
            fin >> Feeds[i][j];
        }
    }
    
    struct node* root = newNode(-1, -1);
    Create_tree(root, G, -1);
    prune(root->left, zero_one, -1);
    //print_tree(root->left);
    prune(root->right, zero_one, -1);
    //print_tree(root->right);
    
    int a = dfs(root->left, zero_one, -1);
    
    int temp [MAXG] = {};
    copy(optimal, optimal + G, temp);
    
    int b = dfs(root->right, zero_one, -1);
    optimal[0] = 1;
    if (a < b) {
        b = a;
        copy(temp, temp + G, optimal);
        optimal[0] = 0;
    }
//    for (int i = 0; i < G; ++i) {
//        cout << optimal[i]<< endl;
//    }

    
    ofstream fout ("holstein.out");
    fout << b <<' ';
    if (G == 1)
        fout << 1;
    else {
        int counter = 0;
        for (int i = 0; i < G; ++i) {
            //cout << optimal[i]<< endl;
            if (optimal[i] && b == 1) {
                fout << i+1;
                break;
            }
            else if (optimal[i] && counter < b-1) {
                fout << i+1 << ' ';
                counter++;
            }
            else if (optimal[i]) {
                fout << i+1;
                break;
            }
        }
    }
    fout << endl;
    fout.close();
    
    return 0;
}














