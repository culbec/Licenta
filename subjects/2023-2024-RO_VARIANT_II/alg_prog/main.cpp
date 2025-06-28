#include <iostream>
#include <string>

#define DEFAULT_SOFA_WIDTH 3
#define DEFAULT_SOFA_HEIGHT 1
#define DEFAULT_SOFA_WITH_ROUND_ARMS_LENGTH_OF_ARMS 2.0

class Sofa
{
private:
    double width;
    double height;
    Sofa *next;
    Sofa *previous;

public:
    Sofa(double width = DEFAULT_SOFA_WIDTH, double height = DEFAULT_SOFA_HEIGHT) : next{nullptr}, previous{nullptr}
    {
        this->width = width <= 0.0 ? DEFAULT_SOFA_WIDTH : width;
        this->height = height <= 0.0 ? DEFAULT_SOFA_HEIGHT : height;
    }

    virtual ~Sofa() = default;

    virtual double getCoefficient() const = 0;

    virtual double getPrice() const
    {
        return this->getCoefficient() * (this->width + this->height);
    }

    virtual Sofa *getNext() const
    {
        return this->next;
    }

    virtual Sofa *getPrevious() const
    {
        return this->previous;
    }

    virtual void setNext(Sofa *next) { this->next = next; }
    virtual void setPrevious(Sofa *previous) { this->previous = previous; }
};

class SofaWithRoundArms : public Sofa
{
private:
    double lengthOfArms;

public:
    SofaWithRoundArms(double lengthOfArms = DEFAULT_SOFA_WITH_ROUND_ARMS_LENGTH_OF_ARMS, double width = DEFAULT_SOFA_WIDTH, double height = DEFAULT_SOFA_HEIGHT) : Sofa{width, height}
    {
        this->lengthOfArms = lengthOfArms <= 0.0 ? DEFAULT_SOFA_WITH_ROUND_ARMS_LENGTH_OF_ARMS : lengthOfArms;
    }

    double getCoefficient() const override
    {
        return 2.0;
    }

    double getPrice() const override
    {
        return Sofa::getPrice() + this->lengthOfArms * 10.0;
    }
};

class ClassicSofa : public Sofa
{
public:
    ClassicSofa(double width = DEFAULT_SOFA_WIDTH, double height = DEFAULT_SOFA_HEIGHT) : Sofa{width, height} {}

    double getCoefficient() const override
    {
        return 1.5;
    }
};

class SellingProducts;
void printProductsIncreasingPrice(const SellingProducts &sp);

class SellingProducts
{
private:
    Sofa *first;
    Sofa *last;

public:
    SellingProducts(Sofa *first = nullptr, Sofa *last = nullptr) : first{first}, last{last} {}

    void addProductToSell(Sofa *sofa)
    {
        if (first == nullptr && last == nullptr)
        {
            first = last = sofa;
            return;
        }

        if (first == last)
        {
            if (first->getPrice() > sofa->getPrice())
            {
                last = sofa;
            }
            else
            {
                first = sofa;
            }
            first->setNext(last);
            last->setPrevious(first);
            return;
        }

        Sofa *current = first;
        Sofa *previous = current->getPrevious();
        Sofa *next = current->getNext();

        while (current != nullptr && current->getPrice() > sofa->getPrice())
        {
            previous = current;
            current = current->getNext();
            next = current ? current->getNext() : nullptr;
        }

        if (current == nullptr)
        {
            // last element, beyond the list
            sofa->setPrevious(last);
            last->setNext(sofa);
            last = sofa;
        }
        else if (previous == nullptr)
        {
            // we are on the first element
            sofa->setNext(first);
            first->setPrevious(sofa);
            first = sofa;
        }
        else if (next == nullptr)
        {
            // we are on the last element
            previous->setNext(sofa);
            sofa->setPrevious(previous);
            sofa->setNext(last);
            last->setPrevious(sofa);
        }
        else
        {
            // in between
            sofa->setPrevious(previous);
            sofa->setNext(current);
            previous->setNext(sofa);
            current->setPrevious(sofa);
        }
    }

    Sofa *getFirstProduct() const { return this->first; };

    void setFirstProduct(Sofa *sofa)
    {
        if (first == nullptr && last == nullptr)
        {
            first = last = sofa;
            return;
        }

        if (first == last)
        {
            delete first;
            first = last = sofa;
            return;
        }

        delete first;
        first = sofa;
        first->setPrevious(nullptr);
    }

    Sofa *getLastProduct() const { return this->last; }

    void setLastProduct(Sofa *sofa)
    {
        if (first == nullptr && last == nullptr)
        {
            first = last = sofa;
            return;
        }

        if (first == last)
        {
            delete last;
            first = last = sofa;
            return;
        }

        delete last;
        last = sofa;
        last->setNext(nullptr);
    }

    ~SellingProducts()
    {
        if (first == nullptr && last == nullptr)
        {
            return;
        }

        Sofa *current = last;
        if (current == nullptr)
        {
            // searching for the last going from first
            // rare case, last should be set
            while (current->getNext() != nullptr)
            {
                current = current->getNext();
            }
        }

        while (current != nullptr)
        {
            Sofa *previous = current->getPrevious();
            delete current;
            current = previous;
        }
    }
};

void printProductsIncreasingPrice(const SellingProducts &sp)
{
    Sofa *current = sp.getLastProduct();

    std::cout << "===== SELLING PRODUCTS IN INCREASING PRICE ORDER =====" << std::endl;
    while (current != nullptr)
    {
        std::cout << current->getPrice() << ' ';
        current = current->getPrevious();
    }
    std::cout << std::endl;
}

void removeProductsPriceRange(SellingProducts &sp, double startPrice, double endPrice)
{
    Sofa *current = sp.getFirstProduct();
    while (current != nullptr && current->getPrice() > endPrice)
    {
        current = current->getNext();
    }

    while (current != nullptr && current->getPrice() >= startPrice)
    {

        Sofa *previous = current->getPrevious();
        Sofa *next = current->getNext();

        if (current == next)
        {
            break;
        }

        if (current == sp.getFirstProduct() && current == sp.getLastProduct())
        {
            sp.setFirstProduct(nullptr);
            sp.setLastProduct(nullptr);
        }
        else if (current == sp.getFirstProduct())
        {
            // first
            sp.setFirstProduct(next);
            current = next;
            continue;
        }
        else if (current == sp.getLastProduct())
        {
            // last
            sp.setLastProduct(previous);
            current = previous;
            continue;
        }
        else
        {
            // in between
            if (previous)
            {
                previous->setNext(next);
            }
            if (next)
            {
                next->setPrevious(previous);
            }
            delete current;
            current = next;
        }
    }
}

int main()
{
    SellingProducts sp{};
    sp.addProductToSell(new ClassicSofa{});
    sp.addProductToSell(new ClassicSofa{5.0, 7.0});
    sp.addProductToSell(new SofaWithRoundArms{1.2});
    sp.addProductToSell(new SofaWithRoundArms{0.9});

    printProductsIncreasingPrice(sp);
    removeProductsPriceRange(sp, 10.0, 20.0);
    printProductsIncreasingPrice(sp);

    return 0;
}