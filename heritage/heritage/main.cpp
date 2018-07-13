
/*
 ID: tfan0328
 PROG: heritage
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
#include <cmath>


using namespace std;
const int infty = 0x7fffffff;
string s;

struct node {
    char c;
    node* left;
    node* right;
};

struct node* newNode(char c)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    
    node->c = c;
    
    node->left = NULL;
    node->right = NULL;
    return(node);
}

struct node* subtree(string s1, string s2) {
    if (s1.length() == 0) {
        return NULL;
    }
    else if (s1.length() == 1) {
        return newNode(s2[0]);
    }
    else {
        node* root = newNode(s2[0]);
        int j = 0;
        while(j < s1.length() && s1[j] != s2[0]) {
            ++j;
        }
        if (j != 0)
            root->left = subtree(s1.substr(0, j), s2.substr(1, j));
        if (j != s1.length()-1)
            root->right = subtree(s1.substr(j+1, s1.length()-j-1), s2.substr(j+1, s1.length()-j-1));
        return root;
    }
}

void print(node* root) {
    if (root->left == NULL && root->right == NULL) {
        s += root->c;
    }
    else if (root->left != NULL && root->right == NULL){
        print(root->left);
        s += root->c;
    }
    else if (root->right != NULL && root->left == NULL){
        print(root->right);
        s += root->c;
    }
    else {
        print(root->left);
        print(root->right);
        s += root->c;
    }
}

int main(int argc, const char * argv[]) {
    
    string s1, s2;
    ifstream fin ("heritage.in");
    getline(fin, s1);
    getline(fin, s2);
    
    node* root = subtree(s1, s2);
    print(root);
    ofstream fout ("heritage.out");
    fout << s << endl;
    fout.close();
    return 0;
}
























