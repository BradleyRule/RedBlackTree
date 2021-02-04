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
bool deleteSearch(tNode*&, tNode*, tNode*, int);
void deleteSWrapper(tNode*&, int);
void deleteNode(tNode*&, tNode*, tNode*, int);
void repairNode(tNode*, tNode*&);
//void repairWrapper(tNode*, tNode*);
void searchTWrapper(tNode*, int);
bool search(tNode*, int);

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
    cout << "What would you like to do? (insert, print, quit, delete, search)" << endl;
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
    else if(strcmp(input, "delete") == 0){
      cout << "What number do you want to delete? " << endl;
      cin >> number;
      cin.get();
      deleteSWrapper(head, number);
    }
    else if(strcmp(input, "search") == 0){
      cout << "What number would you like to search for?" << endl;
      cin >> number;
      cin.get();
      searchTWrapper(head, number);
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

void deleteSWrapper(tNode* &root, int data){
  if(deleteSearch(root, root, root, data)){
    cout << data << " was successfully deleted." << endl;
  }
  else{
    cout << data << " was not found." << endl;
  }
}

bool deleteSearch(tNode* &root, tNode* parent, tNode* child, int data){
  if(!child){
    return false;
  }
  else{
    if(data == child->getData()){
      if(parent == child){
	//	deleteRoot(root);
      }
      else{
	cout << "node found" << endl; //DELETE LATER
	deleteNode(root, parent, child, data);
      }
      return true;
    }
    else if(data < child->getData()){
      return deleteSearch(root, child, child->getLChild(), data);
    }
    else if(data >= child->getData()){
      return deleteSearch(root, child, child->getRChild(), data);
    }
  }

}

void deleteNode(tNode* &head, tNode* parent, tNode* child, int data){
  tNode* temp;
  tNode* previous;
  bool isLChild;

  //determine if child is left or right
  if(parent->getLChild()){
    if(parent->getLChild()->getData() == data){
      isLChild = true;
    }
  }
  else if(parent->getRChild()){
    if(parent->getRChild()->getData() == data){
      isLChild = false;
    }
  }

  //CASE 1 (No children)
  if(child->getLChild() == NULL && child->getRChild() == NULL){
    cout << "CASE 1" << endl; //DELETE LATER
    if(isLChild){//if left child
      if(child->isRed()){//deleted node is red
	delete child;
	parent->setLChild(NULL);
      }
      else{//deleted node is black
	//	repairWrapper(head, child);
      }
    }
    else{//if right child
      if(child->isRed()){//deleted node is red
	delete child;
	parent->setRChild(NULL);
      }
      else{//deleted node is black

      }
    }
  }
  //Case 2 (Right child absent)
  else if(child->getRChild() == NULL){
    cout << "CASE 2" << endl; //DELETE LATER
    if(isLChild){//child is LChild
      if(child->isRed()){//child is red
	parent->setLChild(child->getLChild());
	delete child;
      }
      else{//child is black
	if(child->getLChild()->isRed()){
	  child->setData(child->getLChild()->getData());
	  delete child->getLChild();
	  child->setLChild(NULL);
	}
	else{

	}
      }
    }
    else{//child is RChild
      if(child->isRed()){//child is red
	parent->setRChild(child->getLChild());
	delete child;
      }
      else{//child is black
	if(child->getLChild()->isRed()){
	  child->setData(child->getLChild()->getData());
	  delete child->getLChild();
	  child->setLChild(NULL);
	}
	else{
	  
	}
      }
    }
  }
  //CASE 3 (right child is present)
  else if(child->getRChild()){
    cout << "CASE 3" << endl; //DELETE LATER
    
    temp = child->getRChild();
    previous = child;
    while(temp->getLChild()){
      previous = temp;
      temp = temp->getLChild();
    }
    
    child->setData(temp->getData());
  
      if(temp->isRed()){//if temp is red
	if(previous->getRChild() == temp){//if temp is RChild
	  if(temp->getRChild()){
	    previous->setRChild(temp->getRChild());
	    temp->getRChild()->setParent(previous);
	    delete temp;
	  }
	  else{
	    previous->setRChild(NULL);
	    delete temp;
	  }
	}
	else{// if temp is LChild
	  if(temp->getRChild()){
	    previous->setLChild(temp->getRChild());
	    temp->getRChild()->setParent(previous);
	    delete temp;
	  }
	  else{
	    previous->setLChild(NULL);
	    delete temp;
	  }
	}
	
      }
      else{//if temp is black
	if(previous->getRChild() == temp){//temp is RChild
	  if(temp->getRChild()){//if there is a rChild
	    if(temp->getRChild()->isRed()){//if the child is red
	      temp->setData(temp->getRChild()->getData());
	      delete temp->getRChild();
	      temp->setRChild(NULL);
	    }
	    else{//if the child is black
     
	    }
	  }
	  else{//if there is not a RChild
	    
	  }
	}
	else{//temp is LChild
	  if(temp->getRChild()){//if there is a rChild
	    if(temp->getRChild()->isRed()){//if the child is red
	      temp->setData(temp->getRChild()->getData());
	      delete temp->getRChild();
	      temp->setRChild(NULL);
	    }
	    else{//if the child is black
	      
	    }
	  }
	  else{//if there is not a RChild
	    
	  }
	}
      }
  }
}

void repairNode(tNode* x, tNode* &head){
  tNode* parent = x->getParent();
  
  if(x->getLChild()){
    if(x == parent->getRChild()){
      parent->setRChild(x->getLChild());
      x->getLChild()->setParent(parent);
    }
    else{
      parent->setLChild(x->getLChild());
      x->getLChild()->setParent(parent);
      delete x;
    }
  }
  else if(x->getRChild()){
    if(x == parent->getRChild()){
      parent->setRChild(x->getRChild());
      x->getRChild()->setParent(parent);
    }
    else{
      parent->setLChild(x->getRChild());
      x->getRChild()->setParent(parent);
    }
  }
}

void searchTWrapper(tNode* root, int data){
  if(search(root, data)){//if returns true
    //tell user the data is in the tree
    cout << data << " is in the tree!" << endl;
  }
  else{//if returns false
    //tell user the data is not in the tree
    cout << data << " is not in the tree!" << endl;
  }
}

bool search(tNode* root, int data){
  if(!root){//if we reach a null pointer
    //return false
    return false;
  }
  else{
    if(data == root->getData()){//if data was found
      //return true
      return true; 
    }
    else if(data < root->getData()){//if data is less than current node's data, go left
      return search(root->getLChild(), data);
    }
    else if(data > root->getData()){//if data is greater than current node's data, go right
      return search(root->getRChild(), data);
    }
  }
}

/*
void deleteRoot(){

}


void repairWrapper(tNode* &head, tNode* x){
  tNode* sibling = NULL;
  tNode* parent = x->getParent();
  bool isLChild;

  //determine if child is left or right
  if(parent->getLChild() == x){
    isLChild = true;
  }
  else if(parent->getRChild() == x){
    isLChild = false;
  }

  if(isLChild){
    sibling = parent->getRChild();
  }
  else{
    sibling = parent->getLChild();
  }

  if(sibling){//if sibling exists
    if(sibling->isRed()){//if sibling is red
      repairCase1(head, x, sibling, parent, isChild);
    }
  }
  
}


void repairCase1(tNode* &head, tNode* x, tNode* sibling, tNode* parent, bool isLChild){

      recolor(sibling);
      recolor(parent);
      
      if(isLChild){//if x is LChild
	rotateLeft(parent);
	sibling = parent->getRChild();
      }
      else{//if x is RChild
	rotateRight(parent);
	sibling = parent->getLChild();
      }

      
}

void repairCase2(tNode* &head, tNode* x, tNode* sibling, tNode* parent, bool isLChild){

}

void repairCase3(tNode* &head, tNode* x, tNode* sibling, tNode* parent, bool isLChild){

}

void repairCase4(tNode* &head, tNode* x, tNode* sibling, tNode* parent, bool isLChild){

}

*/
