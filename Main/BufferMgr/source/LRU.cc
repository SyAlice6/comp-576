#ifndef LRU_C
#define LRU_C

#include "Node.h"
#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"

#include <map>

using namespace std;

// Define and implement LRU Cache
// Notice: Head is just a pointer, head -> next is the first node in the DLL

// Constructor
LRUCache :: LRUCache(int cacheSize){
    this -> cacheSize = cacheSize; // size of the LRU Cache
    this -> currSize = 0; // current total nodes in the LRU Cache

    this -> head = new Node(nullptr);
    this -> tail = new Node(nullptr);

    head -> prev = nullptr;
    head -> next = tail;

    tail -> prev = head;
    tail -> next = nullptr;
}


// Destructor
LRUCache :: ~LRUCache(){ // clean up the LRUCache
    while(head != nullptr){
        Node *nextNode = head -> next;
        delete head;
        head = nextNode;
    }

    delete tail;
    tail = nullptr
}

// Methods:

// return the Head node
Node* LRUCache :: getHead(){
    return head -> next;
}

// return the Tail node
Node* LRUCache :: getTail(){
    return tail -> prev;
}

// return the current total nodes in the LRU Cache
int LRUCache :: getCacheSize(){
    return this -> cacheSize;
}

// return if the LRU Cache is full
bool LRUCache :: isFull(){
    if(this -> currSize == this -> cacheSize){
        return true;
    }else{
        return false;
    }
}

// Add the new node right after the Head Node
void LRUCache :: addNewNode(Node *node){
    node -> prev = head;
    node -> next = head -> next;

    head -> next -> prev = node;
    head -> next = node;
}


// Remove an existing node from the linked list
void LRUCache :: removeNode(Node *node){
    Node *prevNode = node -> prev;
    Node *nextNode = node -> next;

    prevNode -> next = nextNode;
    nextNode -> prev = prevNode;
}


// Move certain node in between to the head
void LRUCache :: moveToHead(Node *node){
    this -> removeNode(node);
    this -> addNewNode(node);
}

// pop the Tail node 
Node* LRUCache :: popTail(){
    Node *lastNode = tail -> prev;
    // pop the last node that isn't a pinned node
    // so here, check if the node is pinned node
    while(lastNode != head && lastNode -> getPage() -> isPinned()){
        lastNode = lastNode -> prev;
    }

    if(lastNode == head) return nullptr;

    // write the bytes back to disk if the byte is dirty
    // add something here, isDirty()

    MyDB_PagePtr page = lastNode->getPage();
    this->deleteNode(lastNode);

    if(page -> getReferenceCounter() == 0){ // refCount = 0, kill the page
        this->parentManager.killPage(page->getParentTable(), page->getOffset());
    }

    return lastNode;
}

// Find the target node  
Node* LRUCache :: findNode(pair<MyDB_TablePtr, size_t> identifier){
    if(map.find(identifier) != map.end()){ // find the key in the map
        // find the node, move to head, then return it
        Node *target = map.find(identifier) -> second;
        this -> moveToHead(target);
        return target;
    }else{ // didn't find the key in the map
        return nullptr;
    }
}

// Add a newNode to the LRU linkedlist and Ram
Node* LRUCache :: addToList(pair<MyDB_TablePtr, size_t> identifier, MyDB_PagePtr page){
    // give the page's byte an address
    page->setBytes(this -> parentManager.availableRam[this->parentManager.availableRam.size () - 1]);
    // remove one availableRam since we just assign one above
    this->parentManager.availableRam.pop_back();

    // create a new Node
    Node *newNode = new Node(page);
    // push the node to the LRU Hashmap
    map[make_pair(identifier.first, identifier.second)] = newNode;
    // Add this node to the head of the list
    addNewNode(newNode);
    // increment current size
    currSize += 1;
    return newNode;
}

// Delete a certain node from the linked list and RAM
void LRUCache :: deleteNode(Node *node){
    // Remove node from list
    removeNode(node);

    // find the page object the node refer to
    MyDB_PagePtr page = node -> getPage();
    // delete this page object from the RAM, add this space back to availableRam
    this->parentManager.availableRam.push_back (page->bytes);
    
    // delete the page from the hashmap
    map.erase(page -> getPageIndex());
    // set the page's byte to be null
    page -> bytes = nullptr;
    currSize -= 1;
}

#endif











