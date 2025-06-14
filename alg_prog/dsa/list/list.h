// Linear Lists
// A linear list is an ordered collection where each element has it designated position
// and where an hierarchy is crucial for identifying each element:
//  * there is an unique first element;
//  * there is an unique last element;
//  * each element (except the last) has exactly one successor;
//  * each element (except the first) has exactyle one predecessor.
// This hierarchy and proposition is crucial for allowing insertions, deletions or searches
// in a sequence <l1, l2, ..., ln> of elements of type T, where 'n' is the size of the sequence.

// The position of the first element in the list is crucial for identifying where the sequence begins,
// and if we know the position of an element, then we can determine all elements of the sequence.
// A list is 'circular' if the last element points to the first element, thus creating a cycle
// in the collection ordering.

// The position of an element can be:
//  * its rank: the order number of the element, similar to tables or vectors;
//  * a reference to the location of the next element (an address, an index...);
// For both cases, a position is valid if its points to a correct element in a list (an existing position in the list)
// and is not NULL (non-existing).

// The ADT for a Linear List is presented below. A table approach was considered.

#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include <exception>

#define LINEARLIST_INITIAL_CAPACITY 10
#define LINEARLIST_GROWTH_FACTOR 2

template <typename T>
class LinearListIterator;

template <typename T>
class LinearList
{
    friend class LinearListIterator<T>;

private:
    size_t capacity; // the current capacity of the list
    size_t size;     // the current size of the list
    T *elements;     // the collection of elements

    /**
     * Resizes the list if operations on it exceed the current capacity
     */
    void resize();

public:
    LinearList();

    explicit LinearList(size_t c);

    ~LinearList();

    /**
     * Adds a new element to the list
     * @param element: the new element to be added into the list
     */
    void addElement(T element);

    /**
     * Deletes an element from the list
     * @param index: the position of the element to be deleted
     * @return the deleted element
     * @exception if the position is not valid
     */
    T deleteElement(size_t index);

    /**
     * Searches for an element in the list
     * @param element: the element to be searched
     * @return the index of the element
     * @exception if the element does not exist
     */
    size_t searchElement(T element);
};

// An iterator is used for traversing any container. Its purpose is to decouple
// the traversing operation from the list itself, because when traversed, a container
// may allow other operations through an iterator
template <typename T>
class LinearListIterator
{
private:
    LinearList<T> &linearList; // reference to the list that will be iterated
    size_t currentPosition;    // the current position where the iterator resides

    /**
     * Tells whether the iterator is within the lists bounds or
     * if it exceeded them
     * @return true if the iterator is still valid, false otherwise
     */
    bool valid();
public:
    explicit LinearListIterator(LinearList<T>& l);

    /**
     * Returns the current element from the iterator
     * @return the current element pointed by the iterator
     * @exception if the iterator is not valid and this method is called
     */
    T current();

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

#include "list_impl.h"

#endif // LINEAR_LIST_H