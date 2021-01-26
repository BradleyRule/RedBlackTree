#include "tNode.h"
#include <iostream>
#include <cstring>

using namespace std;

tNode::tNode(){
  lChild = NULL;
  rChild = NULL;
  parent = NULL;
  color = true;
}

tNode::~tNode(){
  parent = NULL;
  lChild = NULL;
  rChild = NULL;
}

void tNode::setRChild(tNode* newnode){
  rChild = newnode;
}

void tNode::setLChild(tNode* newnode){
  lChild = newnode;
}

tNode* tNode::getLChild(){
  return lChild;
}

tNode* tNode::getRChild(){
  return rChild;
}

void tNode::setData(int expression){
  data = expression;
}

int tNode::getData(){
  return data;  
}

void tNode::setColor(bool value){
  color = value;//true = red
}

bool tNode::isRed(){
  return color;
}

void tNode::setParent(tNode* node){
  parent = node;
}

tNode* tNode::getParent(){
  return parent;
}
