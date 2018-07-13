//
//  main.cpp
//  transform
//
//  Created by TFAN on 2017/9/6.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: transform
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

char ** rotation90(char ** input, int n) {
    char ** result;
    result = new char * [n];
    for (int i = 0; i < n; ++i) {
        result[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = input[-j+n-1][i];
        }
    }
    return result;
}

char ** rotation180(char ** input, int n) {
    char ** result;
    result = new char * [n];
    for (int i = 0; i < n; ++i) {
        result[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = input[-i+n-1][-j+n-1];
        }
    }
    return result;

}

char ** rotation270(char ** input, int n) {
    char ** result;
    result = new char * [n];
    for (int i = 0; i < n; ++i) {
        result[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = input[j][-i+n-1];
        }
    }
    return result;

}

char ** reflection(char ** input, int n) {
    char ** result;
    result = new char * [n];
    for (int i = 0; i < n; ++i) {
        result[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = input[i][-j+n-1];
        }
    }
    return result;
}

bool same(char ** input, char ** result, int n) {
    bool s = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (result[i][j] != input[i][j]) {
                s = 0;
            }
        }
    }
    return s;
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    int n = 0;
    fin >> n;
    
    char ** input;
    input = new char * [n];
    for (int i = 0; i < n; ++i) {
        input[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            fin >> input[i][j];
        }
    }
    
    char ** input2;
    input2 = new char * [n];
    for (int i = 0; i < n; ++i) {
        input2[i] = new char [n];
        for (int j = 0; j < n; ++j) {
            fin >> input2[i][j];
        }
    }

    
    char ** result;
    result = reflection(input, n);
    
    if (same(input2, rotation90(input, n), n)) {
        fout << 1 << endl;
    }
    else if (same(input2, rotation180(input, n), n)) {
        fout << 2 << endl;
    }
    else if (same(input2, rotation270(input, n), n)) {
        fout << 3 << endl;
    }
    else if (same(input2, result, n)) {
        fout << 4 << endl;
    }
    else if (same(input2, rotation90(result, n), n)) {
        fout << 5 << endl;
    }
    else if (same(input2, rotation180(result, n), n)) {
        fout << 5 << endl;
    }
    else if (same(input2, rotation270(result, n), n)) {
        fout << 5 << endl;
    }
    else if (same(input2, input, n)) {
        fout << 6 << endl;
    }
    
    else {
        fout << 7 << endl;
    }

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << result[i][j];
        }
        cout << endl;
    }
     */
    //std::cout << "Hello, World!\n";
    return 0;
}
