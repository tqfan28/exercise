//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: prefix
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
string S;
string primitives;
int len = 0;
bool visited[300000] = {};


//int prefix(int start) {
//
//    int result = start;
//    if (start == primitives.length())
//        return result;
//
//    for (int i = 0; i < primitives.length(); ++i) {
//        int current = start;
//        bool did_break = false;
//        if (primitives[i] == ' ')
//            continue;
//        while (primitives[i] != ' ' && i < primitives.length()) {
//            if (current >= S.length() || primitives[i] != S[current]) {
//                did_break = true;
//            }
//            i++;
//            current++;
//        }
//        if (!did_break) {
//            if (state[current])
//                return len;
//            else
//                result = max(result, prefix(current));
//        }
//    }
//
//    state[start] = true;
//    len = max(len, result);
//    return result;
//}

//int prefix_v1(int start) {
//
//    int result = start;
//    if (start == primitives.length())
//        return result;
//
//    for (int i = 0; i < primitives.length(); ++i) {
//        int current = start;
//        bool did_break = false;
//        if (primitives[i] == ' ')
//            continue;
//        while (primitives[i] != ' ' && i < primitives.length()) {
//            if (current >= S.length() || primitives[i] != S[current]) {
//                did_break = true;
//            }
//            i++;
//            current++;
//        }
//        if (!did_break) {
//            result = max(result, prefix_v1(current));
//        }
//    }
//    return result;
//}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("prefix.in");
    if (!fin) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    string current;
    getline(fin, primitives);
    getline(fin, current);
    while (current != ".") {
        primitives = primitives + " " + current;
        getline(fin, current);
    }
    while(getline(fin, current)) {
        S = S + current;
    }

    
    queue<int> lines;
    
    for (int i = 0; i < primitives.length(); ++i) {
        int start = 0;
        bool did_break = false;
        while (primitives[i] != ' ' && i < primitives.length()) {
            if (start >= S.length() || primitives[i] != S[start]) {
                    did_break = true;
                }
                i++;
                start++;
        }
        if (!did_break) {
            visited[start] = true;
            lines.push(start);
            len = max(len, start);
        }
    }

    while(!lines.empty()) {
        int start = lines.front();
        lines.pop();
        for (int i = 0; i < primitives.length(); ++i) {
            int tmp = start;
            bool did_break = false;
            while (primitives[i] != ' ' && i < primitives.length()) {
                if ( tmp >= S.length() || primitives[i] != S[tmp]) {
                    did_break = true;
                }
                i++;
                tmp++;
            }
            if (!did_break && !visited[tmp]) {
                lines.push(tmp);
                visited[tmp] = true;
                len = max(len, tmp);
            }
        }
    }
    
    ofstream fout ("prefix.out");
    fout << len << endl;
    fout.close();

    return 0;
}




















