#ifndef HashTable_h
#define HashTable_h

#include <string>
#include <vector>
using namespace std;

/*         !!!  TO RUN THE PROGRAM, SOURCE FILE OF THE CLASS SHOULD BE EXLUCED FROM THE PROJECT SINCE IT IS TEMPLATED CLASS  !!!   
						
						
						THIS CODE IS THE MODIFIED VERSION OF THE LECTURE CODE.
*/	


template<class HashedObj>
class HashTable {

public:
	enum EntryType { ACTIVE, EMPTY, DELETED };
	
	HashTable(const HashedObj &notFound,int size = 101);
	HashTable(const HashTable & rhs):ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),array(rhs.array),currentSize(rhs.currentSize){}

	const HashedObj& find(const HashedObj& x) const;

	void makeEmpty();
	void insert(const HashedObj& x);
	void remove(const HashedObj& x);

	const HashTable& operator=(const HashTable& rhs);
	
private:
	struct HashEntry {
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY): element(e), info(i) { }

	};



	vector<HashEntry> array;
	int currentSize;
	HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const;
	int findPos(const HashedObj & x) const;
	void rehash();

};


template<class HashedObj>
int Hash(const HashedObj& x, int tableSize);

template<class HashedObj>
bool operator==(const HashedObj& lhs, const HashedObj& rhs);

template<class HashedObj>
bool operator!=(const HashedObj& lhs, const HashedObj& rhs);





#include "HashTable.cpp"




#endif 
