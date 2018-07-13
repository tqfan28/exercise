
/*
 ID: tfan0328
 PROG: shopping
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


using namespace std;
const int infty = 0x7fffffff;
int s;
int b;
int offerPrice[100];
int buyPrice[5];
int state[6][6][6][6][6][100] = {};

struct ck {
    int c;
    int k;
};


int buy[5];
int findc[5];
map<int, int> findi;
list<ck> offers[100];


int solver(int target[5], int offerUsed) {
    int result = 0;

    if (offerUsed == -1) {
        for (int i = 0; i < b; ++i) {
            result += buyPrice[i]*target[i];
        }
        return result;
    }
    
    int newTarget[5];
    for (int i = 0; i < 5; ++i) {
        newTarget[i] = target[i];
    }
    
    bool did_break = false;
    list<ck>currentOffer = offers[offerUsed];
    
    int counter = 0;
    while (!did_break) {
        for (list<ck>::iterator a = currentOffer.begin(); a != currentOffer.end(); ++a) {
            if (findi.find(a->c) != findi.end()) {
                newTarget[findi[a->c]] = target[findi[a->c]] - counter*a->k;
                if (newTarget[findi[a->c]] < 0) {
                    did_break = true;
                    break;
                }
            }
            else {
                did_break = true;
                break;
            }
        }
        if (!did_break) {
            int tmp;
            
            if (state[newTarget[0]][newTarget[1]][newTarget[2]][newTarget[3]][newTarget[4]][offerUsed-1] != 0) {
                tmp = state[newTarget[0]][newTarget[1]][newTarget[2]][newTarget[3]][newTarget[4]][offerUsed-1];
            }
            else {
                tmp = solver(newTarget, offerUsed-1);
                state[newTarget[0]][newTarget[1]][newTarget[2]][newTarget[3]][newTarget[4]][offerUsed-1] = tmp;
            }
            
            
            if (counter == 0) {
                 result = tmp;
            }
            else
                result = min(result, tmp + counter*offerPrice[offerUsed]);
        }
        
        counter ++;
    }
    state[target[0]][target[1]][target[2]][target[3]][target[4]][offerUsed] = result;
    return result;
}


int main(int argc, const char * argv[]) {
    
    ifstream fin ("shopping.in");
    
    fin >> s;
    for (int i = 0; i < s; ++i) {
        int n;
        int c;
        int k;
        fin >> n;
        for (int j = 0; j < n; ++j) {
            fin >> c >> k;
            offers[i].push_back(ck{c, k});
        }
        fin >> offerPrice[i];
    }
    fin >> b;
    
    for (int i = 0; i < b; ++i) {
        fin >> findc[i] >> buy[i];
        fin >> buyPrice[i];
        findi[findc[i]] = i;
    }
    
    ofstream fout ("shopping.out");
    fout << solver(buy, s-1) << endl;
    fout.close();
    
    return 0;
}



















