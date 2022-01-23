// First: define Node

#include "MyDB_Page.h"

class Page;

class Node{
    private:
        // Variables: a pointer to the page, prev pointer, next pointer(in linked list)
        MyDB_PagePtr page; 
        Node *prev; 
        Node *next; 

    public:
        // Constructor
        Node(MyDB_PagePtr page); 

        // getPage 
        MyDB_PagePtr getPage();

        // setPage 
        void setPage(MyDB_PagePtr page);

        // getPrevPointer
        Node *getPrev();

        // setPrevPointer
        void setPrev(Node *prev);

        // getNextPointer
        Node *getNext();

        // setNextPointer
        void setNext(Node *next);
};

#endif