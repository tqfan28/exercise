//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: pprime
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int a;
int b;
int const MAX = 100000;
int Palindromes[MAX]={};

//int firstDigit(int a) {
//    int first = a;
//    while(a > 9) {
//        a /= 10;
//    }
//    return first;
//}
//
//int lastDigit(int a) {
//    return a % 10;
//}
//
//int getLength(int a) {
//    int Length = 1;
//    while(a > 9) {
//        Length ++;
//        a /= 10;
//    }
//    return Length;
//}
//
//int generatePalindromeEven(int i) {
//    int j = i;
//    int k = i;
//    while (k > 0) {
//        j = j * 10 + k % 10;
//        k = k / 10;
//    }
//    //cout << j << endl;
//    return j;
//}
//
//int generatePalindromeOdd(int i) {
//    int j = i;
//    int k = i/10;
//    while (k > 0) {
//        j = j * 10 + k % 10;
//        k = k / 10;
//    }
//    ///cout << j << endl;
//    return j;
//}
//
//int Exp(int i) {
//    if (i == 0)
//        return 1;
//    else
//        return 10*Exp(i-1);
//}
//
//void generatePalindromes(int a, int b) {
//    int peven;
//    int podd;
//    int end = b/Exp(getLength(b)/2)+1;
//
//    for (int i = 1; i < end+1; i++) {
//        podd = generatePalindromeOdd(i);
//        peven = generatePalindromeEven(i);
//        if (podd >= a && podd <= b)
//            Palindromes[podd] = 1;
//        if (peven >= a && peven <= b)
//            Palindromes[peven] = 1;
//    }
//}
//
//bool check_prime(int n) {
//    //cout << n << endl;
//    if (n == 1)
//        return false;
//    if (n == 2) {
//        return true;
//    }
//    else if (n == 3) {
//        return true;
//    }
//    else if (n % 2 == 0)
//        return false;
//    else if (n % 3 == 0)
//        return false;
//    int i = 5;
//    int w = 2;
//    while (i* i <= n) {
//        if (n % i == 0)
//            return false;
//        i += w;
//        w = 6 - w;
//    }
//    return true;
//}
//
//int main(int argc, const char * argv[]) {
//
//
//    ifstream fin ("pprime.in");
//    fin >> a >> b;
//    //check_prime(11);
//    generatePalindromes(a, b);
//
//    ofstream fout ("pprime.out");
//    for (int i = a; i < b +1; ++i) {
//        if (Palindromes[i] == 1 && check_prime(i)) {
//            fout << i << endl;
//        }
//    }
//
//    fout.close();
//
//    return 0;
//}




int getLength(int a) {
    int Length = 1;
    while(a > 9) {
        Length ++;
        a /= 10;
    }
    return Length;
}

int generatePalindromeEven(int i) {
    int j = i;
    int k = i;
    while (k > 0) {
        j = j * 10 + k % 10;
        k = k / 10;
    }
    //cout << j << endl;
    return j;
}

int generatePalindromeOdd(int i) {
    int j = i;
    int k = i/10;
    while (k > 0) {
        j = j * 10 + k % 10;
        k = k / 10;
    }
    ///cout << j << endl;
    return j;
}

int Exp(int i) {
    if (i == 0)
        return 1;
    else
        return 10*Exp(i-1);
}

int generatePalindromes(int a, int b) {
    int counter = 0;
    int peven;
    int podd;
    int end = b/Exp(getLength(b)/2 -1);
    //cout << "end" << end << endl;
    
    for (int i = 1; i < end+1; i++) {
        podd = generatePalindromeOdd(i);
        peven = generatePalindromeEven(i);
        if (podd >= a && podd <= b) {
            Palindromes[counter] = podd;
            counter ++;
        }
        if (peven >= a && peven <= b) {
            Palindromes[counter] = peven;
            counter ++;
        }
    }
    return counter;
}

bool check_prime(int n) {
    //cout << n << endl;
    if (n == 1)
        return false;
    if (n == 2) {
        return true;
    }
    else if (n == 3) {
        return true;
    }
    else if (n % 2 == 0)
        return false;
    else if (n % 3 == 0)
        return false;
    int i = 5;
    int w = 2;
    while (i* i <= n) {
        if (n % i == 0)
            return false;
        i += w;
        w = 6 - w;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("pprime.in");
    fin >> a >> b;
    
    int counter = generatePalindromes(a, b);
    
    ofstream fout ("pprime.out");
    //cout << "counter" << counter << endl;
    //cout << "last" << Palindromes [counter-1] << endl;
    sort(Palindromes, Palindromes + counter);
    //cout << generatePalindromeOdd(1001) << endl;
    for (int i = 0; i < counter ; ++i) {
        if (check_prime(Palindromes[i])) {
            fout << Palindromes[i] << endl;
        }
    }
    
    fout.close();
    
    return 0;
}









