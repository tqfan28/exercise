//
//  main.cpp
//  cryptcow
//
//  Created by TFAN on 2018/9/25.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: cryptcow
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
//#include <stdio.h>
//#include <ctype.h>
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
string original = "Begin the Escape execution at the Break of Dawn";
string message;
const unsigned long hash_size = 999991;
int dp[hash_size] = {};
const int MAXR = 76;
//131071

unsigned long elf_hash(string str) {
    unsigned long h = 0;
    for (int i = 0; i < str.length(); i++) {
        h = (h << 4) + str[i];
        unsigned long g = h & 0xf0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h % hash_size;
}

string decoder(int posC, int posO, int posW, string s) {
    string result = s.substr(0, posC);
    result += s.substr(posO+1, posW-posO-1);
    result += s.substr(posC+1, posO-posC-1);
    if (posW+1 < s.size()) {
        result += s.substr(posW+1, s.size()-posW-1);
    }
    return result;
}

bool notin(char c) {
    for (int i = 0; i < original.size(); ++i) {
        if (c == original[i])
            return false;
    }
    return true;
}

bool check(string s) {
    if (s.size() == original.size()) {
        //cout << s << endl;
        if (s == original) {
            return true;
        }
        return false;
    }
    
    if ( (s.size() - original.size()) % 3 != 0 ) {
        return false;
    }
    
    unsigned long hash_value = elf_hash(s);
    if (dp[hash_value] != -1) {
        return dp[hash_value];
    }
    
    
    for (int i = 0; i < s.size(); i++) {
        if(s[i]=='C') break;
        if(s[i] != original[i]) {
            dp[hash_value] = 0;
            return false;
        }
        if(s[i] == 'W' || s[i]=='O') {
            dp[hash_value] = 0;
            return false;
        }
    }
    int tail = original.size()-1;
    for (int i = s.size()-1; i >= 0; i--) {
        if (s[i]=='W') break;
        if (s[i] != original[tail--]) {
            dp[hash_value] = 0;
            return false;
        }
        if (s[i]=='C' || s[i]=='O') {
            dp[hash_value] = 0;
            return false;
        }
    }
    
    int Cs[MAXR] = {};
    int cnt_C = 0;
    int Os[MAXR] = {};
    int cnt_O = 0;
    int Ws[MAXR] = {};
    int cnt_W = 0;
    int stops[80] = {};
    int cnt = 0;
    
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'C') {
            Cs[cnt_C] = i;
            stops[cnt] = i;
            cnt ++;
            cnt_C ++;
        }
        else if (s[i] == 'O') {
            Os[cnt_O] = i;
            stops[cnt] = i;
            cnt ++;
            cnt_O ++;
        }
        else if (s[i] == 'W') {
            Ws[cnt_W] = i;
            stops[cnt] = i;
            cnt ++;
            cnt_W ++;
        }
    }
    
    stops[cnt++] = s.length();
    
    for (int i = 0; i < cnt-1; i++) {
        if( stops[i]+1 < stops[i+1]){
            string sub = s.substr(stops[i]+1, stops[i+1]-1-stops[i]);
            if( original.find(sub) == string::npos){
                dp[hash_value] = 0;
                return false;
            }
        }
    }
    
    if (! (cnt_C == cnt_O && cnt_O == cnt_W && cnt_W == cnt_C) ) {
        dp[hash_value] = 0;
        return false;
    }
    
    
    for (int i = 0; i < cnt_C; ++i) {
        for (int j = 0; j < cnt_O; ++j) {
            for (int k = 0; k < cnt_W; ++k) {
                if (Cs[i] < Os[j] && Os[j] < Ws[k]) {
                    if ( check(decoder(Cs[i], Os[j], Ws[k], s))) {
                        dp[hash_value] = 1;
                        return true;
                    }
                }
            }
        }
    }
    
    dp[hash_value] = 0;
    return false;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("cryptcow.in");
    
    getline(fin, message);
    
    fin.close();
    
    for (int i = 0; i < hash_size; ++i) {
        dp[i] = -1;
    }
    
    ofstream fout;
    fout.open("cryptcow.out");
    
    if (check(message)) {
        fout << 1 << ' ';
        int times = 0;
        for (int i = 0; i < message.size(); ++i) {
            if (message[i] == 'C') {
                times ++;
            }
        }
        fout << times << endl;
    }
    
    else {
        fout << 0 << ' ' << 0 << endl;
    }
    fout.close();
    
    return 0;
}

































































