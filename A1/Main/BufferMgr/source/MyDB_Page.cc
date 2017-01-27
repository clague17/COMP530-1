#ifndef PAGE_OBJECT_C
#define PAGE_OBJECT_C

#include "MyDB_Page.h"
#include <string>

using namespace std;

MyDB_Page :: markDirty() {
  _dirty = true;
}

MyDB_Page :: unmarkDirty(){
  _dirty = false;
}

MyDB_Page :: markHit(){
  _hitByte = true;
}

MyDB_Page :: unmarkHit(){
  _hitByte = false;
}

MyDB_Page :: MyDB_Page () {
  _dirty = false;
  _hitByte = false;
}

MyDB_Page :: ~MyDB_Page () {

}
#endif
