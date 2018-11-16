#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode> > Table;
  Table *table; // size of table is stored in the Table data structure
  size_t num;   // number of entries in the HashTable;

public:
  HashTable();       // constructor, initializes table of size 1;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)
  size_t hash_function(ulint);  // the table's hash function
  ulint getValue(ulint);    // find and return data associated with key

  void insert(ulint,ulint); // insert data associated with key into table
  void erase(ulint);        // remove key and associated data from table

  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table 

  size_t elementCount = 0;
  // extend if necessary
};

HashTable::HashTable() {
  table = new Table(11);
}

HashTable::HashTable(size_t size) {
  table = new Table(size);
}

HashTable::~HashTable() {
  table->clear();
  delete table;
}

size_t HashTable::size() {
  return table->size();
}

size_t HashTable::hash_function(ulint key) {
  return key % table->size();
}

ulint HashTable::getValue(ulint key) {
  size_t hash = hash_function(key);
  list<HashNode> l = table->at(hash);
  for (HashNode h : l) {
    if (h.getKey() == key) return h.getValue();
  }

  return KEY_NOT_FOUND;
}

void HashTable::insert(ulint key, ulint val) {
  size_t hash = hash_function(key);
  HashNode newNode;
  newNode.assign(key, val); 
  table->at(hash).push_front(newNode);
  elementCount++;

  if (elementCount / size() >= 0.9) rehash(size() * 2);
}

void HashTable::erase(ulint key) {
  size_t hash = hash_function(key);
  list<HashNode> l = table->at(hash);
  for (auto it = l.begin(); it != l.end(); ++it){
    if (it->getKey() == key) {
      l.erase(it);
      break;
    }
  }
  elementCount--;
}

void HashTable::rehash(size_t size) {
  Table *oldTable = table;
  table = new Table(size);

  for (size_t i = 0; i < oldTable->size(); ++i) {
    for (HashNode h : oldTable->at(i)) {
      insert(h.getKey(), h.getValue());
    }
  }
  delete oldTable;
  oldTable = NULL;
}

#endif
