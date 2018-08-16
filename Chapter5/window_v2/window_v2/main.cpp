//
//  main.cpp
//  window_v2
//
//  Created by TFAN on 2018/8/7.
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
    wparser(s, awin.xmax, awin.xmin, awin.ymax, awin.ymin);

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


double area(window cur, list<window>::iterator next) {
    
    next++;
    
    if (cur.xmax <= cur.xmin || cur.ymax <= cur.ymin) {
        return 0.0;
    }
    
    if (next == windows.end()) {
        return (cur.xmax - cur.xmin)*(cur.ymax - cur.ymin);
    }
    
    if (!(cur.ymax <= next->ymin || next->ymax <= cur.ymin
        || cur.xmax <= next->xmin || next->xmax <= cur.xmin)) {
        window left;
        left.xmin = cur.xmin;
        left.xmax = next->xmin;
        left.ymin = cur.ymin;
        left.ymax = cur.ymax;
        window up;
        up.xmin = max(cur.xmin, next->xmin);
        up.xmax = min(cur.xmax, next->xmax);
        up.ymin = next->ymax;
        up.ymax = cur.ymax;
        window right;
        right.xmin = next->xmax;
        right.xmax = cur.xmax;
        right.ymin = cur.ymin;
        right.ymax = cur.ymax;
        window down;
        down.xmin = max(cur.xmin, next->xmin);
        down.xmax = min(cur.xmax, next->xmax);
        down.ymin = cur.ymin;
        down.ymax =  next->ymin;
        return area(left, next) + area(up, next) + area(down, next) + area(right, next);
        
    }
    return area(cur, next);
}

double s(char id) {
    list<window>::iterator itr = windows.begin();
    while(itr != windows.end() && itr->id != id) {
        itr ++;
    }
    if (itr == windows.end()) {
        return 0.0;
    }
    
    double vol = area(*itr, itr);
    
    return vol/float((itr->xmax-itr->xmin)*(itr->ymax-itr->ymin));
    
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
            fout <<fixed <<setprecision(3)<<s(commands.front()[2])*100 << endl;
        }
        commands.pop();
    }
    
    fout.close();
    
    return 0;
}





































