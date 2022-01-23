
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <memory>
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
	return this->page->getBytes();
}

void MyDB_PageHandleBase :: wroteBytes () {
	this->page->wroteBytes();
}

MyDB_PageHandleBase :: MyDB_PageHandleBase (MyDB_PagePtr page) {
	this->page = page;
	// this->page->setReference(1);
}

MyDB_PagePtr MyDB_PageHandleBase :: getPage() {
	return this->page;
}


MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
}

#endif

