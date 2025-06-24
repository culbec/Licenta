// 1. Binary search on sorted list in decreasing order
// We need to return the position of the element or the position
// where the element needs to be inserted so that the list remains sorted
// * The element exists: return its position
// * The element does not exist:
//  * We consume the list (start index >= end index -inclusive because of 1 indexing-)
//  * If the length of the list is 0, we return 1
//  * If the element is less than the LIST[start] element, we return start
//  * If the element is greater thaen the LIST[start] element, we return start+1
// START IMPLEMENTATION - PSEUDOCODE
// SubAlgoritm binarySearchDecreasing(list^{i}, elem^{i}, start^{i}, end^{i}, position^{o})
//     @ returns the position of the element in a list that is sorted in decreasing order
//     @ if the element does not exist, we return the position where it needs to be inserted
//     @ so that the list remains sorted
//     @ list      - a list sorted in decreasing order
//     @ elem      - the element to search for
//     @ start     - start index of searching = 1
//     @ end       - end index of searching = list.length()
//     @ position  - the position of the element, if it exists,
//     @               otherwise the position where the element needs to be inserted so that the list remains sorted
//     Daca start >= end Atunci
//         Daca list.length() == 0 Atunci
//             position <- start
//         AltfelDaca elem < list[start] Atunci
//             position <- start + 1
//         Altfel
//             position <- start
//         SfDaca
//         @returnare, sfarsit subalgoritm
//     @SfDaca

//     mid <- start + (end - start + 1) / 2

//     Daca elem == list[mid] Atunci
//         position <- mid
//         @returnare, sfarsit subalgoritm
//     AtlfelDaca elem < list[mid] Atunci
//         position <- binarySearchDecreasing(list, elem, mid, end)
//     Altfel
//         position <- binarySearchDecreasing(list, elem, start, mid)
//     SfDaca
// SfSubAlgoritm

// 2. Circular permutation with k positions to the right
// SubAlgoritm permutareCirculara(text^{i}, k^{i}, output^{o})
//     @ determines the circular permutation with k positions to the right
//     @ text      - the text to perform the circular permutation on
//     @ k         - the order of the permutation
//     @ output    - the circular permutation result
//     output <- text

//     @ no need to make permutation if k == 0 or k == text.length()
//     Daca k == 0 v k == text.length() Atunci
//         @returnare
//     @SfDaca

//     @ we can do the circular permutation in Theta(n) time, where n is the size of
//     @ the text
//     Pentru i <- 1, text.length() Executa
//         @ bound checking with text.length()
//         @ if we overflow, we go back to the beginning
//         output[i] <- output[(i + k) % text.length()]
//     SfPentru
// SfSubalgoritm

// 3. Check if an array represents an inorder traversal of a binary search tree
// An inorder traversal of a binary search tree will always return the nodes
// sorted in increasing order
// For example:
//          10
//         /  |
//        6    20           => (1, 3, 4, 6, 10, 20)
//       /
//      3
//     / |
//    1   4
// * Knowing that the passed array is an array that contains a permutation of the 1..n
// sequence, we can check if the position in the array contains the position itself as an element
// * If not, that means we need to change the positions
// * We can hold the permutations in a map, to avoid repeating them
// * If the map is empty, then we don't have any permutation => 0
// * If the map is not empty => collect all key:value pairs and put them in a list
// SubAlgoritm isInorderTraversal(a^{i}, permutations^{o})
//     @ checks if the array a represents an inorder traversal
//     @ a             - array that contains a permutation of the 1..n sequence
//     @ permutations  - 0 if the array is an inorder traversal, otherwise a list of permutations
//     @                   needed so that the array is transformed in an inorder traversal

//     @ mapping - dictionar unde cheia este un numar natural, iar valoarea tot un numar natural
//     @ folosit pentru a stoca permutarile, cu search time Theta(1) amortizat
//     mapping <- {}

//     Pentru i <- 1, a.length() Executa
//         Daca a[i] != i Atunci
//             @ each permutation will be ordered in the result
//             Daca i < a[i] Atunci
//                 mapping.put(i, a[i])
//             Altfel
//                 mapping.put(a[i], i)
//             SfDaca
//         SfDaca
//     SfPentru

//     Daca mapping.length() != 0 Atunci
//         Pentru i <- 1, mapping.length() Executa
//             permutations.add((mapping[i].key, mapping[i].value))
//         SfPentru
//     Altfel
//         permutation <- 0
//     SfDaca
// SfSubAlgoritm

// 4.
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Product
{
private:
    std::string name;
    int baseprice;

public:
    Product(const std::string &name, int baseprice) : name{name},
                                                      baseprice{baseprice} {}

    virtual int total_price()
    {
        return this->baseprice;
    }

    virtual std::string toString()
    {
        return this->name;
    }

    virtual ~Product() {}
};

class Computer : public Product
{
private:
    int tax;

public:
    Computer(const std::string &name, int baseprice, int tax) : Product::Product(name, baseprice), tax{tax} {}

    int total_price() override
    {
        return Product::total_price() + this->tax;
    }

    std::string toString() override
    {
        return Product::toString() + ", " + std::to_string(this->total_price());
    }

    ~Computer() = default;
};

class SorterByTotalPrice
{
public:
    static void sort(std::vector<Product *> &products)
    {
        std::sort(products.begin(), products.end(), [](Product *p1, Product *p2)
                  { return p1->total_price() > p2->total_price(); });
    }
};

// 5.
class Contact
{
private:
    std::string name;

public:
    Contact(const std::string &name) : name{name} {}

    virtual void sendMessage(const std::string &message) const = 0;

    virtual const std::string &getName() const { return this->name; }

    virtual ~Contact() = default;
};

class Person : public Contact
{
private:
    std::string number;

public:
    Person(const std::string &name, const std::string &number) : Contact::Contact(name), number{number} {}

    void sendMessage(const std::string &message) const override
    {
        std::cout << this->getName() << ", " << this->number << ": " << message << "\n";
    }
};

class Group : public Contact
{
private:
    std::vector<Contact *> contacts;

public:
    Group(const std::string &name) : Contact::Contact(name) {}

    void addContact(Contact *contact) { this->contacts.push_back(contact); }

    void sendMessage(const std::string &message) const override
    {
        for (auto contact : this->contacts)
        {
            contact->sendMessage(message);
        }
    }

    ~Group()
    {
        for (auto &c : this->contacts)
        {
            if (c == nullptr) {
                continue;
            }
            delete c;
            c = nullptr;
        }
    }
};

int main()
{
    // 4.
    std::vector<Product *> computers{
        new Computer("HC90", 140, 10),
        new Computer("HC91", 100, 12),
        new Computer("HC85", 150, 15)};

    SorterByTotalPrice::sort(computers);
    std::cout << computers[0]->toString();
    for (auto c : computers)
    {
        delete c;
    }

    std::cout << "\n\n";

    // 5.
    Contact *mother = new Person{"Mother", "1234"};
    Contact *father = new Person{"Father", "4321"};
    Contact *jane = new Person{"Jane", "5432"};
    Contact *john = new Person{"John", "2345"};

    Group *parents = new Group{"Parents"};
    parents->addContact(mother);
    parents->addContact(father);

    Group family{"Family"};
    family.addContact(parents);
    family.addContact(jane);

    family.sendMessage("You are invited to my birthday party next week!");
    john->sendMessage("You are invited to my birthday party next week!");

    delete john;

    return 0;
}