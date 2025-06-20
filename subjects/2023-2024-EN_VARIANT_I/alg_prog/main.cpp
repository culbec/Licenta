// Subalgorithm g(x^{i}, n^{i}, y^{io}, i^{i})
//     @ consumes x
//     If i <= n then
//         @ assigns element at ith posititon in y with element at ith position in x
//         @ goes to the next index i+1
//         y[i] <- x[i]
//         g(x, n, y, i + 1)
//     EndIf
// EndSubalgorithm

// @ GOAL: z will contain the initial y + x_reversed
// Subalgorithm transformare(x^{i}, n^{i}, y^{i}, m^{i}, z^{o}, k^{o})
//     @ x: array of integers (x[1], ..., x[n])
//     @ n: size of x
//     @ y: array of integers (y[1], ..., y[m])
//     @ m: size of y
//     @ z: array of integers (z[1], ..., z[k])
//     @ k: size of z
//     If n = 0 then
//         @ executed when x is consumed (no elements to parse)
//         @ here m will be m + n
//         g(y, m, z, 1)
//         @ k = n + m
//         k <- m
//     Else
//         @ y = (y[1], ..., y[m], x[n], ..., x[1])
//         @ y is composed of the initial y and x_reversed
//         y[m + 1] <- x[n]
//         transformare(x, n-1, y, m+1, z, k)
//     EndIf
// EndSubalgorithm

#include <iostream>
#include <unordered_map>
#include <vector>

// Problema 1
void g(const std::vector<int> &x, int n, std::vector<int> &y, int i)
{
    if (i < n)
    {
        y.push_back(x[i]);
        g(x, n, y, i + 1);
    }
}

void transformare(const std::vector<int> &x, int n, std::vector<int> &y, int m, std::vector<int> &z, int &k)
{
    if (n == 0)
    {
        g(y, m, z, 0);
        k = m;
    }
    else
    {
        y.push_back(x[n - 1]);
        transformare(x, n - 1, y, m + 1, z, k);
    }
}

// Problema 2: algorithm cu WORST CASE O(n^3) care cauta patru numere naturale x,y,z,t (x < y < z < t) pt. care:
//      a[x] + a[y] + a[z] + a[t] = 0
// Daca nu exista: -1

void fourNumber(const std::vector<int> &a)
{
    std::unordered_map<int, std::vector<size_t>> sumPositionsMapping{};

    for (size_t x = 0; x < a.size() - 3; x++)
    {
        for (size_t y = x + 1; y < a.size() - 2; y++)
        {
            for (size_t z = y + 1; z < a.size() - 1; z++)
            {
                sumPositionsMapping[a[x] + a[y] + a[z]] = {x, y, z};
            }
        }
    }

    for (size_t t = 3; t < a.size(); t++)
    {
        auto elem = a.at(t);
        int target_elem = -elem;

        if (sumPositionsMapping.count(target_elem) == 1)
        {
            auto indexes = sumPositionsMapping.at(target_elem);

            if (t > indexes[2])
            {
                std::cout << indexes[0] << ',' << indexes[1] << ',' << indexes[2] << ',' << t << '\n';
                return;
            }
        }
    }

    std::cout << "-1\n";
}

// Problema 3: implementare clase
#include <string>

class MyObject
{
protected:
    // Store value as string for generic printing
    std::string value;

public:
    MyObject(const std::string &val) : value{val} {}

    virtual void print() const
    {
        std::cout << value << " ";
    }

    virtual ~MyObject() = default;
};

class MyInteger : public MyObject
{
public:
    MyInteger(int item) : MyObject(std::to_string(item)) {}
};

class MyString : public MyObject
{
public:
    MyString(const std::string &item) : MyObject(item) {}
};

class MyListIterator;

class MyObjectList
{
    friend class MyListIterator;

private:
    std::vector<MyObject *> list;

public:
    MyObjectList &add(MyObject *item)
    {
        list.push_back(item);
        return *this;
    }

    ~MyObjectList()
    {
        for (size_t i = 0; i < list.size(); i++)
        {
            delete list[i];
        }
    }
};

class MyListIterator
{
private:
    MyObjectList &l;
    size_t currentPos;

public:
    MyListIterator(MyObjectList &l) : l{l}, currentPos{0} {}

    bool isValid() { return currentPos < l.list.size(); }
    void next()
    {
        currentPos += 1;
    }
    MyObject *element()
    {
        return l.list.at(currentPos);
    }
};

void function()
{
    MyObjectList list{};
    list.add(new MyInteger{2}).add(new MyString{"Hi"});
    MyString *s = new MyString{"Bye"};
    list.add(s).add(new MyString{"5"});

    MyListIterator i{list};
    while (i.isValid())
    {
        MyObject *o = i.element();
        o->print();
        i.next();
    }
}

// Problema 4
class Person
{
private:
    std::string surname;
    std::string firstname;
    int age;

public:
    Person(const std::string &surname, const std::string &firstname, int age) : surname{surname}, firstname{firstname}, age{age} {}

    const std::string &getSurname() const { return this->surname; }
    const std::string &getFirstname() const { return this->firstname; }
    int getAge() const { return this->age; }
};

typedef bool (*sortCriteria)(const Person &, const Person &);

std::vector<Person> merge(const std::vector<Person> &l1, const std::vector<Person> &l2, sortCriteria criteria)
{
    size_t i = 0, j = 0;
    std::vector<Person> result;

    while (i < l1.size() && j < l2.size())
    {
        if (criteria(l1.at(i), l2.at(j)))
        {
            result.push_back(l1.at(i++));
        }
        else
        {
            result.push_back(l2.at(j++));
        }
    }

    while (i < l1.size())
    {
        result.push_back(l1.at(i++));
    }

    while (j < l2.size())
    {
        result.push_back(l2.at(j++));
    }

    return result;
}

std::vector<Person> mergeSortHelper(const std::vector<Person> &list, sortCriteria criteria, size_t start, size_t end)
{
    if (start >= end)
    {
        return {};
    }
    else if (start == end - 1)
    {
        return {list.at(start)};
    }

    auto m = start + (end - start) / 2;
    auto left = mergeSortHelper(list, criteria, start, m);
    auto right = mergeSortHelper(list, criteria, m + 1, end);

    return merge(left, right, criteria);
}

std::vector<Person> mergeSort(const std::vector<Person> &list, sortCriteria criteria)
{
    return mergeSortHelper(list, criteria, 0, list.size());
}

void runPerson()
{
    std::vector<Person> l1 = {
        Person("PS1", "PF1", 20),
        Person("PS2", "PF2", 10),
        Person("PS3", "PF3", 80)};

    std::vector<Person> l2 = {
        Person("PS100", "PF10", 300),
        Person("PS19", "PF5", 5),
        Person("PS32", "PF70", -20)};

    auto r1 = mergeSort(l2, [](const Person &a, const Person &b)
                        { return a.getSurname() < b.getSurname() && a.getFirstname() < b.getFirstname(); });

    auto r2 = mergeSort(l2, [](const Person &a, const Person &b)
                        { return a.getAge() < b.getAge(); });

    auto r3 = mergeSort(l2, [](const Person &a, const Person &b)
                        { if (a.getAge() == b.getAge()) {
                            return a.getSurname() < b.getSurname() && a.getFirstname() < b.getFirstname();
                        }
                    return a.getAge() < b.getAge(); });
}

int main()
{
    std::vector<int> x = {1, 2, 3, 4};
    std::vector<int> y = {5, 6, 7};
    std::vector<int> z;

    int n = x.size(), m = y.size(), k = 0;
    transformare(x, n, y, m, z, k);

    std::cout << "### K = " << k + 1 << " ###\n";
    std::cout << "### Z = [";
    for (const auto &e : z)
    {
        std::cout << e << " ";
    }
    std::cout << "] ###\n";

    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, -8, -9};
    fourNumber(a);

    function();
    runPerson();

    return 0;
}
