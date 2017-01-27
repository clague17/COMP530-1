#ifndef PAGE_OBJECT_H
#define PAGE_OBJECT_H

#include <string>
using namespace std;
class MyDB_Page;
typedef shared_ptr <MyDB_Page> MyDB_PagePtr;

class MyDB_Page {

public:
  markDirty();

  unmarkDirty();

  markHit();

  unmarkHit();

  MyDB_Page ();

  ~MyDB_Page ();

private:
  size_t _pageSize;
  size_t _refCounter; //for handle
  bool _dirtyBit;
  bool _hitBit;
  //LRU POS
  //data loc
    //balab
}

#endif
