#ifndef PAGE_H
#define PAGE_H
#include <string>
#include <memory>
//#include "MyDB_BufferManager.h"

using namespace std;

class MyDB_BufferManager;
class MyDB_Table;
class MyDB_Page;
typedef shared_ptr <MyDB_Page> MyDB_PagePtr;
typedef shared_ptr<MyDB_BufferManager> MyDB_BufferManagerPtr;
typedef shared_ptr<MyDB_Table> MyDB_TablePtr;
typedef string fileLoc;

class MyDB_Page : public enable_shared_from_this<MyDB_Page>  {

public:
    // Mark the dirty bit
    void markDirty();

    // Unmark the dirty bit
    void unmarkDirty();

    // Mark the hit bit
    void markHit();

    // Unmark the hit bit
    void unmarkHit();

    // Mark the buffer bit
    void markBuffer();

    // Unmark the buffer bit
    void unmarkBuffer();

    // Mark the pin bit
    void markPin();

    // Unmark the pin bit
    void unmarkPin();

    // Return true if the page is dirty, otherwise return false
    bool isDirty();

    // Return true if the page is buffered in RAM, otherwise return false
    bool isBuffered();

    // Return true if the page is pinned, otherwise return false
    bool isPinned();

    bool isAnonymous();

    // Increase the reference counter by one
    void incRefCounter();

    // Decrease the reference counter by one
    void decRefCounter();

    bool hasNoCounter();

    // return PageID
    string getPageID();

    // return the page frame
    char* getPageFrame();

    // return the address of the actual data
    pair<fileLoc, int> getAddress();

    // Buffer the data from file to RAM
    void bufferMyself();

    // Evict the page
    void evictMyself();

    void updateMyselfinLRU();

    void writeBack();

    MyDB_Page(MyDB_BufferManager* const& bufferManager, pair<fileLoc, int> const& addressinStorage, string const& pageID, bool isAnonymous);

    ~MyDB_Page();

private:
    // the size of page
    size_t _pageSize;

    // the counter of handles to the page object
    int _refCounter;

    // a bit to indicate whether a page is dirty
    bool _dirtyBit;

    // a bit to indicate whether a page is hit
    bool _hitBit;

    // a bit to indicate whether a page is buffered in RAM
    bool _bufferBit;

    // a bit to indicate whether a page is pinned
    bool _pinBit;

    // a bit to indicate whether a page is anonymous
    bool _anonBit;

    // a unique page ID
    string _pageID;

    // the address in storage
    pair<fileLoc, int> _addressinStorage;

    // the address of the page frame where the page is buffered in RAM
     char* _pageFrame;

    // the buffer manager
    MyDB_BufferManager* _bufferManager;
};

#endif
