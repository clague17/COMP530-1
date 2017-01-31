#ifndef PAGE_C
#define PAGE_C

#include <iostream>
#include "MyDB_Page.h"
#include "MyDB_BufferManager.h"
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
    cout<<"[MyDB_Page :: markPin()] "<< "markPin"<<endl;
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

bool MyDB_Page :: isAnonymous() {
    return _anonBit;
}

bool MyDB_Page :: hasNoCounter() {
    return _refCounter == 0;
}

string MyDB_Page :: getPageID() {
    return _pageID;
}

char* MyDB_Page :: getPageFrame() {
    return  _pageFrame;
}

void MyDB_Page :: incRefCounter() {
    _refCounter++;
}

void MyDB_Page :: decRefCounter() {
    if (_refCounter > 0) {
        _refCounter--;
    }
}

void MyDB_Page :: bufferMyself() {
    _pageFrame = _bufferManager -> allocBuffer(shared_from_this());
    _bufferBit = true;
    _dirtyBit = false;
}

void MyDB_Page :: evictMyself() {
    if (isDirty()) {
        _bufferManager -> writeBack(shared_from_this());
    }
    _bufferManager -> recyclBuffer(shared_from_this());
    _pageFrame = nullptr;
    unmarkBuffer();
}

void MyDB_Page:: updateMyselfinLRU() {
    _bufferManager -> updateLRUTable(shared_from_this());
}

pair<fileLoc, int> MyDB_Page::getAddress(){
    return _addressinStorage;
}

void MyDB_Page:: writeBack() {
    _bufferManager -> writeBack(shared_from_this());
}

MyDB_Page :: MyDB_Page(MyDB_BufferManager* const& bufferManager, pair<fileLoc, int> const& addressinStorage, string const& pageID, bool isAnonymous){
    cout<<"[MyDB_Page :: MyDB_Page] "<< "Calling constructor."<<endl;
    _bufferManager = bufferManager;
    _addressinStorage = addressinStorage;
    _pageID = pageID;
    _dirtyBit = false;
    _hitBit = false;
    _bufferBit = false;
    _anonBit = isAnonymous;
    _refCounter = 0;
}

MyDB_Page :: ~MyDB_Page () {
    cout<<"[MyDB_Page :: ~MyDB_Page] "<< "Calling destructor."<<endl;

}
#endif
