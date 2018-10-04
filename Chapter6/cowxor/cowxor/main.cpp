//
//  main.cpp
//  cowxor
//
//  Created by TFAN on 2018/8/21.
//  Copyright © 2018年 TFAN. All rights reserved.
//




/*
 ID: tfan0328
 PROG: cowxor
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
//#include <algorithm>
//#include <math.h>
//#include <iomanip>



using namespace std;
//const int infty = 0x7fffffff;
int N;

struct node {
    int id;
    int next[2];
};
const int num = 2097152;

node trie[500000];
int cnt = 1;
int sum[100001] = {};

void insert(int sum, int cur_id) {
    int pos = 1;
    for (int i = 20; i >= 0; --i) {
        int i_digit = (sum>>i)&1;
        if (trie[pos].next[i_digit] == 0) {
            cnt ++;
            trie[pos].next[i_digit] = cnt;
            pos = cnt;
            trie[pos].id = 0;
        }
        else {
            pos = trie[pos].next[i_digit];
        }
    }
    trie[pos].id = cur_id;
}


int search(int input) {
    int pos = 1;
    for (int i = 20; i >= 0; --i) {
        int i_digit = (input>>i)&1;
        if (trie[pos].next[i_digit^1] == 0) {
            pos = trie[pos].next[i_digit];
        }
        else {
            pos = trie[pos].next[i_digit^1];
        }
    }
    return trie[pos].id;
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin("cowxor.in");
    
    fin >> N;
    insert(0, 0);
    int cur = 0;
    int ans = 0;
    int start_pos = 1;
    int end_pos = 1;
    
    for (int i = 1; i <= N; ++i) {
        fin >> cur;
        sum[i] = sum[i-1]^cur;
        insert(sum[i], i);
        int cur_id = search(sum[i]);
        if ( (sum[cur_id]^sum[i]) > ans) {
            ans = sum[cur_id]^sum[i];
            start_pos = cur_id+1;
            end_pos = i;
        }
    }
    
    
    
    ofstream fout("cowxor.out");
    
    fout << ans << ' ' << start_pos << ' ' << end_pos << endl;
    
    
    return 0;
}






























































