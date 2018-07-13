//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: lamps
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>


using namespace std;
int N;
int C;
int constraints[4] = {};

int type(int i) {
    if ( i%2 == 0 && (i-1)%3 != 0)
        return 0;
    else if ( i%2 == 0 && (i-1)%3 == 0)
        return 1;
    else if ( i%2 != 0 && (i-1)%3 != 0)
        return 2;
    else
        return 3;
}

struct node {
    int data;
    node* next;
};

node* newNode(int value) {
    node* temp = (node*) malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

void sortedInsert(node** head_ref, node* new_node) {
    node* current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void deleteList(struct node** head_ref) {
    /* deref head_ref to get the real head */
    node* current = *head_ref;
    node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    /* deref head_ref to affect the real head back
     in the caller. */
    *head_ref = NULL;
}


int main(int argc, const char * argv[]) {
    
    bool possible[8][4];
    int moves[8][2];
    
    // 4 1 3 2
    
    //all off
    possible[0][0] = 0;
    possible[0][1] = 0;
    possible[0][2] = 0;
    possible[0][3] = 0;
    moves[0][0] = 1;
    moves[0][1] = 2;
    
    //even and 3k+1, odd and not 3k+1 on, others off
    possible[1][0] = 0;
    possible[1][1] = 1;
    possible[1][2] = 1;
    possible[1][3] = 0;
    moves[1][0] = 2;
    moves[1][1] = 3;
    
    
    //even on odd off
    possible[2][0] = 1;
    possible[2][1] = 1;
    possible[2][2] = 0;
    possible[2][3] = 0;
    moves[2][0] = 1;
    moves[2][1] = 2;
    
    //not 3k+1 on
    possible[3][0] = 1;
    possible[3][1] = 0;
    possible[3][2] = 1;
    possible[3][3] = 0;
    moves[3][0] = 1;
    moves[3][1] = 4;
    
    
    // only 3k+1 on
    possible[4][0] = 0;
    possible[4][1] = 1;
    possible[4][2] = 0;
    possible[4][3] = 1;
    moves[4][0] = 2;
    moves[4][1] = 3;
    
    //even off odd on
    possible[5][0] = 0;
    possible[5][1] = 0;
    possible[5][2] = 1;
    possible[5][3] = 1;
    moves[5][0] = 1;
    moves[5][1] = 2;
    

    //even and not 3k+1, odd and 3k+1 on, others off
    possible[6][0] = 1;
    possible[6][1] = 0;
    possible[6][2] = 0;
    possible[6][3] = 1;
    moves[6][0] = 2;
    moves[6][1] = 3;
    
    //all on
    possible[7][0] = 1;
    possible[7][1] = 1;
    possible[7][2] = 1;
    possible[7][3] = 1;
    moves[7][0] = 0;
    moves[7][1] = 3;

    
    ifstream fin ("lamps.in");
    fin >> N >> C;
    int current;
    fin >> current;
    int current_type;
    while (current != -1) {
        current_type = type(current);
        constraints[current_type] = 1;
        fin >> current;
    }
    fin >> current;
    
     ofstream fout ("lamps.out");
    
    while (current != -1) {
        current_type = type(current);
        if (constraints[current_type] != 0 && constraints[current_type] != -1) {
            fout << "IMPOSSIBLE"<< endl;
            return 0;
        }
        else {
            constraints[current_type] = -1;
        }
        fin >> current;
    }
    
    
    // C = 1
    // 0 2 3 5
    // C = 2
    // 0 1 2 4 5 6 7
    // C >= 3
    // all possible
    
    bool ok[8] = {};
    
    // 1 2 3 4 5 6
    for (int j = 0; j < 8; ++j) {
        for (int i = 1; i < 7; ++i) {
            int type_i = type(i);
            if (constraints[type_i] != 0) {
                if ( (possible[j][type_i] == 0 && constraints[type_i] == -1)
                    || (possible[j][type_i] == 1 && constraints[type_i] == 1)) {
                    ok[j] = true;
                }
                else {
                    //cout << j << "here";
                    ok[j] = false;
                    break;
                }
            }
            else {
                ok[j] = true;
            }
        }
    }
    //cout << ok[7];
    
    if (C == 0) {
        ok[0] = false;
        ok[1] = false;
        ok[2] = false;
        ok[3] = false;
        ok[4] = false;
        ok[5] = false;
        ok[6] = false;
    }
    else if (C == 1) {
        ok[1] = false;
        ok[4] = false;
        ok[6] = false;
        ok[7] = false;
    }
    
    else if (C == 2) {
        ok[3] = false;
    }
    
    int counter = 0;
    for (int i = 0; i < 8; ++i) {
        if (ok[i]) {
            for (int j = 1; j < N+1; ++j) {
                fout << possible[i][type(j)];
                counter ++;
            }
            fout << endl;
        }
    }
    if (counter == 0) {
        fout << "IMPOSSIBLE"<<endl;
    }
    
    fout.close();
    
    return 0;
}



















