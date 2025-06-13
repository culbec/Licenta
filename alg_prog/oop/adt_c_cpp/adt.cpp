#include "adt.h"

// '::' operator = resolution operator
// Used for specifying the entity referenced when a certain operation or attribute is accessed through
// an entity
void vec_struct::init(int *e1, int d1)
{
    if (e1 == nullptr || d1 <= 0)
    {
        return;
    }

    if (this->e != nullptr)
    {
        this->destroy();
    }

    this->e = new int[d1];
    this->d = d1;

    for (int i = 0; i < this->d; i++)
    {
        this->e[i] = e1[i];
    }
}

void vec_struct::squared()
{
    if (this->e == nullptr)
    {
        return;
    }

    for (int i = 0; i < this->d; i++)
    {
        this->e[i] *= this->e[i];
    }
}

void vec_struct::print()
{
    if (this->e == nullptr)
    {
        return;
    }

    for (int i = 0; i < this->d; i++)
    {
        std::cout << this->e[i] << ' ';
    }
    std::cout << "\n";
}

void Vec_Class::print_siblings()
{
    std::cout << "I am a sibling!\n";
}

Vec_Class::Vec_Class()
{
    this->e = nullptr;
    this->d = 0;
}

Vec_Class::Vec_Class(int *e1, int d1)
{
    if (e1 == nullptr || d1 < 0)
    {
        this->e = nullptr;
        this->d = 0;
        return;
    }

    if (this->e != nullptr)
    {
        delete[] this->e;
    }

    this->e = new int[d1];
    this->d = d1;

    for (int i = 0; i < this->d; i++)
    {
        this->e[i] = e1[i];
    }
}

void Vec_Class::squared()
{
    if (this->e == nullptr)
    {
        return;
    }

    for (int i = 0; i < this->d; i++)
    {
        this->e[i] *= this->e[i];
    }
}

void Vec_Class::print()
{
    if (this->e == nullptr)
    {
        return;
    }

    for (int i = 0; i < this->d; i++)
    {
        std::cout << this->e[i] << ' ';
    }
    std::cout << "\n";
}

Vec_Class::~Vec_Class()
{
    if (this->e != nullptr)
    {
        delete[] this->e;
        this->e = nullptr;
    }
    this->d = 0;
}