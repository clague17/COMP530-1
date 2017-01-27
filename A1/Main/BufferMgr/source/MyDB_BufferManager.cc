
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include <string>
#include <vector>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr whichTable, long i) {
	//get the pair of the key if it exists
	unordered_map<long, MyDB_PagePtr> :: iterator it = _pagetable.find(to_string(i) + whichTable.getName());
	//key exists, copy a new handle of the page object and return it
	if (it != _pagetable.end()) {
		cout << to_string(i) + "th Page is already in the buffer." << endl;
		//get the value of the pair
		it->second;
		cout << "Copy the handle and returned." << endl;
		return nullptr;
	}
	//key doesn't exists, create a new handle of the page object and return it
	else {
		cout << to_string(i) + "th Page is not in the buffer." << endl;

		count << "Made a new handle and returned." << endl;
		return nullptr;
	}
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	return nullptr;
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr whichTable, long i) {
	return nullptr;
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	return nullptr;
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
	_pageSize = pageSize;
	_numPages = numPages;
	_tempFile = tempFile;
	//Initialize a spot for the pages' data
	char** pagesContent = new char*[numPages];
	for (int i = 0; i < numPages; i++) {
		pagesContent[i] = new char[pageSize];
	}
	//vector<char[pageSize]> pagesContent(numPages);
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
}

#endif
