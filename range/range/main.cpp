
/*
 ID: tfan0328
 PROG: range
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <map>
#include <cmath>


using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 251;
int mat[MAXN][MAXN];
int dp[MAXN][MAXN];
int total[MAXN+1] = {};


int main(int argc, const char * argv[]) {
    
    ifstream fin ("range.in");
    fin >> N;
    string s;
    getline(fin, s);
    for (int i = 0; i < N; ++i) {
        getline(fin, s);
        for (int j = 0; j < N; ++j) {
            mat[i][j] = s[j] - '0';
            dp[i][j] = mat[i][j];
        }
    }
    
    //dp[i][j] the largest square with the bottom right corner (i,j)
    
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            if (mat[i][j] != 0) {
                int vertical = 1;
                int horizontal = 1;
                while(i-vertical >= 0 && mat[i-vertical][j] == 1) {
                    vertical ++;
                }
                if (dp[i][j-1] == 0) {
                    dp[i][j] = 1;
                }
                else if (vertical <= dp[i][j-1]) {
                    dp[i][j] = vertical;
                }
                else {
                    while(j - horizontal >=0 && i-dp[i][j-1] >= 0 && mat[i-dp[i][j-1]][j-horizontal] == 1) {
                            horizontal ++;
                        }
                    if (horizontal >= dp[i][j-1] + 1) {
                        dp[i][j] = dp[i][j-1]+1;
                    }
                    else {
                        dp[i][j] = dp[i][j-1];
                    }
                }
                //cout << i << ' ' << j << ' ' << i-dp[i][j-1] << ' ';
                //cout << "vertical" << vertical << "horizonal" << horizontal<< endl;
            }
        }
        //cout << endl;
    }
    
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                cout << dp[i][j] << ' ';
//            }
//            cout << endl;
//        }
    
    ofstream fout ("range.out");
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 1; k < dp[i][j]+1; ++k) {
                total[k] ++;
            }
        }
    }
    
    for (int i = 2; i < N+1; ++i) {
        if (total[i] != 0) {
            fout << i << ' ' << total[i] << endl;
        }
    }
    fout.close();
    return 0;
}






















