
#ifndef PAGE_C
#define PAGE_C

#include <memory>
#include "MyDB_Page.h"

MyDB_Page :: MyDB_Page() {
    this->bytes = nullptr;
    this->reference_counter = 0;
    this->pinned = false;
}

void *MyDB_Page :: getBytes() {
    // this->parentManager.managePage(this->parentTable, this->offset);
    return this->bytes;
}

/* let the page know we have written to the bytes */
void MyDB_Page :: wroteBytes() {
    // this->dirty = true;
}

void MyDB_Page :: setReferenceCounter(int count) {
    this->reference_counter = count;
}

int MyDB_Page :: getReferenceCounter() {
    return this->reference_counter;
}

bool MyDB_Page :: isPinned() {
    return this->pinned;
}

void MyDB_Page :: setPin(bool pinned) {
    this->pinned = pinned;
}

void MyDB_Page :: setBytes(void *ram) {
    this->bytes = ram;
}

MyDB_Page :: ~MyDB_Page () {

}

#endif