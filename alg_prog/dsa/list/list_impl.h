#ifndef LINEAR_LIST_IMPL_H
#define LINEAR_LIST_IMPL_H

#include "list.h"

template <typename T>
LinearList<T>::LinearList()
{
    this->capacity = LINEARLIST_INITIAL_CAPACITY;
    this->size = 0;
    this->elements = new T[this->capacity];
}

template <typename T>
LinearList<T>::LinearList(size_t c)
{
    this->capacity = c <= 0 ? LINEARLIST_INITIAL_CAPACITY : c;
    this->size = 0;
    this->elements = new T[this->capacity];
}

template <typename T>
LinearList<T>::~LinearList()
{
    if (this->elements != nullptr)
    {
        delete[] this->elements;
    }

    this->capacity = 0;
    this->size = 0;
}

template <typename T>
void LinearList<T>::resize()
{
    this->capacity *= LINEARLIST_GROWTH_FACTOR;
    T *newElements = new T[this->capacity];

    for (size_t i = 0; i < this->size; i++)
    {
        newElements[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newElements;
}

template <typename T>
void LinearList<T>::addElement(T element)
{
    if (this->size >= this->capacity)
    {
        this->resize();
    }

    this->elements[this->size++] = element;
}

template <typename T>
T LinearList<T>::deleteElement(size_t index)
{
    if (index >= this->size)
    {
        throw std::runtime_error("index is not valid for deletion");
    }

    T deleted = this->elements[index];
    // moving the to be deleted element to the end of the list
    for (size_t i = index; i < this->size - 1; i++)
    {
        this->elements[i] = this->elements[i + 1];
    }

    this->size--;
    return deleted;
}

template <typename T>
size_t LinearList<T>::searchElement(T element)
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->elements[i] == element)
        {
            return i;
        }
    }

    throw std::runtime_error("element not present in the list");
}

template <typename T>
LinearListIterator<T>::LinearListIterator(LinearList<T> &l) : linearList{l}, currentPosition{0} {}

template <typename T>
bool LinearListIterator<T>::valid()
{
    return this->currentPosition < this->linearList.size;
}

template <typename T>
T LinearListIterator<T>::current()
{
    if (!this->valid())
    {
        throw std::runtime_error("invalid iterator");
    }

    return this->linearList.elements[this->currentPosition];
}

template <typename T>
void LinearListIterator<T>::next()
{
    if (!this->valid())
    {
        throw std::runtime_error("invalid iterator");
    }

    this->currentPosition++;
}

template <typename T>
void LinearListIterator<T>::reset()
{
    this->currentPosition = 0;
}

#endif // LINEAR_LIST_IMPL_H