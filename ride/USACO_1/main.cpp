//
//  main.cpp
//  USACO_1
//
//  Created by TFAN on 2017/8/6.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: ride
 LANG: C++                  
 */
#include <iostream>
#include <fstream>
#include <string>
//#include <unordered_map>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    
    /*
    unordered_map<char, int> hashtable;
    hashtable.emplace('A', 1);
    hashtable.emplace('B', 2);
    hashtable.emplace('C', 3);
    hashtable.emplace('D', 4);
    hashtable.emplace('E', 5);
    hashtable.emplace('F', 6);
    hashtable.emplace('G', 7);
    hashtable.emplace('H', 8);
    hashtable.emplace('I', 9);
    hashtable.emplace('J', 10);
    hashtable.emplace('K', 11);
    hashtable.emplace('L', 12);
    hashtable.emplace('M', 13);
    hashtable.emplace('N', 14);
    hashtable.emplace('O', 15);
    hashtable.emplace('P', 16);
    hashtable.emplace('Q', 17);
    hashtable.emplace('R', 18);
    hashtable.emplace('S', 19);
    hashtable.emplace('T', 20);
    hashtable.emplace('U', 21);
    hashtable.emplace('V', 22);
    hashtable.emplace('W', 23);
    hashtable.emplace('X', 24);
    hashtable.emplace('Y', 25);
    hashtable.emplace('Z', 26);
     */
 
    string a, b;
    fin >> a >> b;
    int m_1 = 1;
    int m_2 = 1;
    for (int i = 0; i < a.length(); ++i) {
        m_1 *= int(a[i]) - 64;
    }
    for (int i = 0; i < b.length(); ++i) {
        m_2 *= int(b[i]) - 64;
    }
    if ((m_1 - m_2) % 47 == 0)
        fout << "GO" << endl;
    else
        fout << "STAY" << endl;
    
    return 0;
}
