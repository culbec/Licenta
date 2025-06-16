// Dictionaries are ADT which are used to store key-value pairs.
// The uniqueness of the keys allows for efficient retrieval of values
// based on the key, making dictionaries a powerful data structure for many applications.

// Dictionaries are mostly implemented using hash tables.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <exception>
#include "../hash_table/hash_table.h"

typedef int TElem;
typedef TElem TKey;
typedef TElem TValue;

#define NULL_KEY -111111111
#define NULL_VALUE -111111111

class Dictionary;
class DictionaryIterator;

#define DICTIONARY_INITIAL_CAPACITY 10
#define DICTIONARY_GROWTH_FACTOR 2

class Dictionary
{
    friend class DictionaryIterator;

private:
    HashTable hash_table;

public:
    Dictionary(size_t c = DICTIONARY_INITIAL_CAPACITY);

    ~Dictionary();

    /**
     * Adds a KeyValuePair in the dictionary with TKey k and TValue v
     * Resizes the Dictionary if the key K doesn't find its place after collision resolution
     * or if the Dictionary is full
     * @param TKey k: the key of the pair
     * @param TValue v: the value of the pair
     */
    void addElement(TKey k, TValue v);

    /**
     * Deletes a KeyValuePair based on the provided key
     * @param TKey k: The key to delete
     * @return KeyValuePair: the KeyValuePair pointed at by the TKey k
     * @exception if TKey k doesn't point to any KeyValuePair in the Dictionary
     */
    KeyValuePair deleteElement(TKey k);

    /**
     * Searches a KeyValuePair based on the provided key
     * @param TKey k: The key to search for
     * @return KeyValuePair: the KeyValuePair pointed at by the TKey k
     * @exception if TKey k doesn't point to any KeyValuePair in the Dictionary
     */
    KeyValuePair searchElement(TKey k);
};

class DictionaryIterator
{
private:
    Dictionary &dictionary; // reference to the dictionary that will be iterated
    size_t currentPosition; // the current position where the iterator resides

    /**
     * Tells whether the iterator is within the dictionary's bounds or
     * if it exceeded them
     * @return true if the iterator is still valid, false otherwise
     */
    bool valid();

public:
    explicit DictionaryIterator(Dictionary &d);

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

#include "dictionary_impl.h"

#endif // DICTIONARY_H