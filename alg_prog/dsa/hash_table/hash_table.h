// Hash tables are containers that encapsulate key:value pairs, meant for easy retrieval
// based on the key. The keys are unique, and the most popular types of hash tables
// are those which have a single value associated per key.

// For easy retrieval, hash functions are used. Hash functions are mathematical functions
// which provide a deterministic and (so) unique value for a provided argument. That said,
// collisions can appear, which are situations when two arguments resolve to the same value,
// and they are solved as follows:
//  * Separate Chaining: all values that resolve to the same index in the hash_table are stored in a list,
//  *                    where they can be found easily by traversing the internal list.
//  * Open Addressing: collisions are solved internally, by applying one of the following techniques:
//  *   1. Linear probing: if the hash position is occupied, then we search for the next linearly until we find one;
//  *                      if no position is found, then we might need to start rehashing;
//  *   2. Quadratic proving: linear hashing, but on an arbitrary quadratic polynomial:
//  *           hash + 1^2, hash + 2^2, ..., hash + k^2
//  *       this method leaves gaps between equal hashes and thus is easier to find a place
//  *   3. Double hashing: the element is hashed twice, using two different hashing functions,
//  *                       if a collision appears with the first

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <exception>

typedef int TElem;
typedef TElem TKey;
typedef TElem TValue;

#define NULL_KEY -111111111
#define NULL_VALUE -111111111

class HashTable;
class HashTableIterator;

class KeyValuePair
{
    friend class HashTable;
    friend class HashTableIterator;

private:
    TKey key;
    TValue value;

public:
    KeyValuePair() : key{NULL_KEY}, value{NULL_VALUE} {}
    KeyValuePair(TKey k, TValue v) : key{k}, value{v} {}

    inline TKey getKey() { return this->key; }
    inline TValue getValue() { return this->value; }

    friend std::ostream &operator<<(std::ostream &os, KeyValuePair kvp)
    {
        os << "{" << kvp.getKey() << ":" << kvp.getValue() << "}";
        return os;
    }
};

#define HASH_TABLE_INITIAL_CAPACITY 10
#define HASH_TABLE_GROWTH_FACTOR 2

class HashTable
{
    friend class HashTableIterator;

private:
    size_t capacity;
    size_t size;
    KeyValuePair *elements;

    // Double hashing collision resolution

    inline size_t hash1(TKey k);
    inline size_t hash2(TKey k);

    void resize();

public:
    HashTable(size_t c = HASH_TABLE_INITIAL_CAPACITY);

    ~HashTable();

    /**
     * Adds a KeyValuePair in the hash table with TKey k and TValue v
     * Resizes the HashTable if the key K doesn't find its place after collision resolution
     * or if the HashTable is full
     * @param TKey k: the key of the pair
     * @param TValue v: the value of the pair
     */
    void addElement(TKey k, TValue v);

    /**
     * Deletes a KeyValuePair based on the provided key
     * @param TKey k: The key to delete
     * @return KeyValuePair: the KeyValuePair pointed at by the TKey k
     * @exception if TKey k doesn't point to any KeyValuePair in the HashTable
     */
    KeyValuePair deleteElement(TKey k);

    /**
     * Searches a KeyValuePair based on the provided key
     * @param TKey k: The key to search for
     * @return KeyValuePair: the KeyValuePair pointed at by the TKey k
     * @exception if TKey k doesn't point to any KeyValuePair in the HashTable
     */
    KeyValuePair searchElement(TKey k);

    size_t getCapacity() const { return this->capacity; }

    KeyValuePair *getElements() const { return this->elements; }
};

class HashTableIterator
{
private:
    HashTable &hash_table;  // reference to the hash_table that will be iterated
    size_t currentPosition; // the current position where the iterator resides

    /**
     * Tells whether the iterator is within the hash_table's bounds or
     * if it exceeded them
     * @return true if the iterator is still valid, false otherwise
     */
    bool valid();

public:
    explicit HashTableIterator(HashTable &ht);

    /**
     * Returns the current element from the iterator
     * @return the current element pointed by the iterator
     * @exception if the iterator is not valid and this method is called
     */
    KeyValuePair current();

    /**
     * Moves the iterator to the next position
     * @exception if the iterator is not valid and this method is called
     */
    void next();

    /**
     * Resets the iterator to its initial state
     */
    void reset();
};

#include "hash_table_impl.h"

#endif // HASH_TABLE_H