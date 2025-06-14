#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "dictionary.h"

Dictionary::Dictionary(size_t c)
{
    this->capacity = c;
    this->size = 0;
    this->elements = new KeyValuePair[this->capacity];
}

Dictionary::~Dictionary()
{
    if (this->elements != nullptr)
    {
        delete[] this->elements;
    }

    this->capacity = 0;
    this->size = 0;
}

inline size_t Dictionary::hash1(TKey k)
{
    return k % this->capacity;
}

inline size_t Dictionary::hash2(TKey k)
{
    return k % this->capacity;
}

void Dictionary::resize()
{
    this->capacity *= DICTIONARY_GROWTH_FACTOR;
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

void Dictionary::addElement(TKey k, TValue v)
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

KeyValuePair Dictionary::deleteElement(TKey k)
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

KeyValuePair Dictionary::searchElement(TKey k)
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

DictionaryIterator::DictionaryIterator(Dictionary &d) : dictionary{d}, currentPosition{0} {}

bool DictionaryIterator::valid()
{
    return this->currentPosition < this->dictionary.capacity;
}

KeyValuePair DictionaryIterator::current()
{
    while (this->valid() && this->dictionary.elements[this->currentPosition].key == NULL_KEY)
    {
        this->currentPosition++;
    }

    if (!this->valid())
    {
        throw std::exception();
    }

    return this->dictionary.elements[this->currentPosition];
}

void DictionaryIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }
    this->currentPosition++;
}

void DictionaryIterator::reset()
{
    this->currentPosition = 0;
}

#endif // DICTIONARY_IMPL_H