
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include <string>
#include <vector>

using namespace std;


MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr whichTable, long i) {
	//get the pair of the key if it exists
	id_to_PagePtr_map :: iterator it = _pagetable.find(to_string(i) + whichTable.getName());
	//key exists, create a new handle of the page object and return it
	if (it != _pagetable.end()) {
		cout << "found Page "
             << whichTable.getName << " "
             << i
             << " in the page table."
             << endl;
		cout << "Create a handle and returned."
             << endl;
		return make_shared<MyDB_PageHandleBase>(it->second);
	}
	//key doesn't exists, create a new handle of the page object and return it
	else {
		cout << "Page"
             << whichTable.getName << " "
             << i
             << "is not in the page table."
             << endl;
		cout << "Made a new page Object returned a handle to it."
             << endl;
        MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(whichTable, i));
		return make_shared<MyDB_PageHandleBase>(pagePtr);
	}
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	return nullptr;
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr whichTable, long i) {
    //get the pair of the key if it exists
    id_to_PagePtr_map :: iterator it = _pagetable.find(to_string(i) + whichTable.getName());
    //key exists, create a new handle of the page object and return it
    if (it != _pagetable.end()) {
        cout << "found Page "
        << whichTable.getName << " "
        << i
        << " in the page table."
        << endl;
        cout << "Create a handle and returned."
        << endl;
        it -> second -> markPin();
        return make_shared<MyDB_PageHandleBase>(it->second);
    }
    //key doesn't exists, create a new handle of the page object and return it
    else {
        cout << "Page"
        << whichTable.getName << " "
        << i
        << "is not in the page table."
        << endl;
        cout << "Made a new page Object returned a handle to it."
        << endl;
        MyDB_PagePtr pagePtr = make_shared<MyDB_Page>(this, make_pair(whichTable, i));
        pagePtr.markPin();
        return make_shared<MyDB_PageHandleBase>(pagePtr);
    }
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	return nullptr;
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
    
}

char* MyDB_BufferManager :: allocBuffer (MyDB_PagePtr pagePtr) {
    int index;
    if (availableSlots.empty()) {
        MyDB_PagePtr evictedPage = _lruTable -> checkLRU();
        evictedPage -> unmarkBuffer();
        index = evictedPage -> getPageFrameIndex();
        if (evictedPage -> isDirty()) {
            evictedPage -> writeBack();
        }
    } else {
        index = availableSlots.pop_back();
        
    }
    pageFrame[index] = new char[_pageSize];
    _lruTable -> updateLRU(pagePtr -> getPageID(), pagePtr);
    // Cache!
    return pageFrame[index];
                               
}


MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
    
	_pageSize = pageSize;
	_numPages = numPages;
	_tempFile = tempFile;
    
    
	//Initialize a spot for the pages' data
    for (int i = _numPages - 1; i >= 0; i--) {
        availableSlots.push_back(i);
    }
    
    isFull = false;
    _lruTable = make_shared<MyDB_LRUTable>();
    
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
}

#endif
