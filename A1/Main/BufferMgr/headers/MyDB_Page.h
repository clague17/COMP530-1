#ifndef PAGE_H
#define PAGE_H
#include <string>
#include <MyDB_BufferManager.h>

using namespace std;
class MyDB_Page;
typedef shared_ptr <MyDB_Page> MyDB_PagePtr;

class MyDB_Page {

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
    
    // Increase the reference counter by one
    void incRefCounter();
    
    // Decrease the reference counter by one
    void decRefCounter();
    
    // return PageID
    string getPageID();
    
    // return index of page frame
    int getPageFrameIndex();
    
    // Buffer the data from file to RAM
    void buffer();

    // write the data back to file
    void writeBack();
    
    MyDB_Page(MyDB_BufferManagerPtr bufferManager, pair<MyDB_TablePtr, int> addressinStorage);

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
    
    // page ID : used for look-up table for buffer manager and look-up table for LRU
    string _pageID;
    
    // the address in storage
    pair<MyDB_TablePtr, int> _addressinStorage;
    
    // the address of the page frame where the page is buffered in RAM
    char* _pageFrame;
    
    // the index of page frame where this page is buffered in RAM
    int _indexofPageFrame;
    
    // the buffer manager
    MyDB_BufferManagerPtr _bufferManager;
}

#endif
