#ifndef HASH_TABLE_IMPL_H
#define HASH_TABLE_IMPL_H

#include "hash_table.h"

HashTable::HashTable(size_t c)
{
    this->capacity = c;
    this->size = 0;
    this->elements = new KeyValuePair[this->capacity];
}

HashTable::~HashTable()
{
    if (this->elements != nullptr)
    {
        delete[] this->elements;
    }

    this->capacity = 0;
    this->size = 0;
}

inline size_t HashTable::hash1(TKey k)
{
    return k % this->capacity;
}

inline size_t HashTable::hash2(TKey k)
{
    return k % this->capacity;
}

void HashTable::resize()
{
    this->capacity *= HASH_TABLE_GROWTH_FACTOR;
    KeyValuePair *newElements = new KeyValuePair[this->capacity];

    for (size_t i = 0; i < this->size; i++)
    {
        if (this->elements[i].key == NULL_KEY || this->elements[i].value == NULL_VALUE)
        {
            continue;
        }

        size_t hash = hash1(this->elements[i].key);
        if (newElements[hash].key == NULL_KEY && newElements[hash].value == NULL_VALUE)
        {
            newElements[hash] = KeyValuePair(this->elements[i].key, this->elements[i].value);
            continue;
        }

        hash = hash2(this->elements[i].key);
        newElements[hash] = KeyValuePair(this->elements[i].key, this->elements[i].value);
    }

    delete[] this->elements;
    this->elements = newElements;
}

void HashTable::addElement(TKey k, TValue v)
{
    if (this->size >= this->capacity)
    {
        this->resize();
    }

    while (true)
    {
        size_t hash = hash1(k);
        if (this->elements[hash].key == NULL_KEY && this->elements[hash].value == NULL_VALUE)
        {
            this->elements[hash] = KeyValuePair(k, v);
            this->size++;
            return;
        }

        hash = hash2(k);
        if (this->elements[hash].key == NULL_KEY && this->elements[hash].value == NULL_VALUE)
        {
            this->elements[hash] = KeyValuePair(k, v);
            this->size++;
            return;
        }
        this->resize();
    }
}

KeyValuePair HashTable::deleteElement(TKey k)
{
    size_t hash = hash1(k);

    if (this->elements[hash].key == k)
    {
        this->size--;
        auto deleted = this->elements[hash];
        this->elements[hash] = KeyValuePair(NULL_KEY, NULL_VALUE);
        return deleted;
    }

    hash = hash2(k);
    if (this->elements[hash].key == k)
    {
        this->size--;
        auto deleted = this->elements[hash];
        this->elements[hash] = KeyValuePair(NULL_KEY, NULL_VALUE);
        return deleted;
    }

    throw std::exception();
}

KeyValuePair HashTable::searchElement(TKey k)
{
    size_t hash = hash1(k);

    if (this->elements[hash].key == k)
    {
        return this->elements[hash];
    }

    hash = hash2(k);
    if (this->elements[hash].key == k)
    {
        return this->elements[hash];
    }

    throw std::exception();
}

HashTableIterator::HashTableIterator(HashTable &ht) : hash_table{ht}, currentPosition{0} {}

bool HashTableIterator::valid()
{
    return this->currentPosition < this->hash_table.capacity;
}

KeyValuePair HashTableIterator::current()
{
    while (this->valid() && this->hash_table.elements[this->currentPosition].key == NULL_KEY)
    {
        this->currentPosition++;
    }

    if (!this->valid())
    {
        throw std::exception();
    }

    return this->hash_table.elements[this->currentPosition];
}

void HashTableIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }
    this->currentPosition++;
}

void HashTableIterator::reset()
{
    this->currentPosition = 0;
}

#endif // HASH_TABLE_IMPL_H