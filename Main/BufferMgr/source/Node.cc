// First: Define and implement Node

#include "Node.h"

// Node Constructor
Node :: Node(MyDB_PagePtr page){
    this -> page = page;
    this -> prev = nullptr;
    this -> next = nullptr;
}

// getPage 
// return type: MyDB_PagePtr page
MyDB_PagePtr Node :: getPage(){
    return this -> page;
}

// setPage 
void Node :: setPage(MyDB_PagePtr page){
    this -> page = page;
}

// getPrevPointer
Node *Node :: getPrev(){
    return this -> prev;
}

// setPrevPointer
void Node :: setPrev(Node *prev){
    Node :: prev = prev;
}

// getNextPointer
Node *Node :: getNext(){
    return this -> next;
}

// setNextPointer
void Node :: setNext(Node *next){
    Node :: next = next;
};