
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <iostream>
#include <memory>
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
    // If the page is not buffered, ask the buffer manager to assign a page frame
    if (!_pagePointer -> isBuffered()) {
        _pagePointer -> bufferMyself();
    }
    // Update the page in the LRU table
    _pagePointer -> updateMyselfinLRU();
    char* address = _pagePointer -> getPageFrame();
    cout<< "[MyDB_PageHandleBase :: getBytes] " << " buffer Address is " << static_cast<void *>(&address[0]) << endl;
    return _pagePointer -> getPageFrame();
}

void MyDB_PageHandleBase :: wroteBytes () {
    // Set the dirty bit to true
    _pagePointer -> markDirty();
}

void MyDB_PageHandleBase :: unpinPage() {
    _pagePointer -> unmarkPin();
}

MyDB_PageHandleBase :: MyDB_PageHandleBase (MyDB_PagePtr pagePointer) {
    _pagePointer = pagePointer;
    _pagePointer -> incRefCounter();
}

MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
    _pagePointer -> decRefCounter();
    // If the page has no reference to it and it's a anonymous page, evict it
    if (_pagePointer -> hasNoCounter() && _pagePointer -> isAnonymous() && _pagePointer -> isBuffered()) {
        _pagePointer -> evictMyself();
    }
    // If a pinned non-anonymous page has not reference to it, unpin it
    if (_pagePointer -> hasNoCounter() && _pagePointer -> isPinned()) {
        _pagePointer -> unmarkPin();
    }
}

#endif
