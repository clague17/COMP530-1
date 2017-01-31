
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include <iostream>
#include "MyDB_BufferManager.h"
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr whichTable, long i) {
    //get the pair of the key if it exists
    string pageID = whichTable -> getName() + whichTable-> getStorageLoc() + to_string(i);
    id_to_PagePtr_map :: iterator it = _pageTable.find(pageID);
    //key exists, create a new handle of the page object and return it
    if (it != _pageTable.end()) {
        cout << "found Page "
        << whichTable->getName() << " "
        << i
        << " in the page table."
        << endl;
        cout << "Create a handle and returned."
        << endl;
        
        cout<<"[MyDB_BufferManager :: getPage] "<<"the page pointer is";
        cout<< it->second <<endl;
        MyDB_PagePtr pagePtr = it->second;
        
        cout<<"[MyDB_BufferManager :: getPage] "<<"get page pointer"<<endl;
        
        return make_shared<MyDB_PageHandleBase>(pagePtr);
    }
    //key doesn't exists, create a new handle of the page object and return it
    else {
        cout << "Page "
        << whichTable->getName() << " "
        << i
        << " is not in the page table." << endl;
        cout << "Made a new page Object returned a handle to it."
        << endl;
        MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(whichTable->getStorageLoc(), i), pageID, false);
        _pageTable[pageID] = pagePtr;
        return make_shared<MyDB_PageHandleBase>(pagePtr);
    }
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
    string pageID = _tempFile + to_string(tempPageIndex);
    //Create a page Pointer
    MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(_tempFile, tempPageIndex),pageID, true);
    //Increate index of page in temp file
    tempPageIndex++;
    //return a page handle
    return make_shared<MyDB_PageHandleBase>(pagePtr);
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr whichTable, long i) {
    //get the pair of the key if it exists
    string pageID = whichTable -> getName() + whichTable-> getStorageLoc() + to_string(i);
    id_to_PagePtr_map :: iterator it = _pageTable.find(pageID);
    //key exists, create a new handle of the page object and return it
    if (it != _pageTable.end()) {
        cout << "found Page "
        << whichTable->getName() << " "
        << i
        << " in the page table."
        << endl;
        cout << "Create a handle and returned."
        << endl;
        
        MyDB_PagePtr pagePtr = it->second;
        cout<<"[MyDB_BufferManager :: getPinnedPage] "<<"the page pointer is " << it->second <<endl;
        cout<<"[MyDB_BufferManager :: getPinnedPage] "<<"the page pointer is " << pagePtr <<endl;
       
        pagePtr -> markPin();
        
        cout<<"[MyDB_BufferManager :: getPinnedPage] "<<"mark Pin" <<endl;
        return make_shared<MyDB_PageHandleBase>(pagePtr);
    }
    //key doesn't exists, create a new handle of the page object and return it
    else {
        cout<< "MyDB_BufferManager :: getPinnedPage : " <<  "Page "
        << whichTable->getName() << " "
        << i
        << " is not in the page table." << endl;
        cout << "Made a new page Object returned a handle to it."
        << endl;
        
        cout<< "[MyDB_BufferManager :: getPinnedPage] " << "Create a page object"<<endl;
        MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(whichTable->getStorageLoc(), i), pageID, false);
        
        cout<<"[MyDB_BufferManager :: getPinnedPage] "<<"the page pointer is " << pagePtr <<endl;

        
        cout<< "[MyDB_BufferManager :: getPinnedPage] " << "markPin" <<endl;
        pagePtr->markPin();
        
        cout<< "[MyDB_BufferManager :: getPinnedPage] " << "insert into lookup table" <<endl;
        _pageTable[pageID] = pagePtr;
        
        cout<< "[MyDB_BufferManager :: getPinnedPage] " << "return a page handle"<<endl;
        return make_shared<MyDB_PageHandleBase>(pagePtr);
    }
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
    string pageID = _tempFile + to_string(tempPageIndex);
    MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(_tempFile, tempPageIndex),pageID, true);
    tempPageIndex++;
    pagePtr -> markPin();
    return make_shared<MyDB_PageHandleBase>(pagePtr);
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
    unpinMe -> unpinPage();
}

char* MyDB_BufferManager :: allocBuffer (MyDB_PagePtr pagePtr) {
    char* pageFrame;
    // If there is no free page frames
    if (availablePageFrames.empty()) {
        cout<<"[MyDB_BufferManager :: allocBuffer] " << "There is no free page frame"<<endl;
        MyDB_PagePtr evictedPage = _lruTable -> checkLRU();
        evictedPage -> evictMyself();
        pageFrame = availablePageFrames.back();
        cout<<"[MyDB_BufferManager :: allocBuffer] " << " buffer Address is " << static_cast<void *>(&pageFrame[0]) << endl;
        availablePageFrames.pop_back();
    }
    // If there is free page frames
    else {
        cout<<"[MyDB_BufferManager :: allocBuffer] " << "There is free page frame"<<endl;
        pageFrame = availablePageFrames.back();
        cout<<"[MyDB_BufferManager :: allocBuffer] " << " buffer Address is " << static_cast<void *>(&pageFrame[0]) << endl;

        availablePageFrames.pop_back();
    }
   
    pair<fileLoc, int> address = pagePtr -> getAddress();
    int fd = open(address.first.c_str(), O_CREAT | O_RDWR | O_FSYNC, 0666);
    lseek(fd, address.second * _pageSize, SEEK_SET);
    read(fd, pageFrame, _pageSize);
    return pageFrame;
}

void MyDB_BufferManager:: recyclBuffer(MyDB_PagePtr pagePtr) {
    pageID id = pagePtr -> getPageID();
    char* recyPageFrame = _lruTable -> evictItem(id);
    availablePageFrames.push_back(recyPageFrame);
}

void MyDB_BufferManager:: writeBack(MyDB_PagePtr pagePtr) {
    pair<fileLoc, int> address = pagePtr -> getAddress();
    int fd = open(address.first.c_str(), O_CREAT | O_RDWR | O_FSYNC, 0666);
    lseek(fd, address.second * _pageSize, SEEK_SET);
    write(fd, pagePtr -> getPageFrame(), _pageSize);
}

void MyDB_BufferManager:: updateLRUTable(MyDB_PagePtr pagePtr) {
    _lruTable -> updateLRU(pagePtr -> getPageID(), pagePtr);
}

void MyDB_BufferManager:: clearBuffer() {
    _lruTable -> clearLRU();
    for (int i = int(_numPages - 1); i >= 0; i--) {
        delete[] allPageFrames[i];
    }
}
MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
    
    _pageSize = pageSize;
    _numPages = numPages;
    _tempFile = tempFile;
    tempPageIndex = 0;
    
    for (int i = int(_numPages - 1); i >= 0; i--) {
        allPageFrames.push_back(new char[_pageSize]);
    }
    
    availablePageFrames = allPageFrames;

    _lruTable = make_shared<MyDB_LRUTable>();
    
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
    
    clearBuffer();
    
}

#endif
