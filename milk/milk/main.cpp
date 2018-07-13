//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: milk
 LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void quick_sort(int arr1 [], int arr2 [], int left, int right) {
    int i = left;
    int j = right;
    int tmp1;
    int tmp2;
    int pivot = arr1[(left + right)/2];
    
    while (i <= j) {
        while (arr1[i] < pivot)
            ++i;
        while (arr1[j] > pivot)
            --j;
        if (i <= j) {
            tmp1 = arr1[i];
            tmp2 = arr2[i];
            arr1[i] = arr1[j];
            arr2[i] = arr2[j];
            arr1[j] = tmp1;
            arr2[j] = tmp2;
            ++i;
            --j;
        }
    }
    if (left < j)
        quick_sort(arr1, arr2, left, j);
    if (i < right)
        quick_sort(arr1, arr2, i, right);
}

int main(int argc, const char * argv[]) {
    
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    //N: milk needed
    //M: number of farmers
    int N;
    int M;
    fin >> N >> M;
    //P: prices
    //A: amount avaiable
    
    int P [M];
    int A [M];
    
    for (int i = 0; i < M; ++i) {
        fin >> P[i] >> A[i];
    }
    
    quick_sort(P, A, 0, M-1);
    
    int payment = 0;
    for (int i = 0; i < M; ++i) {
        if (N - A[i] > 0){
            payment += A[i]*P[i];
            N -= A[i];
        }
        else {
            payment += N*P[i];
            break;
        }
    }
    
    fout << payment << endl;
    //std::cout << "Hello, World!\n";
    return 0;
}


