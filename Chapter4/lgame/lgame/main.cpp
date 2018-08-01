//
//  main.cpp
//  lgame
//
//  Created by TFAN on 2018/7/30.
//  Copyright © 2018年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: lgame
 LANG: C++
 */

#include <cstdio>
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
//const int infty = 0x7fffffff;
const int values[26] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
string dict[40000];
string input;



int val(string word) {
    int result = 0;
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] != ' ') {
            result += values[int(word[i] - 97)];
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("lgame.dict");
    int dictcnt = 0;
    while(getline(fin,dict[dictcnt++])){
        if(dict[dictcnt - 1][0] == '.')
            break;
    }
    fin.close();
    
    
    fin.open("lgame.in");
    fin >> input;
    fin.close();
    
    int N = input.size();
    int input2[26] = {};
    for (int i = 0; i < N; ++i) {
        input2[int(input[i] - 97)] ++;
    }
    
    vector<string> possible;
    
    for (int i = 0; i < dictcnt; ++i) {
        if (dict[i].size() <= N) {
            bool check = true;
            int diff[26] = {};
            for (int j = 0; j < dict[i].size(); ++j) {
                int index = int(dict[i][j] - 97);
                if (diff[index] == input2[index]) {
                    check = false;
                    break;
                }
                else {
                    diff[index]++;
                }
            }
            if (check) {
                possible.push_back(dict[i]);
            }
        }
    }

    
    string ans[5040*2];
    int vals[5040*2];
    int counter = 0;
    
    for (vector<string>::iterator i = possible.begin(); i != possible.end(); ++i) {
        if ((*i).size() == N) {
            ans[counter] = *i;
            vals[counter] = val(*i);
            counter++;
        }
        else {
            int diff[26] = {};
            for (int k = 0; k < (*i).size(); ++k) {
                diff[int((*i)[k]-97)] ++;
            }
            bool check3 = false;
            for (vector<string>::iterator j = i+1; j != possible.end(); ++j) {
                if ((*j).size()+(*i).size() <= N) {
                    int diff2[26] = {};
                    for (int k = 0; k < (*j).size(); ++k) {
                        diff2[int((*j)[k]-97)] ++;
                    }
                    int check2 = true;
                    for (int k = 0; k < 26; ++k) {
                        if(diff[k]+diff2[k] > input2[k])  {
                            check2 = false;
                            break;
                        }
                    }
                    if (check2) {
                        ans[counter] = ((*i) + " " + (*j));
                        vals[counter] = val(((*i) + " " + (*j)));
                        counter ++;
                        check3 = true;
                    }
                }
            }
            if (!check3) {
                ans[counter] = *i;
                vals[counter] = val(*i);
                counter++;
            }
        }
    }
    
    ofstream fout;
    fout.open("lgame.out");
    int points = 0;
    for (int i = 0; i < counter; ++i) {
        points = max(points, vals[i]);
    }
    fout << points << endl;
    for (int i = 0; i < counter; ++i) {
        if (vals[i] == points) {
            fout << ans[i]<< endl;
        }
    }
    fout.close();
    
    return 0;
}































