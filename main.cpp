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
void DBRepair(tNode*, tNode*&, tNode*);
void searchTWrapper(tNode*, int);
bool search(tNode*, int);

int main(){
  //create head pointer, running boolean, char[] input, the number input
  tNode* head = NULL;
  bool running = true;
  char input[60];
  int number;
  
  while(running){//while running is true
    for(int i = 0; i <= 60; i++){//clear input
      input[i] = '\0';
    }

    cout << endl;
    
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
      //ask for manual or file input
      cout << "Would you like to insert manually or by file (enter: 'file' or 'manual')" << endl;
      cin.get(input, 60);
      cin.get();
      
      if(strcmp(input, "manual") == 0){//get a number via cin
	cout << "What number do you want to add?" << endl;
	//get number
	cin >> number;
	cin.get();
	//add number
	addNode(head, number);
      }
      else if(strcmp(input, "file") == 0){//read in all numbers in a file
	fileInput(head);
      }
	
    }
    else if(strcmp(input, "quit") == 0){//end the program
      running = false;
    }
    else if(strcmp(input, "delete") == 0){//remove a number from the tree
      cout << "What number do you want to delete? " << endl;
      //get number to delete
      cin >> number;
      cin.get();
      //start search for number to delete
      deleteSWrapper(head, number);
    }
    else if(strcmp(input, "search") == 0){//search tree for a number
      cout << "What number would you like to search for?" << endl;
      //get number to search for
      cin >> number;
      cin.get();
      //call search function
      searchTWrapper(head, number);
    }
  }







  
  return 0;
}

void reColor(tNode* node){//check the color of a node and make it the opposite
  if(node->isRed()){//if red
    //set to black
    node->setColor(false);
  }
  else{//if black
    //set to red
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
    if(grandParent){//if there is a grandparent
      if(grandParent->getLChild() == parent){//if parent is LCHild
	//set RChild as uncle
	uncle = grandParent->getRChild();
      }
      else{//parent is RChild
	//set uncle as LChild
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

void deleteSWrapper(tNode* &root, int data){//wrapper function for delete
  //if the node to be deleted is found, this function will return true and tell the user it was found
  if(deleteSearch(root, root, root, data)){
    cout << data << " was successfully deleted." << endl;
  }
  else{
    cout << data << " was not found." << endl;
  }
}

bool deleteSearch(tNode* &root, tNode* parent, tNode* child, int data){//recusrsive function that searches for the node to be deleted (very similar to search but it also keeps track of parent and root to pass into delete function
  if(!child){
    return false;
  }
  else{
    if(data == child->getData()){
      deleteNode(root, parent, child, data);
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

void deleteNode(tNode* &head, tNode* parent, tNode* child, int data){//finding actual node to delete(first step of deletion)
  //tNode pointers and boolean to tell if node is left or right child
  tNode* temp;
  tNode* previous;
  bool isLChild;


  //determine if child is left or right
  //only try if there is a parent
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

  //CASE 0 (delete root)
  if(child == head && !child->getLChild() && !child->getRChild()){//the node being deleted is the root node
    //remove node
    delete head;
    //set head pointer to null
    head = NULL;
    return;
  }

  //check if in order successor is needed
  //CASE 1 (No children)
  if(child->getLChild() == NULL && child->getRChild() == NULL){
    repairNode(child, head);
  }
  //Case 2 (Right child absent)
  else if(child->getRChild() == NULL){
    repairNode(child, head);
  }
  //CASE 3 (right child is present)
  else if(child->getRChild()){//in order successor is needed (changes node that will be deleted
    
    temp = child->getRChild();
    previous = child;
    while(temp->getLChild()){//find in order successor (next greatest number in tree) of node we want to delete
      //walk down the left side of the right subtree
      previous = temp;
      temp = temp->getLChild();
    }
    //replace the original node to delete with the data from the in order successor
    child->setData(temp->getData());
    //pass in the in order successor into repair function
    repairNode(temp, head);
  }
}

void repairNode(tNode* tbd, tNode* &head){//does the bulk of basic deleteion of red nodes
  tNode* parent = tbd->getParent();
  tNode* temp = NULL;
  bool isLChild = false;

  if(parent){//if there is a parent
    if(parent->getLChild() == tbd){
      isLChild = true;
    }
    if(parent->getRChild() == tbd){
      isLChild = false;
    }
  }



  
  if(tbd->isRed()){//if the node is red
    if(tbd->getLChild()){
      if(isLChild){
	parent->setLChild(tbd->getLChild());
	tbd->getLChild()->setParent(parent);
      }
      else{
	parent->setLChild(tbd->getRChild());
	tbd->getRChild()->setParent(parent);
      }
    }
    else if(tbd->getRChild()){
      if(isLChild){
	parent->setRChild(tbd->getLChild());
	tbd->getLChild()->setParent(parent);
      }
      else{
	parent->setRChild(tbd->getRChild());
	tbd->getRChild()->setParent(parent);
      }
    }
    else{
      if(isLChild){
	parent->setLChild(NULL);
      }
      else{
	parent->setRChild(NULL);
      }
    }
    delete tbd;
    return;
  }
  else if(!(tbd->isRed())){//if the node is black
    if(tbd->getLChild()){//check if there is a LChild
      if(tbd->getLChild()->isRed()){//if there is check if red
	//if red, put child's data in tbd and delete the child
	tbd->setData(tbd->getLChild()->getData());
	temp = tbd->getLChild();
	tbd->setLChild(NULL);
	delete temp;
	return;
      }
    }
    else if(tbd->getRChild()){//same as directly above but for RChild
      if(tbd->getRChild()->isRed()){
	tbd->setData(tbd->getRChild()->getData());
	temp = tbd->getRChild();
	tbd->setRChild(NULL);
	delete temp;
	return;
      }
    }
    //if no red node could be deleted, a black node must be deleted so run DBRepair
    DBRepair(tbd, head, tbd);
  }
  
}

void DBRepair(tNode* tbd, tNode*& head, tNode* db){//handles deleting a black node

  //booleans to keep track of cases
  bool case1 = true;//sibling and sibling's children are all black
  bool case2 = true;//sibling is red
  bool case3 = true;//sibling is black, sibling's closest child to DB is red and sibling's furthest child is black.
  bool case4 = true;//sibling is black and siblings far child is red
  bool tempColor = true;//red when true, used to swap colors of nodes.
  tNode* parent = NULL;
  tNode* sibling = NULL;
  bool isLChild = false;

  while(db != NULL && db != head){//if DB is not head or NULL

    //reset the cases
    case1 = true;
    case2 = true;
    case3 = true;
    case4 = true;

    //set the parent pointer to the parent of db (double black node)
    parent = db->getParent();
    //reset isLChild
    if(parent->getLChild() == db){
      isLChild = true;
    }
    if(parent->getRChild() == db){
      isLChild = false;
    }

    //Set sibling of db
    if(isLChild){
      sibling = parent->getRChild();
    }
    else{
      sibling = parent->getLChild();
    }
    //-====CHECKING FOR CASES====-
    //rules out different cases. After checks, only one will be true until they are reset
    //requirements for the cases are stated at begining of function
    if(!sibling->isRed()){
      case2 = false;
    }
    if(sibling->isRed()){
      case4 = false;
      case1 = false;
      case3 = false;
    }
    if(sibling->getLChild()){
      if(sibling->getLChild()->isRed()){
	  case1 = false;
      }
    }
    if(sibling->getRChild()){
      if(sibling->getRChild()->isRed()){
	case1 = false;
      }
    }
    if(isLChild){//case 3 and 4 checks for when db is LChild
      if(sibling->getLChild()){
	if(!sibling->getLChild()->isRed()){
	  case3 = false;
	}
      }
      else{
	case3 = false;
      }
      if(sibling->getRChild()){
	if(sibling->getRChild()->isRed()){
	  case3 = false;
	}
	else{
	  case4 = false;
	}
      }
      else{
	case4 = false;
      }
    }
    else{//case 3 and 4 checks for when db is RChild
      if(sibling->getRChild()){
	if(!sibling->getRChild()->isRed()){
	  case3 = false;
	}
      }
      else{
	case3 = false;
      }
      if(sibling->getLChild()){
	if(sibling->getLChild()->isRed()){
	  case3 = false;
	}
	else{
	  case4 = false;
	}
      }
      else{
	case4 = false;
      }
    }
    //-====END CHECK FOR CASES====-
    
    if(case1){//CASE 1 (sibling and sibling's children are black)
      if(parent->isRed()){//increase black value of parent (if red make black, if black make double black)
	parent->setColor(false);
	sibling->setColor(true);
	db = NULL;
      }
      else{
	sibling->setColor(true);
	db = parent;
      }
    }
    else if(case2){//CASE 2 (sibling is red)
      //swap parent color (since sibling is red it will always be black
      parent->setColor(true);
      //swap sibling color to black
      sibling->setColor(false);
      //rotate in direction of db node
      if(isLChild){
	rotateLeft(parent, head);
      }
      else{
	rotateRight(parent, head);
      }
    }
    else if(case3){//CASE 3 (sibling is black. Sibling's child closest to db is red and siblings child furthest from db is black
      sibling->setColor(false);
      //set color of sibling's child closest to db to black (change from red) then rotate sibling away from db
      if(isLChild){//if db is LChild//
	sibling->getLChild()->setColor(false);
	rotateRight(sibling, head);
      }
      else{//if db is RChild//
	sibling->getRChild()->setColor(false);
	rotateLeft(sibling, head);
      }
      //always perform case 4 after case 3 (case 4 is therefore built into this function twice)
      ////////////////////////////////////////// JUMP TO CASE 4 ////////////////////////////////////////////////
      //reistablish parent/sibling/isLChild
      parent = db->getParent();
      if(parent->getLChild() == db){
	isLChild = true;
      }
      if(parent->getRChild() == db){
	isLChild = false;
      }
      
      if(isLChild){
	sibling = parent->getRChild();
      }
      else{
	sibling = parent->getLChild();
      }
      //Case 4 (explained below)
      tempColor = parent->isRed();
      parent->setColor(sibling->isRed());
      sibling->setColor(tempColor);
      if(isLChild){//rotate parent towards db
	rotateLeft(parent, head);
	sibling->getRChild()->setColor(false);
      }
      else{
	rotateRight(parent, head);
	sibling->getLChild()->setColor(false);
      }
      db = NULL;
      ///////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else if(case4){//CASE 4 (sibling is black and sibling's child that is furthest from db is red)
      //store color of parent
      tempColor = parent->isRed();
      //set color of parent to color of sibling
      parent->setColor(sibling->isRed());
      //set color of sibling to color that was stored from parent
      sibling->setColor(tempColor);
      //rotate parent towards bd and color sibling's child that was furthest from db to black
      if(isLChild){//rotate parent towards db
	rotateLeft(parent, head);
	sibling->getRChild()->setColor(false);
      }
      else{
	rotateRight(parent, head);
	sibling->getLChild()->setColor(false);
      }
      //set db to null (no more black depth error)
      db = NULL;
      
    }
  }

  //time to delete the leaf node that was originally passed in
  //set parent to the parent of tbd (tbd = to be deleted)
  parent = tbd->getParent();
  //if tbd has a child, put the child's data in tbd and delete the child
  if(tbd->getLChild()){
    tbd->setData(tbd->getLChild()->getData());
    delete tbd->getLChild();
    tbd->setLChild(NULL);
  }
  else if(tbd->getRChild()){
    tbd->setData(tbd->getRChild()->getData());
    delete tbd->getRChild();
    tbd->setRChild(NULL);
  }
  else{//if there is no child of tbd
    //delete tbd, set the parent's pointer to tbd to NULL
    if(parent->getLChild() == tbd){
      delete tbd;
      tbd = NULL;
      parent->setLChild(NULL);
    }
    else{
      delete tbd;
      tbd = NULL;
      parent->setRChild(NULL);
    }
  }
}

void searchTWrapper(tNode* root, int data){//search wrapper (tells the user if the value was found)
  if(search(root, data)){//if returns true
    //tell user the data is in the tree
    cout << data << " is in the tree!" << endl;
  }
  else{//if returns false
    //tell user the data is not in the tree
    cout << data << " is not in the tree!" << endl;
  }
}

bool search(tNode* root, int data){//walks down tree and returns true if value is found, returns false if no matching value is found
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
