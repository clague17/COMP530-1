#ifndef PAGE_C
#define PAGE_C

#include "MyDB_Page.h"
#include <string>

using namespace std;

void MyDB_Page :: markDirty() {
    _dirtyBit = true;
}

void MyDB_Page :: unmarkDirty() {
    _dirtyBit = false;
}

void MyDB_Page :: markHit() {
    _hitBit = true;
}

void MyDB_Page :: unmarkHit() {
    _hitBit = false;
}

void MyDB_Page :: markBuffer() {
    _bufferBit = true;
}

void MyDB_Page :: unmarkBuffer() {
    _bufferBit = false;
}

void MyDB_Page :: markPin() {
    _pinBit = true;
}

void MyDB_Page :: unmarkPin() {
    _pinBit = false;
}

bool MyDB_Page :: isDirty() {
    return _dirtyBit;
}

bool MyDB_Page :: isBuffered() {
    return _bufferBit;
}

bool MyDB_Page :: isPinned() {
    return _pinBit;
}

string MyDB_Page :: getPageID() {
    return _pageID;
}

int MyDB_Page :: getPageFrameIndex() {
    return _indexofPageFrame;
}

void MyDB_Page :: incRefCounter() {
    _refCounter++;
}

void MyDB_Page :: decRefCounter() {
    if (_refCounter > 0) {
        _refCounter--;
    }
}

void MyDB_Page :: buffer() {
    // Code
}

void MyDB_Page :: writeBack() {
    // Code
}

MyDB_Page :: MyDB_Page(MyDB_BufferManagerPtr bufferManager, pair<MyDB_TablePtr, int> const addressinStorage)
{
    _dirtyBit = false;
    _hitBit = false;
}

MyDB_Page :: ~MyDB_Page () {
    
}
#endif
