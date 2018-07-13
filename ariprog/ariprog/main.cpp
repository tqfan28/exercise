//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: ariprog
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int length = 125001;
int N;
int M;
int Bisquares[length]={};

//bool check(vector<int>::iterator start, vector<int>::iterator end, int d) {
//    if (start + N < end) {
//        vector<int>::iterator newbegin = start;
//        for (int i = 0; i < N; ++i) {
//            newbegin = find(newbegin, end, (*start) + i*d);
//            if ( newbegin == end ) {
//                return false;
//            }
//        }
//        return true;
//    }
//    return false;
//}


void generateBisquares(int M){
    for (int i = 0; i < M+1; ++i) {
        for (int j = 0; j < (i + 1); ++j) {
            Bisquares[ (i*i + j*j) ] = 1;
        }
    }
}

bool isArithmeticProgression(int start, int largest, int d) {
    for (int i = 0; i < N; ++i) {
        if ( Bisquares[(start + i*d)] == 0 ) {
            return false;
        }
    }
    return true;
}

struct Pair {
    int a;
    int b;
};

int main(int argc, const char * argv[]) {
    
    ifstream fin ("ariprog.in");
    fin >> N >> M;
    
    generateBisquares(M);
//    vector<Pair> result;
//    Pair current;
    bool NONE = true;
    int largest = 2*M*M;
    
//    for (int i = 0; i < largest + 1; ++i) {
//        cout << i << ' ' << Bisquares[i]<< endl;
//    }
    
    ofstream fout ("ariprog.out");
    for (int d = 1; d < largest/(N-1) + 1 ; ++d) {
        for (int start = 0; start < largest + 1 - (N-1)*d; ++start) {
            if (isArithmeticProgression(start, largest, d)) {
                NONE = false;
                fout << start << ' ' << d << '\n';
            }
        }
    }
    if (NONE) {
        fout << "NONE" << endl;
    }
    fout.close();
    
// Solution1: too slow
//    vector<int> S;
//    for (int i = 0; i < M+1; ++i) {
//        for (int j = 0; j < i+1; ++j) {
//            if (S.begin() == S.end()) {
//                S.push_back(0);
//            }
//            else {
//                //vector<int>::iterator current = find(S.begin() ,S.end(), i*i + j*j);
//                //if (current == S.end()){
//                    S.push_back(i*i + j*j);
//                //}
//            }
//        }
//    }
//
//    sort(S.begin(), S.end());
//    vector<Pair> result;
//    Pair current;
//    int largest = *(S.end()-1);
//
//    for (int d = 1; d < (2*largest*largest/N); ++d) {
//        for (vector<int>::iterator start = S.begin(); start != S.end(); ++start) {
//            if (check(start, S.end(), d)) {
//                current.a = *start;
//                current.b = d;
//                result.push_back(current);
//            }
//        }
//    }
//    for (int n: S) {
//        std::cout<<n << endl;
//    }
//    cout << endl;
//    
    
    

    
//    ofstream fout ("ariprog.out");
//    for(Pair n : result) {
//        fout << n.a << ' ' << n.b << '\n';
//    }
//    fout.close();
    
    //        for(Pair n : result) {
    //            std::cout << n.a << ' ' << n.b << '\n';
    //        }
    //
    
    return 0;
}








