//
//  main.cpp
//  prime3_v2
//
//  Created by TFAN on 2018/9/27.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: prime3
 LANG: C++
 */

#include <iostream>
#include <fstream>
//#include <cstring>
//#include <string>
//#include <stdio.h>
//#include <ctype.h>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <list>
//#include <map>
#include <algorithm>
//#include <math.h>
//#include <iomanip>

using namespace std;
int sum;
int ul;
int cnt = 0;
int primes[5000] = {};
int digits[5000][5] = {};
bool is_valid[100000] = {};
int board[5][5] = {};
ofstream fout;
int ans = 0;

struct num {
    int val1;
    int val2;
    int val3;
    int val4;
    int val5;
    bool operator<(const num & rhs) const {
        return (
                val1 < rhs.val1
                || (val1 == rhs.val1 && val2 < rhs.val2)
                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 < rhs.val3)
                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 == rhs.val3 && val4 < rhs.val4)
                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 == rhs.val3 && val4 == rhs.val4 && val5 < rhs.val5)
                );
    }
};

num saved[200];

bool is_prime(int n) {
    if (n <= 1)
        return false;
    else if (n <= 3)
        return true;
    else if (n % 2 == 0 || n % 3 == 0)
        return false;
    int i = 5;
    while(i*i <= n) {
        if (n % i == 0 || n % (i+2) == 0) {
            return false;
        }
        i = i +6;
    }
    return true;
}

bool check_sum(int n) {
    int result = 0;
    for (int i = 0; i < 5; ++i) {
        result += (n % 10);
        n = (n - n % 10)/10;
    }
    if (result == sum)
        return true;
    else
        return false;
}

int get_digit(int n, int t) {
    int result = 0;
    for (int i = 0; i < t; ++i) {
        result = n % 10;
        n = (n - (n % 10))/10;
    }
    return result;
}

void generate_primes() {
    for (int i = 10000; i < 100000; ++i) {
        if (is_prime(i) && check_sum(i)) {
            is_valid[i] = true;
            primes[cnt] = i;
            // 0 1 2 3 4
            // 1 1 3 5 1
            for (int j = 0; j < 5; ++j) {
                digits[cnt][j] = get_digit(i, 5-j);
            }
            cnt ++;
        }
    }
}

void init() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = -1;
        }
    }
    board[0][0] = ul;
    generate_primes();
}


bool row1col1(int id) {
    if (digits[id][0] != ul)
        return false;
    for (int i = 1; i < 5; ++i) {
        if (digits[id][i] == 0) {
            return false;
        }
    }
    return true;
}

void setrow(int n, int id) {
    for (int i = 0; i < 5; ++i) {
        board[n-1][i] = digits[id][i];
    }
}

void setcol(int n, int id) {
    for (int i = 0; i < 5; ++i) {
        board[i][n-1] = digits[id][i];
    }
}

//int filrow(int i, int j) {
//    int res = 0;
//    for (int k = 0; k < 5; ++k) {
//        if (k != j) {
//            res += board[i][k];
//        }
//    }
//    board[i][j] = sum - res;
//    return board[i][j];
//}

int readcol(int i) {
    return board[0][i]*10000 + board[1][i]*1000 + board[2][i]* 100 + board[3][i]*10 + board[4][i];
}

int readrow(int i) {
    return board[i][0]*10000 + board[i][1]*1000 + board[i][2]* 100 + board[i][3]*10 + board[i][4];
}

//int filcol(int i, int j) {
//    int res = 0;
//    for (int k = 0; k < 5; ++k) {
//        if (k != i) {
//            res += board[k][j];
//        }
//    }
//    board[i][j] = sum - res;
//    return board[i][j];
//}

void save() {
    saved[ans].val1 = readrow(0);
    saved[ans].val2 = readrow(1);
    saved[ans].val3 = readrow(2);
    saved[ans].val4 = readrow(3);
    saved[ans].val5 = readrow(4);
    ans ++;
}

// too slow

//void search() {
//    for (int i0 = 0; i0 < cnt; ++i0) {
//        if (row1col1(i0)) {
//            setrow(1, i0);
//            for (int i1 = 0; i1 < cnt; ++i1) {
//                if (row1col1(i1)) {
//                    setcol(1, i1);
//                    for (int i2 = 0; i2 < cnt; ++i2) {
//                        if (digits[i2][0] == ul)  {
//                            for (int j = 0; j < 5; ++j) {
//                                board[j][j] = digits[i2][j];
//                            }
//                            for (int i3 = 0; i3 < cnt; ++i3) {
//                                if (digits[i3][0] == board[4][0]
//                                    && digits[i3][2] == board[2][2]
//                                    && digits[i3][4] == board[0][4]
//                                    ) {
//                                    board[3][1] = digits[i3][1];
//                                    board[1][3] = digits[i3][3];
//                                    if ( (board[1][0]+ board[1][1]+board[1][3] <= sum)
//                                        && (board[3][0]+ board[3][1]+board[3][3] <= sum)
//                                        ) {
//                                        for (int i4 = 0; i4 < cnt; ++i4) {
//                                            if (digits[i4][0] == board[4][0]
//                                                && digits[i4][4] == board[4][4]
//                                                ) {
//                                                board[4][1] = digits[i4][1];
//                                                board[4][2] = digits[i4][2];
//                                                board[4][3] = digits[i4][3];
//
//                                                filcol(2, 1);
//                                                int col2 = readcol(1);
//                                                if (
//                                                    is_valid[col2]
//                                                    && board[4][1] % 2 != 0
//                                                    && board[4][2] % 2 != 0
//                                                    && board[4][3] % 2 != 0
//                                                    ) {
//                                                    filcol(2, 3);
//                                                    int col4 = readcol(3);
//                                                    if (is_valid[col4]) {
//                                                        filrow(2, 4);
//                                                        int row3 = readrow(2);
//                                                        if (is_valid[row3]
//                                                            && (board[0][2]+ board[2][2]+board[4][2] <= sum)
//                                                            ) {
//                                                            for (int i5 = 0; i5 < cnt; ++i5) {
//                                                                if (digits[i5][0] == board[0][4]
//                                                                    && digits[i5][2] == board[2][4]
//                                                                    && digits[i5][4] == board[4][4]
//                                                                    ) {
//                                                                    board[1][4] = digits[i5][1];
//                                                                    board[3][4] = digits[i5][3];
//
//                                                                    filrow(1,2);
//                                                                    filrow(3, 2);
//
//                                                                    int row2 = readrow(1);
//                                                                    int row4 = readrow(3);
//                                                                    int col3 = readcol(2);
//
//                                                                    if (is_valid[row2] && is_valid[row4] && is_valid[col3]) {
//                                                                        save();
//                                                                    }
//                                                                }
//                                                            }
//                                                        }
//                                                    }
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}

bool row5(int id) {
    if (digits[id][0] != board[4][0]) {
        return false;
    }
    
    for (int i = 1; i <= 3;  ++i) {
        if (digits[id][i] % 2 == 0 || digits[id][i] == 5) {
            return false;
        }
    }
    return true;
}

bool col5(int id) {
    if (digits[id][0] != board[0][4] || digits[id][4] != board[4][4]) {
        return false;
    }
    for (int i = 1; i <= 3;  ++i) {
        if (digits[id][i] % 2 == 0 || digits[id][i] == 5) {
            return false;
        }
    }
    return true;
}

bool solver(int & a33, int & a31, int & a21, int & a22, int & a23, int & a32) {

    
    int c1 = sum - (board[0][1] + board[1][1] + board[4][1]);
    int c2 = sum - (board[0][2] + board[1][2] + board[4][2]);
    int c3 = sum - (board[0][3] + board[1][3] + board[4][3]);
    int c4 = sum - (board[2][0] + board[2][4]);
    int c5 = sum - (board[3][0] + board[3][4]);
    
    int c6 = sum - (board[0][0] + board[1][1] + board[4][4]);

    if (c1 != (c4 + c5 - c2 - c3))
        return false;
    
    int c7 = sum - (board[4][0] + board[1][3] + board[0][4]);
    
    if (c1 < 0 || c2 < 0 || c3 < 0 || c4 < 0 || c5 < 0 || c6 < 0 || c7 < 0)
        return false;
    
    a33 = c5 - c2 + 2*c6 -c7;
    if (a33 % 3 != 0 || a33 < 0) {
        return false;
    }
    a33 = a33/3;
    a31 = c7 - c6 + a33;
    a21 = c1 - a31;
    a22 = c6 - a33;
    a23 = c3 -a33;
    a32 = c2 - a22;
    if (a31 < 0 || a21 < 0 || a22 < 0 || a23 < 0 || a32 < 0)
        return false;
    
    return true;
    
}

int read_diag(int which) {
    if (which == 1) {
        return board[0][0]*10000 + board[1][1]*1000 + board[2][2]* 100 + board[3][3]*10 + board[4][4];
    }
    else {
        return board[4][0]*10000 + board[3][1]*1000 + board[2][2]* 100 + board[1][3]*10 + board[0][4];
    }
}

void search_v2() {
    for (int i0 = 0; i0 < cnt; ++i0) {
        if (row1col1(i0)) {
            setrow(1, i0);
            for (int i1 = 0; i1 < cnt; ++i1) {
                if (row1col1(i1)) {
                    setcol(1, i1);
                    for (int i2 = 0; i2 < cnt; ++i2) {
                        if (row5(i2)) {
                            setrow(5, i2);
                            for (int i3 = 0; i3 < cnt; ++i3) {
                                if (col5(i3)) {
                                    setcol(5, i3);
                                    //cout << board[1][0] << ' ' << board[1][4] << endl;
                                    for (int i4 = 0; i4 < cnt; ++i4) {
                                        if (digits[i4][0] == board[1][0]
                                            && digits[i4][4] == board[1][4]) {
                                            setrow(2, i4);
                                            
                                            if (solver(board[3][3], board[3][1], board[2][1], board[2][2], board[2][3], board[3][2])) {
                                                if (is_valid[readrow(2)]
                                                    && is_valid[readrow(3)]
                                                    && is_valid[readcol(1)]
                                                    && is_valid[readcol(2)]
                                                    && is_valid[readcol(3)]
                                                    && is_valid[read_diag(1)]
                                                    && is_valid[read_diag(2)]
                                                    ) {
                                                    save();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("prime3.in");
    
    fin >> sum >> ul;
    
    fin.close();
    
    init();
    search_v2();

    fout.open("prime3.out");
    
    if (ans == 0) {
        fout << "NONE" << endl;
    }
    else {
        sort(saved, saved+ans);
        for (int i = 0; i < ans; ++i) {
            if (i == 0) {
                fout << saved[i].val1 << endl;
                fout << saved[i].val2 << endl;
                fout << saved[i].val3 << endl;
                fout << saved[i].val4 << endl;
                fout << saved[i].val5 << endl;
            }
            else {
                fout << endl;
                fout << saved[i].val1 << endl;
                fout << saved[i].val2 << endl;
                fout << saved[i].val3 << endl;
                fout << saved[i].val4 << endl;
                fout << saved[i].val5 << endl;
            }
        }
    }
    
    fout.close();
    
    return 0;
}


































































