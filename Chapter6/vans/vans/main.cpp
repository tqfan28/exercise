//
//  main.cpp
//  vans
//
//  Created by TFAN on 2018/8/19.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: vans
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
const int M = 4;
int N;
const int MAXN = 1000;
const int C = 500;
const int base = 10;


//naive search, too slow

//const int diff[8] = {-1, 0, 0, 1, 1, 0, 0, -1};
//bool visited[M][MAXN] = {};
//
//bool check(int i, int j) {
//    return (j >= 0 && j < N && i >=0 && i < M);
//}
//
//int sol = 0;
//
//void dfs(int cnt, int curi, int curj) {
//
//    if (cnt == M*N) {
//        if ( (curi == 0 && curj == 1) || (curi == 1 && curj == 0) )
//            sol ++;
//    }
//
//    for (int i = 0; i < 8; i = i+2) {
//
//        int nexti = curi+diff[i];
//        int nextj = curj+diff[i+1];
//
//        if (!visited[nexti][nextj] && check(nexti, nextj)) {
//            visited[nexti][nextj] = true;
//            //printV();
//            dfs(cnt+1, nexti, nextj);
//            visited[nexti][nextj] = false;
//        }
//    }
//}

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

//here num3 cannot be num1
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
    
    
    ifstream fin;
    fin.open("vans.in");
    
    fin >> N;
    
    fin.close();
    
//    visited[0][0] = true;
//    dfs(1, 0, 0);
    
    int f[MAXN+1][C] = {};
    int g[MAXN+1][C] = {};
    
    f[1][0] = 0;
    f[1][C-1] = 1;
    f[1][C-2] = 1;
    f[2][0] = 1;
    f[2][C-1] = 1;
    f[2][C-2] = 1;
    f[3][0] = 2;
    f[3][C-1] = 1;
    f[3][C-2] = 1;
    
    g[1][0] = 1;
    g[1][C-1] = 1;
    g[1][C-2] = 1;
    g[2][0] = 1;
    g[2][C-1] = 1;
    g[2][C-2] = 1;
    g[3][0] = 4;
    g[3][C-1] = 1;
    g[3][C-2] = 1;
    

    
    
    for (int i = 4; i <= N; ++i) {
        add(f[i-1], g[i-1], f[i]);
        add(f[i-1], f[i-1], g[i]);
        add(g[i], g[i-1], g[i]);
        add(g[i], g[i-2], g[i]);
        g[i-3][C-1] = -1;
        int tmp[C];
        copy(g[i], g[i]+C, tmp);
        add(tmp, g[i-3], g[i]);
        g[i-3][C-1] = 1;
    }


    // f[i] = f[i-1]+g[i-1]
    // g[i] = f[i-1]*2 + g[i-1] + g[i-2] - g[i-3]
    add(f[N], f[N], f[N]);
    
    ofstream fout;
    fout.open("vans.out");

    for (int i = f[N][C-2]-1; i >= 0; --i) {
        fout << f[N][i];
    }
    fout << endl;
    fout.close();
    
    return 0;
}



























































