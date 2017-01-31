//
//
//

#ifndef LRU_TABLE_H
#define LRU_TABLE_H

#include <list>
#include <unordered_map>
#include <memory>
#include "MyDB_Page.h"

using namespace std;

class MyDB_LRUTable;
typedef shared_ptr<MyDB_LRUTable> MyDB_LRUTablePtr;
typedef string pageID;
typedef pair<pageID, MyDB_PagePtr> id_and_page_pair;
typedef list<id_and_page_pair> :: iterator list_it;

using namespace std;

class MyDB_LRUTable {

public:

    // get the evicted candidate, return a smart pointer to a page that is going to be evicted.
    // Called by buffer manager when there is no free space for pages
    MyDB_PagePtr checkLRU();

    // update LRU table
    // if the id is in the table, shift it to the last position of access history
    // if the id is not in the table, append it to the last position of access history and lookup table
    void updateLRU(pageID updateMeID, MyDB_PagePtr updateMePtr);

    // evict a specified item
    // return the address of page frame
    // Called by buffer manager to evict a anonymous page
    char* evictItem(pageID evictMeID);

    void clearLRU();

    MyDB_LRUTable();

    ~MyDB_LRUTable();

private:

    // A list of pairs of id and page pointer ordered by accessing time
    list<id_and_page_pair> _accessHistory;

    // A look up table to find out a iterator in the access history list
    // key: pageID, value: iterator
    unordered_map<pageID, list_it> _lookUpTable;
};



#endif
