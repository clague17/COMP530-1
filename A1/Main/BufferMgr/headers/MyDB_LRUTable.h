//
//
//

#ifndef LRU_TABLE_H
#define LRU_TABLE_H

#include <list>
#include <unordered_map>
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
    
    MyDB_PagePtr checkLRU();
    
    void updateLRU(pageID updateMeID, MyDB_PagePtr updateMePtr);
    
    MyDB_LRUTable();
    
    ~MyDB_LRUTable();
    
private:
    list<id_and_page_pair> _accessHistory;
    unordered_map<pageID, list_it> _lookUpTable;
};



#endif
