#ifndef PAGE_H
#define PAGE_H

#include <memory>

// page handles are basically smart pointers
using namespace std;

class MyDB_PageBase;
typedef shared_ptr <MyDB_PageBase> MyDB_PagePtr;

class MyDB_PageBase {

public:

	MyDB_Page();

	void getReference();

	void setReference();

	void *getBytes();

	void setBytes(void *ram);

	void wroteBytes();

	void setPin(bool condition);

	bool isPinned();

	~MyDB_PageBase ();

private:
	void *bytes;
	bool pinned;
	long referenceCounter;
};

#endif

