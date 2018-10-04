////
////  main.cpp
////  prime3
////
////  Created by TFAN on 2018/9/26.
////  Copyright © 2018年 TFAN. All rights reserved.
////
//
///*
// ID: tfan0328
// PROG: prime3
// LANG: C++
// */
//
//#include <iostream>
//#include <fstream>
////#include <cstring>
////#include <string>
////#include <stdio.h>
////#include <ctype.h>
////#include <vector>
////#include <queue>
////#include <stack>
////#include <list>
////#include <map>
//#include <algorithm>
////#include <math.h>
////#include <iomanip>
//#include<ctime>
//
//using namespace std;
//int sum;
//int ul;
//int cnt = 0;
//int primes[5000] = {};
//bool is_valid[100000] = {};
//int board[5][5] = {};
//ofstream fout;
//int ans = 0;
//
//struct num {
//    int val1;
//    int val2;
//    int val3;
//    int val4;
//    int val5;
//    bool operator<(const num & rhs) const {
//        return (
//                val1 < rhs.val1
//                || (val1 == rhs.val1 && val2 < rhs.val2)
//                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 < rhs.val3)
//                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 == rhs.val3 && val4 < rhs.val4)
//                || (val1 == rhs.val1 && val2 == rhs.val2 && val3 == rhs.val3 && val4 == rhs.val4 && val5 < rhs.val5)
//                );
//    }
//};
//
//num saved[100];
//
//bool is_prime(int n) {
//    if (n <= 1)
//        return false;
//    else if (n <= 3)
//        return true;
//    else if (n % 2 == 0 || n % 3 == 0)
//        return false;
//    int i = 5;
//    while(i*i <= n) {
//        if (n % i == 0 || n % (i+2) == 0) {
//            return false;
//        }
//        i = i +6;
//    }
//    return true;
//}
//
//bool check_sum(int n) {
//    int result = 0;
//    for (int i = 0; i < 5; ++i) {
//        result += (n % 10);
//        n = (n - n % 10)/10;
//    }
//    if (result == sum)
//        return true;
//    else
//        return false;
//}
//
//int get_digit(int n, int t) {
//    int result = 0;
//    for (int i = 0; i < t; ++i) {
//        result = n % 10;
//        n = (n - (n % 10))/10;
//    }
//    return result;
//}
//
//void generate_primes() {
//    for (int i = 10000; i < 100000; ++i) {
//        if (is_prime(i) && check_sum(i)) {
//            is_valid[i] = true;
//            primes[cnt] = i;
//            cnt ++;
//        }
//    }
//}
//
//void init() {
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            board[i][j] = -1;
//        }
//    }
//    board[0][0] = ul;
//    generate_primes();
//}
//

//
//  main.cpp
//  prime3
//
//  Created by TFAN on 2018/9/26.
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

num saved[100];

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


bool row1col1(int p) {
    if (get_digit(p, 5) != ul)
        return false;
    for (int i = 1; i < 5; ++i) {
        if (get_digit(p, i) == 0) {
            return false;
        }
    }
    return true;
}

void setrow(int n, int id) {
    for (int i = 0; i < 5; ++i) {
        board[n-1][i] = get_digit(primes[id], 5-i);
    }
}

void setcol(int n, int id) {
    for (int i = 0; i < 5; ++i) {
        board[i][n-1] = get_digit(primes[id], 5-i);
    }
}

int filrow(int i, int j) {
    int res = 0;
    for (int k = 0; k < 5; ++k) {
        if (k != j) {
            res += board[i][k];
        }
    }
    board[i][j] = sum - res;
    return board[i][j];
}

int readcol(int i) {
    return board[0][i]*10000 + board[1][i]*1000 + board[2][i]* 100 + board[3][i]*10 + board[4][i];
}

int readrow(int i) {
    return board[i][0]*10000 + board[i][1]*1000 + board[i][2]* 100 + board[i][3]*10 + board[i][4];
}

int filcol(int i, int j) {
    int res = 0;
    for (int k = 0; k < 5; ++k) {
        if (k != i) {
            res += board[k][j];
        }
    }
    board[i][j] = sum - res;
    return board[i][j];
}

void save() {
    saved[ans].val1 = readrow(0);
    saved[ans].val2 = readrow(1);
    saved[ans].val3 = readrow(2);
    saved[ans].val4 = readrow(3);
    saved[ans].val5 = readrow(4);
    ans ++;
}

void dfs(int depth) {
    
    if (depth == 6) {
        save();
        return ;
    }
    
    if (depth == 0) {
        for (int i = 0; i < cnt; ++i) {
            if (row1col1(primes[i])) {
                setrow(1, i);
                dfs(depth+1);
            }
        }
    }
    
    else if (depth == 1) {
        for (int i = 0; i < cnt; ++i) {
            if (row1col1(primes[i])) {
                setcol(1, i);
                dfs(depth+1);
            }
        }
    }
    
    else if (depth == 2) {
        for (int i = 0; i < cnt; ++i) {
            if (get_digit(primes[i], 5) == ul)  {
                for (int j = 0; j < 5; ++j) {
                    board[j][j] = get_digit(primes[i], 5-j);
                }
                dfs(depth+1);
            }
        }
    }
    
    else if (depth == 3) {
        for (int i = 0; i < cnt; ++i) {
            if (get_digit(primes[i], 5) == board[4][0]
                && get_digit(primes[i], 3) == board[2][2]
                && get_digit(primes[i], 1) == board[0][4]
                ) {
                board[3][1] = get_digit(primes[i], 4);
                board[1][3] = get_digit(primes[i], 2);
                if ( (board[1][0]+ board[1][1]+board[1][3] <= sum)
                    && (board[3][0]+ board[3][1]+board[3][3] <= sum)
                    ) {
                    dfs(depth+1);
                }
            }
        }
    }
    
    else if (depth == 4) {
        for (int i = 0; i < cnt; ++i) {
            if (get_digit(primes[i], 5) == board[4][0]
                && get_digit(primes[i], 1) == board[4][4]
                ) {
                board[4][1] = get_digit(primes[i], 4);
                board[4][2] = get_digit(primes[i], 3);
                board[4][3] = get_digit(primes[i], 2);
                
                filcol(2, 1);
                int col2 = readcol(1);
                if (is_valid[col2]) {
                    filcol(2, 3);
                    int col4 = readcol(3);
                    if (is_valid[col4]) {
                        filrow(2, 4);
                        int row3 = readrow(2);
                        if (is_valid[row3]
                            && (board[0][2]+ board[2][2]+board[4][2] <= sum)
                            ) {
                            dfs(depth+1);
                        }
                    }
                }
            }
        }
    }
    
    else if (depth == 5) {
        for (int i = 0; i < cnt; ++i) {
            if (get_digit(primes[i], 5) == board[0][4]
                && get_digit(primes[i], 3) == board[2][4]
                && get_digit(primes[i], 1) == board[4][4]
                ) {
                board[1][4] = get_digit(primes[i], 4);
                board[3][4] = get_digit(primes[i], 2);
                
                filrow(1,2);
                filrow(3, 2);
                
                int row2 = readrow(1);
                int row4 = readrow(3);
                int col3 = readcol(2);
                
                if (is_valid[row2] && is_valid[row4] && is_valid[col3]) {
                    dfs(depth+1);
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
    dfs(0);
    
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


































































//void print(ostream& stream) {
//
//    if (ans != 0)
//        stream << endl;
//
//    ans ++;
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            stream << board[i][j];
//        }
//        stream << endl;
//    }
//}
//
//
//bool row1col1(int p) {
//    if (get_digit(p, 5) != ul)
//        return false;
//    for (int i = 1; i < 5; ++i) {
//        if (get_digit(p, i) == 0) {
//            return false;
//        }
//    }
//    return true;
//}
//
//void setrow(int n, int id) {
//    for (int i = 0; i < 5; ++i) {
//        board[n-1][i] = get_digit(primes[id], 5-i);
//    }
//}
//
//void setcol(int n, int id) {
//    for (int i = 0; i < 5; ++i) {
//        board[i][n-1] = get_digit(primes[id], 5-i);
//    }
//}
//
//void filrow(int i, int j) {
//    int res = 0;
//    for (int k = 0; k < 5; ++k) {
//        if (k != j) {
//            res += board[i][k];
//        }
//    }
//    board[i][j] = sum - res;
//}
//
//int readcol(int i) {
//    return board[0][i]*10000 + board[1][i]*1000 + board[2][i]* 100 + board[3][i]*10 + board[4][i];
//}
//
//int readrow(int i) {
//    return board[i][0]*10000 + board[i][1]*1000 + board[i][2]* 100 + board[i][3]*10 + board[i][4];
//}
//
//void filcol(int i, int j) {
//    int res = 0;
//    for (int k = 0; k < 5; ++k) {
//        if (k != i) {
//            res += board[k][j];
//        }
//    }
//    board[i][j] = sum - res;
//}
//
//void save() {
//    saved[ans].val1 = readrow(0);
//    saved[ans].val2 = readrow(1);
//    saved[ans].val3 = readrow(2);
//    saved[ans].val4 = readrow(3);
//    saved[ans].val5 = readrow(4);
//    ans ++;
//}
//
//void dfs(int depth) {
//
//    if (depth == 7) {
//        save();
//        return ;
//    }
//
//    if (depth == 0) {
//        for (int i = 0; i < cnt; ++i) {
//            if (row1col1(primes[i])) {
//                setrow(1, i);
//                dfs(depth+1);
//            }
//        }
//    }
//
//    else if (depth == 1) {
//        for (int i = 0; i < cnt; ++i) {
//            if (row1col1(primes[i])) {
//                setcol(1, i);
//                dfs(depth+1);
//            }
//        }
//    }
//
//    else if (depth == 2) {
//        for (int i = 0; i < cnt; ++i) {
//            if (get_digit(primes[i], 5) == ul)  {
//                for (int j = 0; j < 5; ++j) {
//                    board[j][j] = get_digit(primes[i], 5-j);
//                }
//                dfs(depth+1);
//            }
//        }
//    }
//
//    else if (depth == 3) {
//        for (int i = 0; i < cnt; ++i) {
//            if (get_digit(primes[i], 5) == board[4][0]
//                && get_digit(primes[i], 3) == board[2][2]
//                && get_digit(primes[i], 1) == board[0][4]
//                ) {
//                board[3][1] = get_digit(primes[i], 4);
//                board[1][3] = get_digit(primes[i], 2);
//                if ( (board[1][0]+ board[1][1]+board[1][3] <= sum)
//                    && (board[3][0]+ board[3][1]+board[3][3] <= sum)
//                    ) {
//                    dfs(depth+1);
//                }
//            }
//        }
//    }
//
//    else if (depth == 4) {
//        for (int i = 0; i < cnt; ++i) {
//            if (get_digit(primes[i], 5) == board[1][0]
//                && get_digit(primes[i], 4) == board[1][1]
//                && get_digit(primes[i], 2) == board[1][3]
//                ) {
//                board[1][2] = get_digit(primes[i], 3);
//                board[1][4] = get_digit(primes[i], 1);
//
//                dfs(depth+1);
//            }
//        }
//    }
//
//    else if (depth == 5) {
//        for (int i = 0; i < cnt; ++i) {
//            if (get_digit(primes[i], 5) == board[0][1]
//                && get_digit(primes[i], 4) == board[1][1]
//                && get_digit(primes[i], 2) == board[3][1]
//                ) {
//                board[2][1] = get_digit(primes[i], 3);
//                board[4][1] = get_digit(primes[i], 1);
//
//                dfs(depth+1);
//            }
//        }
//    }
//
//    else if (depth == 6) {
//        for (int i = 0; i < cnt; ++i) {
//            if (get_digit(primes[i], 5) == board[0][2]
//                && get_digit(primes[i], 4) == board[1][2]
//                && get_digit(primes[i], 3) == board[2][2]
//                ) {
//                board[3][2] = get_digit(primes[i], 2);
//                board[4][2] = get_digit(primes[i], 1);
//
//                filrow(3, 4);
//                int row4 = readrow(3);
//
//                if (is_valid[row4]) {
//                    filcol(2, 4);
//                    int col5 = readcol(4);
//                    if (is_valid[col5]) {
//                        filrow(2, 3);
//                        int row3 = readrow(2);
//                        if (is_valid[row3]) {
//                            filrow(4, 3);
//                            int row5 = readrow(4);
//                            int col4 = readcol(3);
//                            if (is_valid[row5] && is_valid[col4]) {
//                                dfs(depth+1);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//
//}
//
//
//int main(int argc, const char * argv[]) {
//
//    ifstream fin;
//    fin.open("prime3.in");
//
//    fin >> sum >> ul;
//
//    fin.close();
//
//    init();
//    clock_t begin = clock();
//
//    dfs(0);
//
//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    cout << elapsed_secs << endl;
//
//    fout.open("prime3.out");
//
//    if (ans == 0) {
//        fout << "NONE" << endl;
//    }
//    else {
//        sort(saved, saved+ans);
//        for (int i = 0; i < ans; ++i) {
//            if (i == 0) {
//                fout << saved[i].val1 << endl;
//                fout << saved[i].val2 << endl;
//                fout << saved[i].val3 << endl;
//                fout << saved[i].val4 << endl;
//                fout << saved[i].val5 << endl;
//            }
//            else {
//                fout << endl;
//                fout << saved[i].val1 << endl;
//                fout << saved[i].val2 << endl;
//                fout << saved[i].val3 << endl;
//                fout << saved[i].val4 << endl;
//                fout << saved[i].val5 << endl;
//            }
//        }
//    }
//
//    fout.close();
//
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
