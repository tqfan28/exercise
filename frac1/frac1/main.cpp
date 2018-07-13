//
//  main.cpp
//  palsquare
//
//  Created by TFAN on 2017/9/22.
//  Copyright © 2017年 TFAN. All rights reserved.
//

/*
 ID: tfan0328
 PROG: frac1
 LANG: C++
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>


using namespace std;
int N;
const int MAX = 160;
//int fractions[MAX][2] = {};

struct Node
{
    int fraction[2];
    struct Node *next;
};

bool isEqual(Node* node1, Node* node2) {
    if ( (node1->fraction[0] == node2->fraction[0]) && (node1->fraction[1] == node2->fraction[1]))
        return true;
    else
        return false;
}

bool isSecondBigger(Node* node1, Node* node2) {
    if ( (float(node1->fraction[0])/float(node1->fraction[1])) < (float(node2->fraction[0])/float(node2->fraction[1])))
        return true;
    else
        return false;
}

void sort_insert(struct Node** head_ref, int* new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    
    new_node->fraction[0]  = new_data[0];
    new_node->fraction[1]  = new_data[1];
    new_node->next = NULL;
    
    bool did_break = false;
    Node** pre_head_ref = head_ref;
    while ( head_ref != NULL) {
        if (isEqual(new_node, *head_ref)) {
            did_break = true;
            break;
        }
        else if (isSecondBigger(new_node,*head_ref)) {
            new_node->next = *head_ref;
            (*pre_head_ref)->next = new_node;
            did_break = true;
            break;
        }
        pre_head_ref = head_ref;
        if ((*head_ref)->next != NULL) {
            head_ref = &((*head_ref)->next);
        }
        else
            head_ref = NULL;
    }
    if (!did_break) {
        (*pre_head_ref)->next = new_node;
        new_node->next = NULL;
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool reduced_form(int* data) {
    if ( (data[0] == 1) || (data[1] == 1) )
        return true;
    else {
        int GCD = gcd(data[0], data[1]);
        if (GCD == 1)
            return true;
        else {
            data[0] = data[0]/GCD;
            data[1] = data[1]/GCD;
            return false;
        }
    }
}

void print_node (Node * node) {
    cout << (node->fraction)[0] << '/' << (node->fraction)[1] << endl;
}

int main(int argc, const char * argv[]) {
    
    ifstream fin ("frac1.in");
    fin >> N;
    
    struct Node* head = (struct Node*) malloc(sizeof(struct Node));
    head->fraction[0] = 0;
    head->fraction[1] = 1;
    head->next = NULL;
    
//    //test print_node
//    print_node(head);

    int new_data[2];
    Node ** head_ref = &head;
    
//    //test reduced_form
//    new_data[0] = 1;
//    new_data[1] = 1;
//    cout << reduced_form(new_data) <<endl;
//    cout << new_data[0] << endl;
//    cout << new_data[1] << endl;
//
//    //test sort_insert
//
//    new_data[0] = 0;
//    new_data[1] = 1;

//    reduced_form(new_data);
//    head_ref = &head;
//    sort_insert(head_ref, new_data);
//    new_data[0] = 1;
//    new_data[1] = 1;
//    reduced_form(new_data);
//    head_ref = &head;
//    sort_insert(head_ref, new_data);
//    new_data[0] = 1;
//    new_data[1] = 2;
//    reduced_form(new_data);
//    head_ref = &head;
//    sort_insert(head_ref, new_data);
//    while(*head_ref != NULL) {
//        print_node (*head_ref);
//        head_ref = &((*head_ref)->next);
//    }

    
//    //test isEqual
//    struct Node* node1 = (struct Node*) malloc(sizeof(struct Node));
//    node1->fraction[0] = 1;
//    node1->fraction[1] = 1;
//    struct Node* node2 = (struct Node*) malloc(sizeof(struct Node));
//    node2->fraction[0] = 1;
//    node2->fraction[1] = 1;
//    cout << "look" << isEqual(node1, node2) << endl;
    
    
    for (int j = 1; j < N+1; ++j) {
        for (int i = 1; i < j+1; ++i) {
            new_data[0] = i;
            new_data[1] = j;
            head_ref = &head;
            reduced_form(new_data);
            sort_insert(head_ref, new_data);
        }
    }
    
    ofstream fout ("frac1.out");
    head_ref = &head;
    while(head_ref != NULL) {
        fout << ((*head_ref)->fraction)[0] << '/' << ((*head_ref)->fraction)[1] << endl;
        if ((*head_ref)->next != NULL)
            head_ref = &((*head_ref)->next);
        else
            head_ref = NULL;
    }

    fout.close();
    
    return 0;
}












