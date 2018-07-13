
/*
 ID: tfan0328
 PROG: game1
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


using namespace std;
const int infty = 0x7fffffff;
int N;
const int MAXN = 100;
int board[MAXN] = {};
int dp[MAXN][MAXN] = {};
int s[MAXN][MAXN] = {};

int main(int argc, const char * argv[]) {
    
    ifstream fin ("game1.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> board[i];
        s[i][i] = board[i];
        dp[i][i] = s[i][i];
    }
    // dp[i][j] best sol for a play picking from [i, j] on the board

    
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            s[i][j] = s[i][j-1] + board[j];
        }
    }
    // dp[i][j] = max(board[i]+s[i+1][j]-dp[i+1][j], board[j]+s[i][j-1]-dp[i][j-1])
    
    for (int d = 1; d < N; ++d) {
        for (int i = 0; i < N; ++i) {
            if (i+d < N) {
                int j = i+d;
                dp[i][j] = max(board[i]+s[i+1][j]-dp[i+1][j], board[j]+s[i][j-1]-dp[i][j-1]);
            }
        }
    }
    
    
    ofstream fout ("game1.out");
    fout << dp[0][N-1]<< ' '<< s[0][N-1] - dp[0][N-1] << endl;

    fout.close();
    return 0;
}























