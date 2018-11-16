#ifndef MY_HASH_NODE
#define MY_HASH_NODE

using namespace std;

class HashNode {
  unsigned long key;   // The hash node's key
  unsigned long value; // The key's associated data

  /* extend if necessary */

public:

  // Add constructors, destructor if necessary

  unsigned long getKey() { return key; }
  unsigned long getValue() { return value; }
  void assign(unsigned long key, unsigned long value); 

  // extend if necessary
};

void HashNode::assign(unsigned long key, unsigned long value) {
  this->key = key;
  this->value = value;
}
/* 
   Implement the assign method 
   and any methods that you may additionally need for the HashTable to work.
*/

#endif
