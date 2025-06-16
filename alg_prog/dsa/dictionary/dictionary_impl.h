#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "dictionary.h"

Dictionary::Dictionary(size_t c): hash_table{c} {}

Dictionary::~Dictionary() = default;

void Dictionary::addElement(TKey k, TValue v)
{
    this->hash_table.addElement(k, v);
}

KeyValuePair Dictionary::deleteElement(TKey k)
{
    return this->hash_table.deleteElement(k);
}

KeyValuePair Dictionary::searchElement(TKey k)
{
    return this->hash_table.searchElement(k);
}

DictionaryIterator::DictionaryIterator(Dictionary &d) : dictionary{d}, currentPosition{0} {}

bool DictionaryIterator::valid()
{
    return this->currentPosition < this->dictionary.hash_table.getCapacity();
}

KeyValuePair DictionaryIterator::current()
{
    while (this->valid() && this->dictionary.hash_table.getElements()[this->currentPosition].getKey() == NULL_KEY)
    {
        this->currentPosition++;
    }

    if (!this->valid())
    {
        throw std::exception();
    }

    return this->dictionary.hash_table.getElements()[this->currentPosition];
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