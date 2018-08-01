//
//  main.cpp
//  buylow
//
//  Created by TFAN on 2018/7/22.
//  Copyright © 2018年 TFAN. All rights reserved.
//



/*
 ID: tfan0328
 PROG: buylow
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>


using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 5000;
int prices[MAXN] = {};
int dp1[MAXN] = {};
int const C = 100;
int const base = 10;
int dp2[MAXN][C] = {};

// 1 num1 < num2
// -1 num1 > num2
int compare (int num1[C], int num2[C]) {
    if (num1[C-1] < num2[C-1]) {
        return 1;
    }
    else if (num1[C-1] > num2[C-1]) {
        return -1;
    }
    else {
        for (int i = max(num1[C-2], num2[C-2])-1; i >= 0; --i) {
            if (num1[i] > num2[i]) {
                if (num1[C-1] == 1) {
                    return 1;
                }
                else {
                    return -1;
                }
            }
        }
        return 0;
    }
}

void absolute_subtract(int num1[C], int num2[C], int num3[C]) {
    int borrow = 0;
    for (int i = 0; i < max(num1[C-2], num2[C-2]); ++i) {
        num3[i] = num1[i] - num2[i] - borrow;
        if (num3[i] < 0) {
            num3[i] = num3[i] + base;
            borrow = 1;
        }
        else
            borrow = 0;
        if (num3[i] != 0) {
            num3[C-2] = i+1;
        }
    }

}

void absolute_add(int num1[C], int num2[C], int num3[C]) {
    int carry = 0;
    for (int i = 0; i < max(num1[C-2], num2[C-2]); ++i) {
        num3[i] = num1[i] + num2[i] + carry;
        carry = num3[i]/base;
        num3[i] = num3[i] % base;
    }
    if (carry != 0) {
        num3[max(num1[C-2], num2[C-2])] = carry;
        num3[C-2] = max(num1[C-2], num2[C-2])+1;
    }
    else {
        num3[C-2] = max(num1[C-2], num2[C-2]);
    }
}

void add(int num1[C], int num2[C], int num3[C]) {
    if (num1[C-1] == num2[C-1]) {
        absolute_add(num1, num2, num3);
        num3[C-1] = num1[C-1];
    }
    else {
        int comp = compare(num1, num2);
        if (comp == -1) {
            absolute_subtract(num1, num2, num3);
            num3[C-1] = num1[C-1];
        }
        else if (comp == 1){
            absolute_subtract(num2, num1, num3);
            num3[C-1] = num2[C-1];
        }
        else {
            num3[C-1] = 0;
            for (int k = 0; k < num3[C-2]; ++k) {
                num3[k] = 0;
            }
            num3[C-2] = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("buylow.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> prices[i];
    }
    for (int i = 0; i < N; ++i) {
        dp1[i] = 1;
        dp2[i][0] = 1;
        dp2[i][C-1] = 1;
        dp2[i][C-2] = 1;
        
        for (int j = 0; j < i; ++j) {
            if (prices[j] == prices[i]) {
                dp2[i][0] = 0;
                dp2[i][C-1] = 0;
                dp2[i][C-2] = 0;
            }
        }
    }
    

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (prices[i] < prices[j]) {
                dp1[i] = max(dp1[i], dp1[j]+1);
            }
        }
        bool check = false;
        int tmp = dp2[i][C-2];
        for (int j = 0; j < i; ++j) {
            if (prices[i] < prices[j] && dp1[i] == dp1[j]+1) {
                int arr1[C];
                copy(dp2[i], dp2[i]+C, arr1);
                add(arr1, dp2[j], dp2[i]);
                //dp2[i] += dp2[j];
                check = true;
            }
          
        }
        if (i == 104) {
            for (int k = dp2[i][C-2]-1; k >= 0; --k) {
                cout << dp2[i][k];
            }
            cout << endl;
        }
        
        if (dp2[i][C-2] > 0) {
            for (int j = 0; j < i; ++j) {
                if (prices[i] == prices[j] && dp1[i] == dp1[j]) {
                    int arr2[C];
                    copy(dp2[j], dp2[j]+C, arr2);
                    arr2[C-1] = -1;
                    int arr1[C];
                    copy(dp2[i], dp2[i]+C, arr1);
                    add(arr1, arr2, dp2[i]);
                    //dp2[i] -= dp2[j];
                }
            }
        }
        
        if (i == 104) {
            for (int k = dp2[i][C-2]-1; k >= 0; --k) {
                cout << dp2[i][k];
            }
            cout << endl;
        }
        
        if (check && tmp != 0) {
            int arr2[C] = {};
            arr2[C-1] = -1;
            arr2[0] = 1;
            arr2[C-2] = 1;
            int arr1[C];
            copy(dp2[i], dp2[i]+C, arr1);
            add(arr1, arr2, dp2[i]);
            //dp2[i]--;
        }
        
        if (i == 104) {
            for (int k = dp2[i][C-2]-1; k >= 0; --k) {
                cout << dp2[i][k];
            }
            cout << endl;
        }
//        cout << i << ' ' << prices[i] << ' ' << dp1[i] << ' ';
//        cout << '(' << dp2[i][C-1] << ')';
//        for (int k = dp2[i][C-2]-1; k >= 0; --k) {
//            cout << dp2[i][k];
//        }
//        cout << endl;
    }
    
    int a = 0;
    int b[C] = {};
    for (int i = 0; i < N; ++i) {
        if (a < dp1[i]) {
            a = dp1[i];
        }
    }
    
    for (int i = 0; i < N; ++i) {
        if (a == dp1[i]) {
            int arr1[C];
            copy(b, b+C, arr1);
            add(arr1, dp2[i], b);
            //b += dp2[i];
        }
    }
    
    ofstream fout ("buylow.out");
    fout << a << ' ';
    for (int i = b[C-2]-1; i >= 0; --i) {
        fout << b[i];
    }
    fout << endl;
    fout.close();
    return 0;
}































