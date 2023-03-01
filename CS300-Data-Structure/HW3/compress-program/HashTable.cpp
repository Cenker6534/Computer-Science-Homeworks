#include "HashTable.h"

using namespace std;

// Modified version of the Lecture Codes




// checks if n is prime. 
bool isPrime(int n)
{
    if (n == 2 || n == 3){
        return true;
    }
        

    if (n == 1 || n % 2 == 0) {
        return false;
    }
        

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// find next prime number after n.
int nextPrime(int n)
{
    if (n % 2 == 0) {
        n++;
    }

    for (; !isPrime(n); n += 2){
        ;
    }

    return n;
}

template<class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size)
    : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
    makeEmpty();
}

template<class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{

    int p = Hash(x, array.size()); // current position

    

    while (array[p].info != EMPTY && array[p].element != x) {

        p += 1;  // add the difference

        if (p >= array.size()) {             // perform the mod
            p -= array.size();                // if necessary
        }
    }

    return p;
}

template<class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template<class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
    int currentPos = findPos(x);

    if (isActive(currentPos)) {
        array[currentPos].info = DELETED;
    }
}

template<class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const
{
    int currentPos = findPos(x);

    if (isActive(currentPos)) {
        return array[currentPos].element;
    }

    return ITEM_NOT_FOUND;
}

template<class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
    // Insert x as active
    int currentPos = findPos(x);

    if (isActive(currentPos)) {
        return;
    }

    array[currentPos] = HashEntry(x, ACTIVE);

    // enlarge the hash table if necessary 
    if (++currentSize >= array.size() / 2) {
        rehash();
    }
}

template<class HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));

    for (int j = 0; j < array.size(); j++){
        array[j].info = EMPTY;
    }
        

    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE) {
            insert(oldArray[i].element);
        }
}

            
template<class HashedObj>
const HashTable<HashedObj>& HashTable<HashedObj>::operator=(const HashTable& rhs) {
    currentSize = rhs.currentSize;
    array = rhs.array;
    ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
    return (*this);
}

template<class HashedObj>
void HashTable<HashedObj>::makeEmpty() {
    for (int i = 0; i < array.size(); i++)
    {
        array[i].info = EMPTY;
    }
    currentSize = 0;
}

