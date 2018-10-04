//
//  main.cpp
//  packrec
//
//  Created by TFAN on 2018/9/21.
//  Copyright © 2018年 TFAN. All rights reserved.
//




/*
 ID: tfan0328
 PROG: packrec
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
const int infty = 0x7fffffff;

struct rect{
    int h;
    int w;
};

rect rects[4];
bool rotates[16*4] = {
    0, 0, 0, 0,
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
    1, 1, 0, 0,
    1, 0, 1, 0,
    1, 0, 0, 1,
    0, 1, 1, 0,
    0, 1, 0, 1,
    0, 0, 1, 1,
    1, 1, 1, 0,
    1, 1, 0, 1,
    1, 0, 1, 1,
    0, 1, 1, 1,
    1, 1, 1, 1
};

// four rects line up
int layout1(rect* rs, int & h) {
    int maxh = 0;
    int maxw = 0;
    for (int i = 0; i < 4; ++i) {
        maxh = max(rs[i].h, maxh);
        maxw += rs[i].w;
    }
    h = maxh;
    return maxh*maxw;
}

// three line up, fourth on the bottom
int layout2(rect* rs, int & h) {
    int maxh = 0;
    int maxw = 0;
    for (int i = 0; i < 3; ++i) {
        maxh = max(rs[i].h, maxh);
        maxw += rs[i].w;
    }
    maxh += rs[3].h;
    maxw = max(rs[3].w, maxw);
    
    h = maxh;
    return maxh*maxw;
}

// two line up, third on the bottom, fourth on the right
int layout3(rect* rs, int & h) {
    int maxh = 0;
    int maxw = 0;
    for (int i = 0; i < 2; ++i) {
        maxh = max(rs[i].h, maxh);
        maxw += rs[i].w;
    }
    maxh += rs[2].h;
    maxw = max(rs[2].w, maxw);
    
    maxh = max(rs[3].h, maxh);
    maxw += rs[3].w;
    
    h = maxh;
    return maxh*maxw;
}

// two line up, the other two stack
int layout45(rect* rs, int & h) {
    int maxh = 0;
    int maxw = 0;
    for (int i = 0; i < 2; ++i) {
        maxw = max(rs[i].w, maxw);
        maxh += rs[i].h;
    }
    maxh = max(rs[2].h, maxh);
    maxw += rs[2].w;
    
    maxh = max(rs[3].h, maxh);
    maxw += rs[3].w;
    
    h = maxh;
    return maxh*maxw;
}

// two line up, third one on top of first, fourth one on top of second
int layout6(rect* rs, int & h) {
    int maxh = 0;
    int maxw = 0;
    for (int i = 0; i < 2; ++i) {
        maxh = max(rs[i].h, maxh);
        maxw += rs[i].w;
    }
    if (rs[0].h <= rs[1].h) {
        if (rs[2].w <= rs[0].w) {
            if (rs[2].h+rs[0].h <= rs[1].h) {
                maxh = rs[1].h+rs[3].h;
                maxw = max(rs[3].w, maxw);
            }
            else {
                maxw = max(maxw, rs[2].w+rs[3].w);
                maxh = max(rs[1].h+rs[3].h, rs[0].h+rs[2].h);
            }
        }
        else {
            if (rs[2].h+rs[0].h <= rs[1].h) {
                maxh = rs[1].h+rs[3].h;
                maxw = max(rs[2].w+rs[1].w, rs[3].w);
            }
            else {
                maxh = max(rs[1].h+rs[3].h, rs[0].h+rs[2].h);
                maxw = rs[2].w+ max(rs[3].w, rs[1].w);
            }
        }
    }
    else {
        if (rs[3].w <= rs[1].w) {
            if (rs[3].h+rs[1].h <= rs[0].h) {
                maxh = rs[0].h+rs[2].h;
                maxw = max(rs[2].w, maxw);
            }
            else {
                maxw = max(maxw, rs[3].w+rs[2].w);
                maxh = max(rs[0].h+rs[2].h, rs[1].h+rs[3].h);
            }
        }
        else {
            if (rs[3].h+rs[1].h <= rs[0].h) {
                maxh = rs[0].h+rs[2].h;
                maxw = max(rs[3].w+rs[0].w, rs[2].w);
            }
            else {
                maxh = max(rs[0].h+rs[2].h, rs[1].h+rs[3].h);
                maxw = rs[3].w+ max(rs[2].w, rs[0].w);
            }
        }
    }
    
    h = maxh;
    return maxh*maxw;
}


int main(int argc, const char * argv[]) {
    
    
    ifstream fin;
    fin.open("packrec.in");
    for (int i = 0; i < 4; ++i) {
        fin >> rects[i].w;
        fin >> rects[i].h;
    }
    fin.close();
    
    int ans = infty;
    int cnt = 0;
    int id = 0;
    int ansh[10000] = {};
    int answ[10000] = {};
    int tmp = 0;
    int tmph = 0;
    
    int perm[4] = {0, 1, 2, 3};
    do {
        rect cur_rects[4];
        for (int i = 0; i < 4; ++i) {
            cur_rects[i].h = rects[perm[i]].h;
            cur_rects[i].w = rects[perm[i]].w;
        }
        rect cur_rects_rot[4];
        for (int i = 0; i < 64; i = i + 4) {
            for (int j = 0; j < 4; ++j) {
                if (rotates[i+j]) {
                    cur_rects_rot[j].h = cur_rects[j].w;
                    cur_rects_rot[j].w = cur_rects[j].h;
                }
                else {
                    cur_rects_rot[j].h = cur_rects[j].h;
                    cur_rects_rot[j].w = cur_rects[j].w;
                }
            }
            tmp = layout1(cur_rects_rot, tmph);
            if (ans >= tmp) {
                ans = tmp;
                ansh[cnt] = tmph;
                answ[cnt] = ans/tmph;
                cnt ++;
            }
            tmp = layout2(cur_rects_rot, tmph);
            if (ans >= tmp) {
                ans = tmp;
                ansh[cnt] = tmph;
                answ[cnt] = ans/tmph;
                cnt ++;
            }
            tmp = layout3(cur_rects_rot, tmph);
            if (ans >= tmp) {
                ans = tmp;
                ansh[cnt] = tmph;
                answ[cnt] = ans/tmph;
                cnt ++;
            }
            tmp = layout45(cur_rects_rot, tmph);
            if (ans >= tmp) {
                ans = tmp;
                ansh[cnt] = tmph;
                answ[cnt] = ans/tmph;
                cnt ++;
            }
            tmp = layout6(cur_rects_rot, tmph);
            if (ans >= tmp) {
                ans = tmp;
                ansh[cnt] = tmph;
                answ[cnt] = ans/tmph;
                cnt ++;
            }
        }
    } while (next_permutation(perm, perm+4));

    
    ofstream fout;
    fout.open("packrec.out");
    
    int fil_ansh[10000] = {};
    int cnt_filansh = 0;
    for (int i = 0; i < cnt; ++i) {
        if (ans == ansh[i]*answ[i]) {
            fil_ansh[cnt_filansh] = ansh[i];
            cnt_filansh ++;
        }
    }
    fout << ans << endl;
    
    sort(fil_ansh, fil_ansh+cnt_filansh);

    
    int sofar[1000] = {};
    int cnt_sofar = 0;
    for (int i = id; i < cnt_filansh; ++i) {
        if (i != id) {
            if (fil_ansh[i-1] != fil_ansh[i]) {
                int * check_repeat = find(sofar, sofar+cnt_sofar, ans/fil_ansh[i]);
                if (check_repeat == sofar+cnt_sofar) {
                    sofar[cnt_sofar] = fil_ansh[i];
                    cnt_sofar ++;
                    fout << min(fil_ansh[i], (ans/fil_ansh[i])) << ' ' << max(fil_ansh[i], (ans/fil_ansh[i])) << endl;
                }
            }
            
        }
        else {
            sofar[cnt_sofar] = fil_ansh[i];
            cnt_sofar ++;
            fout << min(fil_ansh[i], (ans/fil_ansh[i])) << ' ' << max(fil_ansh[i], (ans/fil_ansh[i])) << endl;
        }
    }
    
    fout.close();
    
    return 0;
}





























































