#include <iostream>
#include "list/list.h"
#include "hash_table/hash_table.h"
#include "dictionary/dictionary.h"
#include "bst/bst.h"

int main()
{
    // ===========================================================
    // LinearList example
    // ===========================================================
    LinearList<int> l;

    std::cout << "Adding 5, 6 and 8 to the list...\n";

    l.addElement(5);
    l.addElement(6);
    l.addElement(8);

    std::cout << "Deleting the first element...\n";
    int deleted = l.deleteElement(0);
    std::cout << "Deleted element: " << deleted << "\n\n";

    std::cout << "Searching an invalid element...\n";
    try
    {
        size_t index = l.searchElement(9);
        std::cout << "Index of element 9 is: " << index << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR! Message: " << e.what() << "\n\n";
    }

    LinearListIterator<int> li(l);

    std::cout << "Current iterated element: " << li.current() << "\n";
    li.next();
    std::cout << "Current iterated element: " << li.current() << "\n";
    li.next();
    try
    {
        int current = li.current();
        std::cout << "Current iterated element: " << current << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR! Message: " << e.what() << "\n\n";
    }

    // ===========================================================
    // HashTable example
    // ===========================================================
    HashTable d;

    std::cout << "Adding 5:2, 6:4 and 8:3 to the hash table...\n";
    d.addElement(5, 2);
    d.addElement(6, 4);
    d.addElement(8, 3);

    std::cout << "Deleting the element with key '5'...\n";
    KeyValuePair deletedD = d.deleteElement(5);
    std::cout << "Deleted element: " << deletedD << "\n\n";

    std::cout << "Searching an invalid key...\n";
    try
    {
        KeyValuePair kvp = d.searchElement(9);
        std::cout << "Searched element: " << kvp << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR!\n\n";
    }

    HashTableIterator di(d);

    std::cout << "Current iterated element: " << di.current() << "\n";
    di.next();
    std::cout << "Current iterated element: " << di.current() << "\n";
    di.next();
    try
    {
        KeyValuePair current = di.current();
        std::cout << "Current iterated element: " << current << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR! Message: " << e.what() << "\n\n";
    }

    // ===========================================================
    // Dictionary example
    // ===========================================================
    Dictionary dd;

    std::cout << "Adding 5:2, 6:4 and 8:3 to the dictionary...\n";
    dd.addElement(5, 2);
    dd.addElement(6, 4);
    dd.addElement(8, 3);

    std::cout << "Deleting the element with key '5'...\n";
    KeyValuePair deletedDD = dd.deleteElement(5);
    std::cout << "Deleted element: " << deletedDD << "\n\n";

    std::cout << "Searching an invalid key...\n";
    try
    {
        KeyValuePair kvp = dd.searchElement(9);
        std::cout << "Searched element: " << kvp << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR!\n\n";
    }

    DictionaryIterator ddi(dd);

    std::cout << "Current iterated element: " << ddi.current() << "\n";
    ddi.next();
    std::cout << "Current iterated element: " << ddi.current() << "\n";
    ddi.next();
    try
    {
        KeyValuePair current = ddi.current();
        std::cout << "Current iterated element: " << current << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR! Message\n\n";
    }

    // ===========================================================
    // BST example
    // ===========================================================
    BST<int> bst;
    std::cout << "Adding 5, 2 and 8 to the BST...\n";
    bst.add(5);
    bst.add(2);
    bst.add(8);

    std::cout << "Searching for 2 in the BST...\n";
    if (bst.exists(2))
    {
        std::cout << "2 exists in the BST.\n";
    }
    else
    {
        std::cout << "2 does not exist in the BST.\n";
    }
    std::cout << "Searching for 10 in the BST...\n";
    if (bst.exists(10))
    {
        std::cout << "10 exists in the BST.\n";
    }
    else
    {
        std::cout << "10 does not exist in the BST.\n";
    }
    std::cout << "Pre-order traversal: ";
    for (const auto &elem : bst.pre_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    std::cout << "Post-order traversal: ";
    for (const auto &elem : bst.post_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    std::cout << "In-order traversal: ";
    for (const auto &elem : bst.in_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    std::cout << "Removing 5 from the BST...\n";
    if (bst.remove(5))
    {
        std::cout << "5 was removed from the BST.\n";
    }
    else
    {
        std::cout << "5 was not found in the BST.\n";
    }
    std::cout << "Searching for 5 in the BST after removal...\n";
    if (bst.exists(5))
    {
        std::cout << "5 exists in the BST.\n";
    }
    else
    {
        std::cout << "5 does not exist in the BST.\n";
    }
    std::cout << "Pre-order traversal after removal: ";
    for (const auto &elem : bst.pre_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    std::cout << "Post-order traversal after removal: ";
    for (const auto &elem : bst.post_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    std::cout << "In-order traversal after removal: ";
    for (const auto &elem : bst.in_order())
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    return 0;
}