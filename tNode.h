#ifndef TNODE
#define TNODE

#include <iostream>
#include <cstring>

using namespace std;

class tNode{
 public:
  tNode();
  ~tNode();
  void setRChild(tNode*);
  void setLChild(tNode*);
  tNode* getLChild();
  tNode* getRChild();
  void setData(int);
  int getData();
  void setColor(bool);
  bool isRed();
  void setParent(tNode*);
  tNode* getParent();
  
 private:
  tNode* lChild;
  tNode* rChild;
  tNode* parent;
  int data;
  bool color;//red if true  
};
#endif
