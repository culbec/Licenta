#include <iostream>
#include "list/list.h"
#include "dictionary/dictionary_impl.h"

int main()
{
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

    Dictionary d;

    std::cout << "Adding 5:2, 6:4 and 8:3 to the dictionary...\n";
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

    DictionaryIterator di(d);

    std::cout << "Current iterated element: " << di.current() << "\n";
    di.next();
    std::cout << "Current iterated element: " << di.current() << "\n";
    di.next();
    try
    {
        int current = li.current(); 
        std::cout << "Current iterated element: " << current << "\n\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR! Message\n\n";
    }

    return 0;
}