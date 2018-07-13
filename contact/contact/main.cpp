//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: contact
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <time.h>

using namespace std;
int A;
int B;
int N;
queue<int> frequency[8191] = {};
int result[8191] = {};
string S;
int order[8191] = {};
struct data {
    int index;
    int value;
    bool operator<(const data& rhs) const
    {
        return (value < rhs.value || (value == rhs.value && index > rhs.index) );
    }
};
priority_queue<data> lines;

string indexToString(int index) {
    string s;
    //cout << index << "and";
    int k = floor(log2(index+1));
    index -= pow(2, k)-1;
    //cout << index << endl;
    for (int i = 0; i < k; ++i) {
        if (index % 2 == 0)
            s = "0"+s;
        else {
            s = "1"+s;
        }
        index = (index -(index % 2 ))/2;
    }
    return s;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("contact.in");
    fin >> A >> B >> N;
    string s;
    while(getline(fin, s)) {
        S += s;
    }
   
    // index: 2^1 + 2^2 + ... + 2^{12}
    // length k: 2^{k}-1 + (i = 0,...,2^k-1)

//    for (int i = 0; i < S.length()-1; ++i) {
//        if (S[i] == '0' && S[i+1] == '0') {
//            frequency[3].push(i);
//            result[3]++;
//        }
//        else if (S[i] == '0' && S[i+1] == '1') {
//            frequency[4].push(i);
//            result[4]++;
//        }
//        else if (S[i] == '1' && S[i+1] == '0') {
//            frequency[5].push(i);
//            result[5]++;
//        }
//        else if (S[i] == '1' && S[i+1] == '1') {
//            frequency[6].push(i);
//            result[6]++;
//        }
//    }
    
    for (int i = 0; i < S.length(); ++i) {
        if (S[i] == '0') {
            frequency[1].push(i);
            result[1]++;
        }
        else if (S[i] == '1') {
            frequency[2].push(i);
            result[2]++;
        }
    }
    
    for (int k = 2; k < B+1; ++k) {
        int start = pow(2, k)-1;
        for (int i = 0; i < pow(2, k); i=i+2) {
            int prev = (start+i)/2;
            while (!frequency[prev].empty()) {
                if (frequency[prev].front()+k-1 < S.length() && S[frequency[prev].front()+k-1] == '0') {
                    frequency[start+i].push(frequency[prev].front());
                    //cout << (start+i) << ' ' << frequency[start+i].back() <<endl;
                    result[start+i]++;
                }
                else if (frequency[prev].front()+k-1 < S.length()&& S[frequency[prev].front()+k-1] == '1') {
                    frequency[start+i+1].push(frequency[prev].front());
                    //cout << (start+i+1) << ' ' << frequency[start+i+1].back() <<endl;
                    result[start+i+1]++;
                }
                frequency[prev].pop();
            }
        }
    }
    
    ofstream fout ("contact.out");
    
    for (int k = A; k < B+1; ++k) {
        int start = pow(2, k)-1;
        for (int i = 0; i < pow(2, k); i++) {
            if (result[start+i] != 0) {
                //cout << start+i << ' '<< result[start+i] << endl;
                lines.push(data{start+i, result[start+i]});
            }
        }
    }
    
    int counter = 0;
    int start = -1;
    int six = 0;
    //cout << lines.top().index;
    while(counter < N && !lines.empty()) {
        if (start == -1) {
            start = lines.top().value;
            fout << start << endl;
            fout << indexToString(lines.top().index);
            six++;
            lines.pop();
        }
        while(!lines.empty() && lines.top().value == start) {
            if (six != 0) {
                fout <<' '<< indexToString(lines.top().index);
                six = (six + 1) % 6;
            }
            else {
                fout <<endl<< indexToString(lines.top().index);
                six ++;
            }
            lines.pop();
        }
        fout << endl;
        six = 0;
        start = -1;
        counter ++;
    }
    fout.close();
    return 0;
}



































