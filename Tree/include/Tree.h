#ifndef TREE_H
#define TREE_H
#include "mynode.h"
#include <bits/stdc++.h>
using namespace std;

class Tree
{
public:
    Tree();
    Tree(vector<Node>t, int b);
     ~Tree();
    vector <Node> nodelist;
    int root;
    vector <int> left;     
    vector <int> keyroots; 
    vector <string>labels; 
    void traverse();
    void traverse(int node);
    void getindex();
    int getindex(int node, int index);
    void getleftarr();
    void getleftarr(int node);
    void getnodeleft();
    void getnodeleft(int node);
    void getkeyroots();
protected:

private:

};

#endif // TREE_H
