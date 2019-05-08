#ifndef MYNODE_H_INCLUDED
#define MYNODE_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

struct Edge{
    string attribute; 
    int childnodenum;   
    Edge(int b){
        attribute="",childnodenum=b;
    }
    Edge(string a="",int b=0){
        attribute=a,childnodenum=b;
    }
};
struct Node{
  vector<Edge>edgelist;
  vector<string>attribute;

  int index;
  int leftmost;
  string nodename;
  Node(){
    edgelist.clear();
  }
  Node(vector<Edge>e,string name){
     edgelist = e,nodename=name;
  }
};


#endif 