
/*
 ID: tfan0328
 PROG: gift1
 LANG: C++
 */


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[]) {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
    
    int a = 0;
    fin >> a;
    vector<string> names;
    vector<int> money;
    for (int i = 0; i < a; ++i) {
        string name;
        fin >> name;
        names.push_back(name);
        money.push_back(0);
    }
    
    while(fin) {
        string name;
        fin >> name;
        int index = find(names.begin(), names.end(), name) - names.begin();
        int m, n;
        fin >> m >> n;
        if (n != 0) {
            int give = m/n;
            money[index] = money[index] - n*(m/n);
            for (int i = 0; i < n; ++i) {
                string recieve;
                fin >> recieve;
                int index2 = find(names.begin(), names.end(), recieve) - names.begin();
                money[index2] = money[index2] + (m/n);
            }
        }
    }
    
    for (int i = 0; i < a; ++i) {
        fout << names[i] << ' ' << money[i] << endl;
    }
    return 0;
}
