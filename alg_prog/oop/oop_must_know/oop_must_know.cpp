#include <iostream>

// OOP stands on four fundamental columns:
// * Encapsulation: private or protected members are accessible only by that class, friend classes or sibling classes (protected)
// * Abstractization: declaration is decoupled from the implementation
//                    - this allows for multiple definitions of the class's operations that might serve multiple purposes
// * Inheritance: the ability to reuse code; derived classes inherit from their parent all protected/public methods, allowing
// *              reuse of code;
// * Polymorphism: the ability of a derived class to do something different than its parent is supposed to do so, or that a parent has
// *               multiple uses and definitions across its children
// *    Overriding: re-writing the base functionalities of a method with other code
// *    Overloading: adding more arguments to a function, therefore multiple functions with with the same name, but different signature, may exist

// Overriding and Overloading are tightly coupled with Polymorphishm, as these operations
// allow methods to have either:
//  - same definition, but different behavior;
//  - same name, but other arguments => different behavior;

// In C++ a class can be derived from multiple parent classes, behavior disallowed in other OOP languages such as
// Java or C#, as this is ambiguous.

// class A : public B, protected C, private D
// A inherits B with public modifier, C with protected modifier and D with private modifier

// ===== VISIBILITY MODIFIERS ACROSS BASE/DERIVED CLASSES ===== //
// | BASE       | VISIBILITY BASE           | DERIVED           |
// --------------------------------------------------------------
// | public     | public                    | public            |
// | protected  | public                    | protected         |
// | private    | public                    | non-accessible    |
// | public     | protected                 | protected         |
// | protected  | protected                 | protected         |
// | private    | protected                 | non-accessible    |
// | public     | private                   | private           |
// | protected  | private                   | private           |
// | private    | private                   | non-accessible    |

// Private members are not accesible in derived classes
// More restrictive the visibility modifier is in the inheritance step,
// that visibility will also apply to the elements in the derived class (those inherited from the base class)
//  - protected marks all elements as protected in the derived class;
//  - private marks all elements as private in the derived class;
//  - public does not change the visibility modifier;
// This behavior allows for stricter management in derived classes, so that resources and methods are not leaked
// by classes which should not expose them.

class Base
{
public:
    void f1()
    {
        std::cout << "f1 Base\n";
    }
    void f2()
    {
        std::cout << "f2 Base\n";
        f1();
    }
};

class Derived : public Base
{
public:
    void f1()
    {
        std::cout << "f1 Derived\n";
    }
};

// The execution of the following snippet:
// *     Derived d;
// *    d.f2();
// will result in the following prints
// *    f2 Base
// *    f1 Base
// This is not the desired result, as f1 in Derived is overridden, and has other print
// This is where POLYMORPHISM and the 'virtual' keyword come in play

// The 'virtual' keyword enables 'dynamic binding/dispatch': function declarations will be linked
// at runtime depending on the type of the variable that calls them, instead of
// 'static binding/dispatch' which links function declarations at compile time

// Each function should have a 'final overrider': a class that employs that method without explicitly
// making it virtual or that doesn't make it implicit virtual through:
//  * same name;
//  * same parameter-type list (but not return type);
//  * same cv-qualifiers (const and volatile);
//  * same ref-qualifiers (references)
// The above characteristics mark a non-declared virtual function redeclared in a class as implicit virtual
// If the parameter list is different from the virtual function, then redeclarations of that functions are 'hidden'
// from the class, as it is an overloaded one that doesn't resume to the base class

// Constructors cannot be virtual, as they are always called when a derived object is created
// Destructors need to be virtual, as resources of the base class need to be deallocated
// when the object is destroyed

// When a base class is inherited from using the 'virtual' keyword, only the latest inheritance is considered
// Example:
class A
{
public:
    void show()
    {
        std::cout << "Hello from A \n";
    }
};

class B : public /*virtual*/ A
{
};

class C : public /*virtual*/ A
{
};

class D : public B, public C
{
};

// int main()
// {
//     D object;
//     object.show(); // ERROR: D::show() is ambiguous
// }

// This leads to ambiguity as D inherits from both B and C, which both inherit from A, which transforms to:
// class D: public A, public A {};
// By using the 'virtual' keyword when A is derived from B and C, then D will inherit A only from the latest
// derivation

// If we want to declare abstract classes, we can declare function members which
// have 'pure virtual functions' = functions which have implementation deleted in the base class
// by equaling the function with 0. Any class that has at leats one such pure virtual function is an abstract class
// Example:

// Interfaces are entities which only declare what the one that
// employs it must do, not how it does it. It represents a 'contract' between the user and the creator.
// In Java and C# there are interfaces, whereas in C++ they do not exist.
// Interfaces must have only function declarations, and can have function implementations and members if they are 'default',
// meaning that they are the same for all employers
// Interfaces in C++ can be created by creating a class with no function members and only pure virtual function declarations
// Example:

class Vehicle
{
public:
    virtual void TurnOn() = 0;
    virtual void TurnOff() = 0;
    virtual void Drive(int km) = 0;
    virtual void Stop(int min) = 0;
};

// Bike and Car need to implement all pure virtual functions or
// mark them as pure virtual too

class Bike : public Vehicle
{
public:
    void TurnOn();
    void TurnOff();
    void Drive(int km);
    void Stop(int min);
};

void Bike::TurnOn()
{
    std::cout << "Bike turns on.\n";
}
void Bike::TurnOff()
{
    std::cout << "Bike turns off.\n";
}
void Bike::Drive(int km)
{
    std::cout << "Bike drives " << km << " kilometers.\n";
}
void Bike::Stop(int min)
{
    std::cout << "Bike stops " << min << " minutes.\n";
}

class Car : public Vehicle
{
public:
    void TurnOn();
    void TurnOff();
    void Drive(int km);
    void Stop(int min);
};

void Car::TurnOn()
{
    std::cout << "Car TurnOn.\n";
}
void Car::TurnOff()
{
    std::cout << "Car se TurnOff.\n";
}
void Car::Drive(int km)
{
    std::cout << "Car drives " << km << " kilometers.\n";
}
void Car::Stop(int min)
{
    std::cout << "Car stops " << min << " minutes.\n";
}

void Path(Vehicle *v)
{
    v->TurnOn();
    v->Drive(3);
    v->Stop(2);
    v->Drive(2);
    v->TurnOff();
}

// int main()
// {
//     Vehicle *b = new Bike;
//     Path(b);
//     Vehicle *m = new Car;
//     Path(m);
//     delete m;
//     delete b;
// }

// Example Abstract Class:
class Animal
{
protected:
    double weight;
    double age;
    double speed;

public:
    inline Animal(double w, double a, double s) : weight{w}, age{a}, speed{s} {}

    // pure virtual functions that will be determined by each derived class

    virtual double average_weight() = 0;
    virtual double average_age() = 0;
    virtual double average_speed() = 0;

    // functions that act on the pure virtual functions, thus are the same in all derived classes

    bool fat()
    {
        return this->weight > this->average_weight();
    }

    bool fast()
    {
        return this->speed > this->average_speed();
    }

    bool young()
    {
        return 2 * this->age < this->average_age();
    }

    void print()
    {
        std::cout << (fat() ? "fat, " : "skinny, ");
        std::cout << (fast() ? "fast, " : "slow, ");
        std::cout << (young() ? "young" : "old") << "\n";
    }
};

class Parrot : public Animal
{
public:
    inline Parrot(double w, double a, double s) : Animal(w, a, s) {}

    double average_weight() { return 0.5; }
    double average_age() { return 6; }
    double average_speed() { return 90; }
};

class Bear : public Animal
{
public:
    inline Bear(double w, double a, double s) : Animal(w, a, s) {}

    double average_weight() { return 80; }
    double average_age() { return 30; }
    double average_speed() { return 20; }
};

class Horse : public Animal
{
public:
    inline Horse(double w, double a, double s) : Animal(w, a, s) {}

    double average_weight() { return 40; }
    double average_age() { return 12; }
    double average_speed() { return 180; }
};

int main()
{
    Parrot p(0.6, 1, 80);
    Bear b(500, 40, 46);
    Horse h(900, 8, 70);

    p.print();
    b.print();
    h.print();
    return 0;
}