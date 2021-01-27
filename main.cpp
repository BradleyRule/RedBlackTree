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
  //create head pointer, running boolean, char[] input, the number input
  tNode* head = NULL;
  bool running = true;
  char input[60];
  int number;
  
  while(running){//while running is true
    for(int i = 0; i < 60; i++){//clear input
      input[i] = '\0';
    }

    //get input 
    cout << "What would you like to do? (insert, print, quit)" << endl;
    cin.get(input, 60);
    cin.get();


    //call functions based on input to perform stated actions
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

void reColor(tNode* node){//check the color of a node and make it the opposite
  if(node->isRed()){
    node->setColor(false);
  }
  else{
    node->setColor(true);
  }
}

void rotateLeft(tNode* node, tNode* &head){
  //rightT is node's Right child
  tNode* rightT = node->getRChild();

  if(node->getRChild() != NULL){//if the right child exists
    //set node's right child to rightT's left child
    node->setRChild(rightT->getLChild());
    if(rightT->getLChild()){//if rightT has a left child
      //set the child's parent as node
      rightT->getLChild()->setParent(node);
    }
    //set rightT's parent to node's parent
    rightT->setParent(node->getParent());

    if(node->getParent() == NULL){//if node is the head
      //set rightT to head
      head = rightT;
    }
    else if(node == node->getParent()->getLChild()){//if node is left child of its parent
      //set rightT as the new left child
      node->getParent()->setLChild(rightT);
    }
    else{//if node is right child of its parent
      //set rightT as the new right child
      node->getParent()->setRChild(rightT);
    }

    //set node as rightT's left child
    rightT->setLChild(node);
    //set node's parent as rightT
    node->setParent(rightT);
  }
}

void rotateRight(tNode* node, tNode* &head){//opposite of rotate left
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
  if(root){//if there is a tree
    //set the grandparent
    grandParent = parent->getParent();
    //get uncle if there is a grandparent
    if(grandParent){
      if(grandParent->getLChild() == parent){
	uncle = grandParent->getRChild();
      }
      else{
	uncle = grandParent->getLChild();
      }
    }
  }

  
  
  if(root == NULL){//if there is no tree
    //create newnode and set it as the head of the tree
    tNode* newnode = new tNode();
    newnode->setData(data);
    //set color as black
    newnode->setColor(false);
    head = newnode;
  }
  else if(root){//if there is a tree, add the newnode to the parent node
    tNode* newParent = parent;
    tNode* newnode = new tNode();
    newnode->setData(data);
    newnode->setParent(newParent);
    
    if(isLChild){//determine which child newnode should be
      parent->setLChild(newnode);
    }
    else{
      parent->setRChild(newnode);
    }

    
    while(parent->isRed() && newnode->isRed()){//if parent and newnode are red
      if(uncle != NULL){
	if(uncle->isRed()){//if uncle is red
	  //recolor and recheck
	  reColor(uncle);
	  reColor(parent);
	  if(grandParent != root){
	    reColor(grandParent);
	  }
	  //reset the newnode
	  newnode = grandParent;
	  if(!newnode->isRed()){//check if newnode is red
	    break;
	  }
	  //reset parent
	  parent = newnode->getParent();
	  if(!parent->isRed()){//check if parent is red
	    break;
	  }
	  //reset grandparent
	  grandParent = parent->getParent();
	  if(grandParent->getRChild() != parent){//reset uncle
	    uncle = grandParent->getRChild();
	  }
	  else{
	    uncle = grandParent->getLChild();
	  }
	  
	  if(parent->getRChild() == newnode){//check if newnode is left or right child
	    isLChild = false;
	  }
	  else{
	    isLChild = true;
	  }
	  
	}
	
	else if(!uncle->isRed()){//if uncle is black
	  if(parent == grandParent->getRChild()){//if parent is the right child
	    if(isLChild){//if newnode is a left child
	      //rotate right for to make RR case
	      rotateRight(parent, head);
	      //rotate left to balance tree
	      rotateLeft(grandParent, head);
	      //recolor
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{//if newnode is a right child
	      //already RR case, rotate to balance and recolor
	      rotateLeft(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  else{//if parent is the left child
	    if(!isLChild){//if newnode is a right child
	      //rotate left to make LL case
	      rotateLeft(parent, head);
	      //rotate right to balance tree
	      rotateRight(grandParent, head);
	      //recolor 
	      reColor(grandParent);
	      reColor(newnode);
	    }
	    else{
	      //already LL case, rotate right to balance and recolor
	      rotateRight(grandParent, head);
	      reColor(grandParent);
	      reColor(parent);
	    }
	  }
	  //break out of while loop
	  break;
	}
      }
      else{//if uncle is null (black) (same as if uncle is black)
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
	    else{//if newnode is a left child
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
  if(head == NULL){//if there is no head call insert immediately
    insert(head, head, data, true);
  }
  else{//walk down the tree to find where the data should be inserted
    tNode* temp = head;
    while(temp != NULL){//while the end of a branch hasn't been reached
      if(data < temp->getData()){//if data is smaller than temp
	if (temp->getLChild() == NULL){//if currently at the end of the branch
	  //call insert and set temp to null
	  insert(temp, head, data, true);
	  temp = NULL;
	}
	else{//if not at the end of a branch
	  //advance down the tree
	  temp = temp->getLChild();
	}
      }
      else if(data >= temp->getData()){//if data is greater than or equal to temp
	if(temp->getRChild() == NULL){//if currently at the end of the branch
	  //call insert and set temp to null
	  insert(temp, head, data, false);
	  temp = NULL;
	}
	else{//if not at the end of a branch
	  //advance down the tree
	  temp = temp->getRChild();
	}
      }
    }
  }
}

void printWrapper(tNode* root){//wrapper for print function
  print(root, 0);
  cout << endl;
}

void print(tNode* root, int count){
  if(root){//if root exists
    //call print on right child incrementing count
    print(root->getRChild(), count+1);
    //output number of indents equal to the count
    for(int i = 0; i < count; i++){
      cout << "\t";
    }
    //output the data and the color of the node
    cout << root->getData();
    if(root->isRed()){
      cout << "R" << endl;
    }
    else{
      cout << "B" << endl;
    }
    //call print on the left child incrementing count by 1
    print(root->getLChild(), count+1);
  }
}


void fileInput(tNode* &head){
  char fileName[60];
  cout << "Enter the name of the file you want to use (example.txt)" << endl;

  int tempNum = 0;

  //get name of file
  cin.get(fileName, 60);
  cin.get();

  //create file object
  ifstream file (fileName);

  if(file.is_open()){
    while(!file.eof()){
      //add each number in file into the tree
      file >> tempNum;
      addNode(head, tempNum);
    }
  }
}
