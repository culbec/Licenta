#include <iostream>
#include <string>

// A class has the following purpose: serve as a blueprint for instantianting objects
// which respect the same convention (serve the same goal)

// Example: a Person can have roughly the same attributes: name, age, height, weight etc.

class Person
{
private:
    // as 'std::string' is an object, at initialization the constructors of
    // object data members will be called before the constructor code is executed
    std::string name;
    
    int age;
    int height;
    int weight;

public:
    // const& represents a constant reference of a specific object
    // this constant reference does not trigger any copies and defines that
    // the object will not be altered in any way

    Person() : name{"no one"}, age{10}, height(180), weight(70) {}

    Person(const std::string &n, const int a, const int h, const int w) : name{n}, age{a}, height{h}, weight{w} {}

    // ===== RULE OF THREE ====== //
    // If you declare the destructor, copy method or copy assignment method,
    // then you probably need to declare all three
    // Either means that the object is managing complex resources (e.g. raw pointers)
    // or that the object has non-copyable resources (e.g. ID)

    ~Person() = default;

    // Copy method
    Person(const Person &p)
    {
        this->name = p.name;
        this->age = p.age;
        this->height = p.height;
        this->weight = p.weight;
    }

    // Copy assignment operator
    Person &operator=(const Person &p)
    {
        this->name = p.name;
        this->age = p.age;
        this->height = p.height;
        this->weight = p.weight;

        return *this;
    }

    // ===== RULE OF FIVE ====== //
    // Hardens the rule of three in cases where we want to copy non-copyable resources,
    // but that implies redefining the object that will hold all attributes
    // Example: if a person with an ID is to be copied, then that is a whole new person
    // Declaration of destructor, copy method or copy assignment operator prevents the default
    // declaration of the move method and move assignment operator. That may be a missed optimization opportunity in some cases,
    // but also an issue if resources are not managed well

    // Move method
    Person(Person &&p) = default;

    // Move assignemnt operator
    Person &operator=(Person &&p) = default;

    // ===== RULE OF ZERO ===== //
    // Explicit RULE OF FIVE should deal with ownership
    // If default is desired, all should be default

    // Print method
    friend std::ostream& operator<<(std::ostream& os, const Person& p);

    // functions that have 'const' after them indicate that the function will not
    // alter the class in any way
    const std::string& getName() const {
        return this->name;
    }
};

// friend functions are used to allow two entities to access their private data,
// without creating methods to do so (e.g. getters)
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.name << " | " << p.age << " | " << p.height << " | " << p.weight << "\n";
    return os; 
}

int main() {
    Person p1(
        "Ana",
        70,
        40,
        20
    );
    std::cout << "=== PERSON1 INIT ===\n";
    std::cout << "Person1: " << p1;
    
    Person p2(p1);
    std::cout << "\n=== PERSON2 COPY METHOD PERSON1 ===\n";
    std::cout << "Person1: " << p1;
    std::cout << "Person2: " << p2;
    
    Person p3 = p2;
    std::cout << "\n=== PERSON3 COPY METHOD ASSG PERSON2 ===\n";
    std::cout << "Person1: " << p1;
    std::cout << "Person2: " << p2;
    std::cout << "Person3: " << p3;

    std::cout << "\n=== PERSON4 MOVE METHOD PERSON2 ===\n";
    Person p4(std::move(p2));
    // objects are moved, primitives are kept and copied in the moved location
    std::cout << "Person1: " << p1;
    std::cout << "Person2: " << p2;
    std::cout << "Person3: " << p3;
    std::cout << "Person4: " << p4;

    std::cout << "\n=== PERSON5 MOVE ASSG PERSON4 ===\n";
    Person p5 = std::move(p4);
    // objects are moved, primitives are kept and copied in the moved location
    std::cout << "Person1: " << p1;
    std::cout << "Person2: " << p2;
    std::cout << "Person3: " << p3;
    std::cout << "Person4: " << p4;
    std::cout << "Person5: " << p5;

    std::cout << "\nPerson1 name: " << p1.getName() << "\n";

    std::cout << "Done!\n";

    return 0;
}