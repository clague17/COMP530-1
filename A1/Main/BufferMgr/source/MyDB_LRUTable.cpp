//
//  MyDB_LRUTable.cpp
//

#ifndef LRU_TABLE_C
#define LRU_TABLE_C

#include "MyDB_LRUTable.h"


typedef unordered_map<pageID, list_it> :: iterator map_it;

using namespace std;

MyDB_PagePtr MyDB_LRUTable :: checkLRU() {
    list_it evicted = _accessHistory.begin();
    while ((*evicted).second -> isPinned()) {
        evicted = next(evicted,2);
    }
    if (evicted != _accessHistory.end()) {
        MyDB_PagePtr pagePtr = (*evicted).second;
        _lookUpTable.erase((*evicted).first);
        _accessHistory.erase(evicted);
        return pagePtr;
    }
    return NULL;
}

void MyDB_LRUTable :: updateLRU(pageID updateMeID, MyDB_PagePtr updateMePtr) {
    map_it it = _lookUpTable.find(updateMeID);
    if (it != _lookUpTable.end()) {
        _accessHistory.erase(it->second);
    }
    _accessHistory.push_back(make_pair(updateMeID, updateMePtr));
    _lookUpTable[updateMeID] = _accessHistory.end();
}

MyDB_LRUTable :: MyDB_LRUTable() {
    
}

MyDB_LRUTable :: ~MyDB_LRUTable() {
    
}

#endif
