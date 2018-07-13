//
//  main.cpp
//  transform
//
//  Created by TFAN on 2017/9/6.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: namenum
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int a, char b) {
    int c = int(b) -65;
    if (b == 'Q' || b == 'Z') {
        return false;
    }
    if (c > 17) {
        c = c-1;
    }
    if ( ((c - (c % 3))/3) == (a-2)) {
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream dict;
    dict.open("dict.txt");
    string current;
    long long n;
    fin >> n;

    vector<int> m;
    while(n != 0) {
        m.push_back(n % 10);
        n = (n - (n % 10))/10;
    }

    int count = 0;
    if (dict.is_open())
    {
        while (getline(dict,current))
        {
            bool output = true;
            if (current.length() != m.size()) {
                output = false;
            }
            else {
                for (int i = 0; i < m.size(); ++i) {
                    if (! check( m[m.size() - i -1] , current[i])) {
                        output = false;
                        break;
                    }
                }
            }
            if (output) {
                fout << current << endl;
                ++ count;
            }
        }
        if (count == 0) fout << "NONE" << endl;
        dict.close();
    }

    return 0;
}
