//
//  main.cpp
//  calfflac
//
//  Created by TFAN on 2018/9/20.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: calfflac
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
#include <string>
#include <stdio.h>
#include <ctype.h>
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
string chars;
int len;

int left_char(int mid) {
    if (mid <= 0)
        return -1;
    int left = mid-1;
    while(left >= 0 && !isalpha(chars[left])) {
        left --;
    }
    return left;
}

int right_char(int mid) {
    if (mid >= len-1) {
        cout << len << endl;
        return len;
    }
    int right = mid+1;
    while(right < len && !isalpha(chars[right])) {
        right ++;
    }
    return right;
}

int palindromes_even(int start, int & l, int & r) {
    int even_len = 0;
    int right = right_char(start);
    int left = start;
    while(right < len && left > -1) {
        if (toupper(chars[left]) == toupper(chars[right])) {
            even_len ++;
            right = right_char(right);
            left = left_char(left);
        }
        else {
            break;
        }
    }
    l = right_char(left);
    r = left_char(right);
    return even_len*2;
}

int palindromes_odd(int start, int & l, int & r) {
    int odd_len = 0;
    int right = right_char(start);
    int left = left_char(start);
    while(right < len && left > -1) {
        if (toupper(chars[left]) == toupper(chars[right])) {
            odd_len ++;
            right = right_char(right);
            left = left_char(left);
        }
        else {
            break;
        }
    }
    l = right_char(left);
    r = left_char(right);
    return odd_len*2 + 1;
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("calfflac.in");
    string line;
    while(getline(fin, line)) {
        chars = chars + line;
        chars = chars + "\n";
    }
    fin.close();

    
    len = chars.size();
    int ans = 0;
    int l = 0;
    int r = 0;
    int tmp = 0;
    int ansl = 0;
    int ansr = 0;
    for (int i = 0; i < len; ++i) {
        if (isalpha(chars[i])) {
            tmp = palindromes_even(i, l, r);
            if (ans < tmp) {
                ans = tmp;
                ansl = l;
                ansr = r;
            }
            tmp = palindromes_odd(i, l, r);
            if (ans < tmp) {
                ans = tmp;
                ansl = l;
                ansr = r;
            }
        }
    }
    
    ofstream fout;
    fout.open("calfflac.out");
    
    fout << ans << endl;
    for (int i = ansl; i <= ansr; ++i) {
        fout << chars[i];
    }
    fout << endl;
    
    fout.close();
    
    return 0;
}




























































