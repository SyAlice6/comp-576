
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"
#include "LRU.h"
#include <string>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr tablePointer, long offset) {
	// define the key of the look up table
	pair<MyDB_TablePtr, long> pageIndex = make_pair(tablePointer, offset);
	// using an iterator to search for the specific page in the loop up table
	map<pair<MyDB_TablePtr, long>, MyDB_PagePtr>::iterator it;
	it = this -> lookUpTable.find(pageIndex);
	// iterator not found
	if (it == lookUpTable.end()) {
		// create page, add page into lookupTable
		// pointer to the page stored in the lookup table
		MyDB_PagePtr newPage = make_shared<MyDB_Page> (*this, tablePointer, offset);
		this->lookUpTable[pageIndex] = newPage;
		return make_shared <MyDB_PageHandleBase> (newPage);
	} else {
		return make_shared <MyDB_PageHandleBase> (this->lookUpTable[pageIndex]);
	}		
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	pair<MyDB_TablePtr, long> pageIndex = make_pair(nullptr, this->anonymousPageCounter);
	MyDB_PagePtr newPage = make_shared<MyDB_Page> (*this, nullptr, this->anonymousPageCounter);
	this->lookUpTable[pageIndex] = newPage;
	this->anonymousPageCounter += 1;
	return make_shared <MyDB_PageHandleBase> (newPage);		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr tablePointer, long offset) {
	// define the key of the look up table
	pair<MyDB_TablePtr, long> pageIndex = make_pair(tablePointer, offset);	
	MyDB_PagePtr ans_page;

	// using an iterator to search for the specific page in the loop up table
	map<pair<MyDB_TablePtr, long>, MyDB_PagePtr>::iterator it;
	it = this -> lookUpTable.find(pageIndex);

	if (it == lookUpTable.end()) {// iterator not found
		// create page, add page into lookupTable
		// pointer to the page stored in the lookup table
		ans_page = make_shared<MyDB_Page> (*this, tablePointer, offset);
		this->lookUpTable[pageIndex] = ans_page;
	} else { // iterator found
		ans_page = this -> lookUpTable[pageIndex];
		// if the page is in the LRU list, set the pinned to be true --- ?
		if(this -> LRU_cache -> findNode(pageIndex) != nullptr){
			ans_page -> setPin(true);
		}
	}

	// put the page in the LRU cache if there are still available ram
	if(ans_page -> getBytes() == nullptr){
		if(this -> availableRam.size() == 0){ // LRU full of pinend page
			this -> LRU_cache->popTail();
		}

		if(this -> availableRam.size() == 0){
			return nullptr; // only try pop out the LRU for once?
		}

		// allocate the availble ram to the ans_page
		this->LRU_cache->addToList(pageIndex, ans_page);
	}		

	return make_shared <MyDB_PageHandleBase> (ans_page);
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	return nullptr;		
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
	unpinMe -> getPage() -> setPin(false);
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
	this -> pageSize = pageSize;
	this -> numPages = numPages;
	this -> tempFile = tempFile;
	this -> anonymousPageCounter = 0;

	for (size_t i = 0; i < numPages; i++) {
		this->availableRam.push_back((void *) malloc (pageSize));
	}	
	this->LRU_cache = new LRUCache(numPages);
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
}
	
#endif


