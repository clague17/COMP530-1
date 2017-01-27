
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <memory>
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
	return nullptr;
}

void MyDB_PageHandleBase :: wroteBytes () {
}

MyDB_PagePtr MyDB_PageHandleBase :: getPagePointer() {
}

MyDB_PageHandleBase :: MyDB_PageHandleBase (MyDB_PagePtr pagePointer) {
}

MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
}

#endif
