//
//  main.cpp
//  hidden
//
//  Created by TFAN on 2018/8/14.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: hidden
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
int L;

struct achar {
    char c;
    int id;
    bool operator<(const achar & rhs) const{
        return ((c < rhs.c) || (c == rhs.c && id < rhs.id) );
    }
};
const int MAXL = 100000;
char input[MAXL];
achar current[MAXL];
achar Next[MAXL];
int len;

void computeLen(achar* arr) {
    if (len < 1) {
        return;
    }
    for (int i = 0; i < len-1; ++i) {
        if (arr[i+1].c != arr[i].c) {
            len = i+1;
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("hidden.in");
    
    fin >> L;
    len = L;
    
    for (int i = 0; i < L; ++i) {
        fin >> input[i];
        current[i].c = input[i];
        current[i].id = i;
    }
    
    fin.close();
    
    sort(current, current+len);
    computeLen(current);
    int cnt = 1;
    
    while(cnt != L && len > 1) {
        
        for (int i = 0; i < len; ++i) {
            Next[i].c = input[ (current[i].id+cnt) % L];
            Next[i].id = current[i].id;
        }
        sort(Next, Next+len);
        computeLen(Next);
        for (int i = 0; i < len; ++i) {
            current[i] = Next[i];
        }
        cnt ++;
        cout << cnt << endl;
    }
    
    
    ofstream fout;
    fout.open("hidden.out");
    
    cout << current[0].id << endl;
    
    fout.close();
    
    return 0;
}





















































