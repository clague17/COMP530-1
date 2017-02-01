//
//  MyDB_LRUTable.cpp
//

#ifndef LRU_TABLE_C
#define LRU_TABLE_C

#include <iostream>
#include "MyDB_LRUTable.h"


typedef unordered_map<pageID, list_it> :: iterator map_it;

using namespace std;

MyDB_PagePtr MyDB_LRUTable :: checkLRU() {
    // Get the oldest page
    list_it evicted = _accessHistory.begin();
    
    // Iterate until a page is not pinned
    while (evicted -> second -> isPinned()) {
        evicted = next(evicted,1);
    }
    return evicted -> second;
}

void MyDB_LRUTable :: updateLRU(pageID updateMeID, MyDB_PagePtr updateMePtr) {
    map_it it = _lookUpTable.find(updateMeID);
    
    // Get the list iterator for page in lookup table
    // If it's found, erase it from list
    if (it != _lookUpTable.end()) {
        
        _accessHistory.erase(it->second);
        
    }
    
    // Append a new pair to the end of the list
    _accessHistory.push_back(make_pair(updateMeID, updateMePtr));
    
    // Update the value in the lookup table (if not exists, create a new pair of key and value)
    _lookUpTable[updateMeID] = --_accessHistory.end();
}

char* MyDB_LRUTable :: evictItem(pageID evictMeID){
    
    // Find the list iterator for the page in lookup table
    map_it it_map = _lookUpTable.find(evictMeID);
    
    if (it_map != _lookUpTable.end()) {
        
        //Get the page frame where the page is buffered
        list_it it_list = it_map -> second;
        char* pageFrame = it_list -> second -> getPageFrame();
        
        //Erase the page from the list and the map
        _accessHistory.erase(it_list);
        _lookUpTable.erase(it_map);
        
        // return page frame
        return pageFrame;
    }
    cout<< "No such a record in LRU. "<< endl;
    return NULL;
}

void MyDB_LRUTable:: clearLRU() {
    list_it it = _accessHistory.begin();
    while (it != _accessHistory.end()) {
        if (it -> second -> isDirty()) {
            it -> second -> writeBack();
        }
        it = next(it, 1);
    }
}

MyDB_LRUTable :: MyDB_LRUTable() {
    
}

MyDB_LRUTable :: ~MyDB_LRUTable() {
    
}


#endif
