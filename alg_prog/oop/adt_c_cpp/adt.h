#include <iostream>

// Abstract Data Type (ADT) in C

// Data referencing between different files is hard to do, especially when
// we want to also protect such data from unrestricted access

// Declaring data as 'static' blocks that data in the file where it is declared,
// and so it cannot be referenced elsewhere

// Abstract Data Types come in help. These structures declare the attributes and operations
// that a specific entity can work with, creating a 'contract' between the user and the developer
// Each entity created using this ADT will have the same attributes and same operations, but their
// values and implementations may differ

// Example - integer vector

struct vec_struct
{
private:
    // attributes or data members
    int *e;
    int d;

public:
    // operations or function members

    // inline functions (functions declared inside an ADT) are acceptable if their
    // implementation is not complex

    void destroy()
    {
        if (e != nullptr)
        {
            delete[] e;
            e = nullptr;
            d = 0;
        }
    }

    // if not, function declarations need to be provided elsewhere

    void init(int *e1, int d);
    void squared();
    void print();
};

// ===== HOWEVER ====== //
// These structures are not protected, in a way that each attribute and each operation can be accesed
// without restricting visibility IN PURE C. In CPP visibility specifiers were added, and implicit
// visibility for structs is 'public'
// This is where classes come in help, where we can specify which operations are:
// * public: accessible from wherever;
// * protected: accessible only by siblings or 'friend' functions;
// * private: accessible only within the class implementation or 'friend' functions;
// * static: accessible without the need of instantiating a class;
// Java has something called "package restricted visibility", where an entity can be referenced only in the same package (namespace)
// Implicit visibility is 'private'
// 'friend' keyword act as a bridge between a certain class and another entity
// allowing the entity to access the private members of that specific class

class Vec_Class
{
    // accessible only in this class or friend functions
private:
    // default values for safety
    int *e = nullptr;
    int d = 0;

    // acessible by siblings or friend functions
    // which can access
protected:
    void print_siblings();

    // accessible by everyone
public:
    // If the initialization process is not complex, we can define the attributes here
    // Vec_Class(int *e1, int d1): e{e1}, d{d1} {}

    // Implicit constructor: generated automatically by the class blueprint
    Vec_Class();

    // Explicit constructor: we declare it
    // If no Explicit constructor exists => Implicit constructor is created
    Vec_Class(int *e1, int d1);

    // Operations
    void squared();
    void print();

    // Destructor: called when an object exists its scope
    // Used for freeing resources that are used by that object
    ~Vec_Class();
};