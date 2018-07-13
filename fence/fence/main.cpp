
/*
 ID: tfan0328
 PROG: fence
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
//const int infty = 0x7fffffff;
int F;
int Circuit[1025];
int degree[501] = {};

struct edge {
    int a;
    int b;
};

list<edge> edges;
stack<int> vertexes;



int main(int argc, const char * argv[]) {
    
    ifstream fin ("fence.in");
    fin >> F;
    
    int a, b;
    for (int i = 0; i < F; ++i) {
        fin >> a >> b;
        degree[a]++;
        degree[b]++;
        edges.push_back({a, b});
    }
    int locationTour = 501;
    int location = 501;
    int counter = 0;
    for (int i = 1; i <501; ++i) {
        if (degree[i] == 0)
            continue;
        
        if (degree[i]%2 != 0) {
            counter ++;
            locationTour = min(locationTour, i);
        }
        else {
            location = min(location, i);
        }
    }
    if (counter ==2) {
        location = locationTour;
    }
    
    int pos = 0;
    while(pos != F+1) {
        bool did_push = false;
        //cout << location << endl;
        list<edge>::iterator i = edges.begin();
        list<edge>::iterator j;
        int minj = 501;
        while ( i!= edges.end()) {
            if (i->a == location) {
                if (i->b < minj) {
                    minj = i->b;
                    j = i;
                    did_push = true;
                }
            }
            else if (i->b == location) {
                if (i->a < minj) {
                    minj = i->a;
                    j = i;
                    did_push = true;
                }
            }
            ++i;
        }
        if (did_push) {
            vertexes.push(location);
            location = minj;
            edges.erase(j);
        }
        else {
            Circuit[pos] = location;
            pos ++;
            if (!vertexes.empty()) {
                location = vertexes.top();
                vertexes.pop();
            }
        }
    }
    

    
    ofstream fout ("fence.out");
    //cout << pos << endl;
    for (int i = F; i >-1; --i) {
        fout << Circuit[i] << endl;
    }
    
    fout.close();
    
    return 0;
}


















