//
//  main.cpp
//  window
//
//  Created by TFAN on 2018/8/6.
//  Copyright © 2018年 TFAN. All rights reserved.
//


/*
 ID: tfan0328
 PROG: window
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
#include <math.h>
#include <iomanip>


using namespace std;
//const int infty = 0x7fffffff;
queue<string> commands;

struct window {
    char id;
    int xmax;
    int xmin;
    int ymax;
    int ymin;
};
list<window> windows;

void wparser(const string& s, int& xmax, int& xmin, int& ymax, int& ymin) {
    int st = 4;
    int arr[4] = {};
    for (int i = 0; i < 4; ++i) {
        int ed = st+1;
        while(ed < s.size()-1 && s[ed] != ',') {
            ed++;
        }
        string num = s.substr(st, ed);
        arr[i] = stoi(num);
        st = ed+1;
    }
    xmax = max(arr[0], arr[2]);
    xmin = min(arr[0], arr[2]);
    ymax = max(arr[1], arr[3]);
    ymin = min(arr[1], arr[3]);
}

void w(string s) {
    window awin;
    awin.id = s[2];
    awin.xmax = 0;
    awin.xmin = 0;
    awin.ymax = 0;
    awin.ymin = 0;
    wparser(s, awin.xmax, awin.xmin, awin.ymax, awin.ymin);
    if (windows.empty()) {
       
        windows.push_back(awin);
        return ;
    }
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != awin.id) {
        itr ++;
    }
    if (itr == windows.end()) {
        windows.push_back(awin);
    }
}

void t(char id) {
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != id) {
        itr ++;
    }
    if (itr != windows.end()) {
        window tmp = (*itr);
        windows.erase(itr);
        windows.push_back(tmp);
    }
}

void b(char id) {
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != id) {
        itr ++;
    }
    if (itr != windows.end()) {
        window tmp = (*itr);
        windows.erase(itr);
        windows.push_front(tmp);
    }
}

void d(char id) {
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != id) {
        itr ++;
    }
    if (itr != windows.end()) {
        windows.erase(itr);
    }
}

bool isIn(int xmax, int xmin, int ymax, int ymin, int x, int y) {
    if (x >= xmin && x < xmax && y >= ymin && y < ymax)
        return true;
    return false;
}

double s(char id) {
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != id) {
        itr ++;
    }
    if (itr == windows.end()) {
        return 0.0;
    }
    int xmax = itr->xmax;
    int xmin = itr->xmin;
    int ymax = itr->ymax;
    int ymin = itr->ymin;
    itr ++;
    list<window>::iterator itr2 = itr;

    int vol = 0;
    for (int i = xmin; i < xmax; ++i) {
        for (int j = ymin; j < ymax; ++j) {
            bool did_break = false;
            itr2 = itr;
            while (itr2 != windows.end()) {
                //cout << i << ' ' << j << ' ' << itr2->xmax<< ' ' << itr2->xmin<< ' ' << itr2->ymax << ' ' << itr2->ymin << endl;
                //cout << isIn(itr2->xmax, itr2->xmin, itr2->ymax, itr2->ymin, i, j) << endl;
                if (isIn(itr2->xmax, itr2->xmin, itr2->ymax, itr2->ymin, i, j)) {
                    did_break = true;
                    vol ++;
                    break;
                }
                itr2++;
            }
        }
    }
    
    //cout << "vol"<<vol << endl;
    //cout << "total" << (xmax-xmin)*(ymax-ymin) << endl;
    return 1- float(vol)/float((xmax-xmin)*(ymax-ymin));
}

int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("window.in");
    
    string ss;
    while((fin>>ss)) {
        commands.push(ss);
    }
    
    fin.close();
    
    ofstream fout;
    fout.open("window.out");
    
    while(!commands.empty()) {
        if (commands.front()[0] == 'w') {
            w(commands.front());
        }
        else if (commands.front()[0] == 't') {
            t(commands.front()[2]);
        }
        else if (commands.front()[0] == 'b') {
            b(commands.front()[2]);
        }
        else if (commands.front()[0] == 'd') {
            d(commands.front()[2]);
        }
        else {
            cout <<fixed <<setprecision(3)<<s(commands.front()[2])*100 << endl;
        }
        commands.pop();
    }
    
    fout.close();
    
    return 0;
}




































