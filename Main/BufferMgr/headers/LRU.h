#include "Node.h"
#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"

class Node;

class LRUCache{

    private:
        int cacheSize; // size of the LRU Cache
        int currSize; // current total nodes in the LRU Cache
        Node *head; // head Node 
        Node *tail; // tail Node

        MyDB_BufferManager &parentManager;   // ?

    public:
        // variable HashMap: pageIdentifier -> Page Node
        map<pair<MyDB_TablePtr, size_t>, Node*> map;

        // Constructor
        LRUCache();

        // Destructor
        ~LRUCache();

        // Methods:

        // return the Head node
        Node* getHead();

        // return the Tail node
        Node* getTail();

        // return the current total nodes in the LRU Cache
        int getCacheSize();

        // return if the LRU Cache is full
        bool isFull();

        // Add the new node right after the Head Node
        void addNewNode(Node *node);

        // Remove an existing node from the linked list
        void removeNode(Node *node);

        // Move certain node in between to the head
        void moveToHead(Node *node);

        // Delete a certain node from the linked list
        void deleteNode(Node *node); 


        // pop the Tail node    ?
        Node* popTail();

        // Find the target node   ?
        Node* findNode(pair<MyDB_TablePtr, size_t> identifier);

        // Add a newNode to the LRU linkedlist     ?
        Node* addToList(pair<MyDB_TablePtr, size_t> identifier, MyDB_PagePtr page);

};

#endif
