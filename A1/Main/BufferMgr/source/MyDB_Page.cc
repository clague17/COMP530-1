#ifndef PAGE_C
#define PAGE_C

#include "MyDB_Page.h"
#include <string>

using namespace std;

void MyDB_Page :: markDirty() {
  _dirty = true;
}

void MyDB_Page :: unmarkDirty() {
  _dirty = false;
}

void MyDB_Page :: markHit() {
  _hitByte = true;
}

void MyDB_Page :: unmarkHit() {
  _hitByte = false;
}

void MyDB_Page :: markBuffer() {
    _bufferBit = true;
}

void MyDB_Page :: unmarkBuffer() {
    _bufferBit = false;
}

void MyDB_Page :: markPin() {
    _PinBit = true;
}

void MyDB_Page :: unmarkPin() {
    _PinBit = false;
}

bool MyDB_Page :: isDirty() {
    return _dirty;
}

bool MyDB_Page :: isBuffered() {
    return _bufferBit;
}

bool MyDB_Page :: isPinned() {
    return _PinBit;
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

void buffer() {
    // Code
}

void writeBack() {
    // Code
}

MyDB_Page :: MyDB_Page () {
  _dirty = false;
  _hitByte = false;
}

MyDB_Page :: ~MyDB_Page () {

}
#endif
