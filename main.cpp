#include <iostream>
#include <cstring>
#include <fstream>
#include "tNode.h"


using namespace std;

void rotateLeft(tNode*, tNode*&);
void rotateRight(tNode*, tNode*&);
void reColor(tNode*);
void insert(tNode*, tNode*&, int, bool);
void printWrapper(tNode*);
void print(tNode*, int);
void addNode(tNode*&, int);
void fileInput(tNode*&);

int main(){
  tNode* head = NULL;
  bool running = true;
  char input[60];
  int number;
  
  while(running){
    for(int i = 0; i < 60; i++){
      input[i] = '\0';
    }

    cout << "What would you like to do? (insert, print, quit)" << endl;
    cin.get(input, 60);
    cin.get();

    if(strcmp(input, "print") == 0){
      printWrapper(head);
    }
    else if(strcmp(input, "insert") == 0){
      for(int i = 0; i < 60; i++){
	input[i] = '\0';
      }

      cout << "Would you like to insert manually or by file (enter: 'file' or 'manual')" << endl;
      cin.get(input, 60);
      cin.get();
      
      if(strcmp(input, "manual") == 0){
	cout << "What number do you want to add?" << endl;
	cin >> number;
	cin.get();
	addNode(head, number);
      }
      else if(strcmp(input, "file") == 0){
	fileInput(head);
      }
	
    }
    else if(strcmp(input, "quit") == 0){
      running = false;
    }
  }







  
  return 0;
}

void reColor(tNode* node){
  if(node->isRed()){
    node->setColor(false);
  }
  else{
    node->setColor(true);
  }
}

void rotateLeft(tNode* node, tNode* &head){
  tNode* rightT = node->getRChild();

  if(node->getRChild() != NULL){
    node->setRChild(rightT->getLChild());
    if(rightT->getLChild()){
      rightT->getLChild()->setParent(node);
    }
    rightT->setParent(node->getParent());

    if(node->getParent() == NULL){
      head = rightT;
    }
    else if(node == node->getParent()->getLChild()){
      node->getParent()->setLChild(rightT);
    }
    else{
      node->getParent()->setRChild(rightT);
    }
    
    rightT->setLChild(node);
    node->setParent(rightT);
  }
}

void rotateRight(tNode* node, tNode* &head){
  tNode* leftT = node->getLChild();
  
  if(node->getLChild() != NULL){
    node->setLChild(leftT->getRChild());
    if(leftT->getRChild()){
      leftT->getRChild()->setParent(node);
    }

    leftT->setParent(node->getParent());
    
    if(node->getParent() == NULL){
      head = leftT;
    }
    else if(node == node->getParent()->getLChild()){
      node->getParent()->setLChild(leftT);
    }
    else if(node == node->getParent()->getRChild()){
      node->getParent()->setRChild(leftT);
    }
    leftT->setRChild(node);
    node->setParent(leftT);
  }
}

void insert(tNode* parent, tNode* &head, int data, bool isLChild){
  tNode* root = head;
  tNode* grandParent = NULL;
  tNode* uncle = NULL;
  if(root){
    grandParent = parent->getParent();
    //get uncle
    if(grandParent){
      if(grandParent->getLChild() == parent){
	uncle = grandParent->getRChild();
      }
      else{
	uncle = grandParent->getLChild();
      }
    }
  }

  
  
  if(root == NULL){
    tNode* newnode = new tNode();
    newnode->setData(data);
    newnode->setColor(false);
    head = newnode;
  }
  else if(root){
    tNode* newParent = parent;
    tNode* newnode = new tNode();
    newnode->setData(data);
    newnode->setParent(newParent);
    
    if(isLChild){
      parent->setLChild(newnode);
    }
    else{
      parent->setRChild(newnode);
    }

    
    while(parent->isRed() && newnode->isRed()){//if parent and newnode are red
      cout << "test 1" << endl;//DELETE LATER
      if(uncle != NULL){
	cout << "test 2" << endl;//DELETE LATER
	if(uncle->isRed()){//if uncle is red
	  cout << "red U" << endl;//DELETE LATER
	  reColor(uncle);
	  reColor(parent);
	  if(grandParent != root){
	    reColor(grandParent);
	  }

	  newnode = grandParent;
	  if(!newnode->isRed()){
	    break;
	  }
	  parent = newnode->getParent();
	  if(!parent->isRed()){
	    break;
	  }
	  grandParent = parent->getParent();
	  if(grandParent->getRChild() != parent){
	    uncle = grandParent->getRChild();
	  }
	  else{
	    uncle = grandParent->getLChild();
	  }
	  
	  if(parent->getRChild() == newnode){
	    isLChild = false;
	  }
	  else{
	    isLChild = true;
	  }
	  
	}
	
	else if(!uncle->isRed()){//if uncle is black
	  cout << "Black U" << endl;//DELETE LATER
	  if(parent == grandParent->getRChild()){//if parent is the right child
	    if(isLChild){//if newnode is a left child
	      rotateRight(parent, head);
	      rotateLeft(grandParent, head);
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{//if newnode is a right child
	      rotateLeft(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  else{//if parent is the left child
	    if(!isLChild){//if newnode is a right child
	      rotateLeft(parent, head);
	      rotateRight(grandParent, head);
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{
	      rotateRight(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  break;
	}
      }
      else{//if uncle is null (black)
	cout << "NULL U" << endl;//DELETE LATER
	  if(parent == grandParent->getRChild()){//if parent is the right child
	    cout << "right parent" << endl;//DELETE LATER
	    if(isLChild){//if newnode is a left child
	      cout << "left newnode" << endl;//DELETE LATER
	      rotateRight(parent, head);
	      rotateLeft(grandParent, head);
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{//if newnode is a right child
	      cout << "Right newnode" << endl;//DELETE LATER
	      rotateLeft(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  else{//if parent is the left child
	    cout << "left parent" << endl;//DELETE LATER
	    if(!isLChild){//if newnode is a right child
	      cout << "right newnode" << endl;//DELETE LATER
	      rotateLeft(parent, head);
	      rotateRight(grandParent, head);
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{//if newnode is a left child
	      cout << "left newnode" << endl;//DELETE LATER
	      rotateRight(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  break;
      }
    }
  }
}

void addNode(tNode* &head, int data){
  if(head == NULL){
    insert(head, head, data, true);
  }
  else{
    tNode* temp = head;
    while(temp != NULL){
      if(data < temp->getData()){
	if (temp->getLChild() == NULL){
	  insert(temp, head, data, true);
	  temp = NULL;
	}
	else{
	  temp = temp->getLChild();
	}
      }
      else if(data >= temp->getData()){
	if(temp->getRChild() == NULL){
	  insert(temp, head, data, false);
	  temp = NULL;
	}
	else{
	  temp = temp->getRChild();
	}
      }
    }
  }
}

void printWrapper(tNode* root){
  print(root, 0);
  cout << endl;
}

void print(tNode* root, int count){
  if(root){
    print(root->getRChild(), count+1);
    for(int i = 0; i < count; i++){
      cout << "\t";
    }
    cout << root->getData();
    if(root->isRed()){
      cout << "R" << endl;
    }
    else{
      cout << "B" << endl;
    }
    print(root->getLChild(), count+1);
  }
}


void fileInput(tNode* &head){
  char fileName[60];
  cout << "Enter the name of the file you want to use (example.txt)" << endl;

  int tempNum = 0;
  
  cin.get(fileName, 60);
  cin.get();

  ifstream file (fileName);

  if(file.is_open()){
    while(!file.eof()){
      file >> tempNum;
      addNode(head, tempNum);
    }
  }
}
