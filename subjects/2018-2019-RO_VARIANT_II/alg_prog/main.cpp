#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_RAILCAR_NAME "OK"
#define DEFAULT_PASSENGERCAR_CAPACITY 10
#define DEFAULT_RESTAURANTCAR_NUMBER_OF_TABLES 4

class RailCar
{
private:
    std::string name;
    RailCar *next;

public:
    RailCar(const std::string &name, RailCar *next = nullptr) : next{next}
    {
        this->name = name.size() < 2 ? DEFAULT_RAILCAR_NAME : name;
    }

    virtual bool isProfitable() const = 0;
    virtual std::string toString() const = 0;
    virtual RailCar *clone() const = 0;

    virtual const std::string &getName() const { return this->name; }
    virtual RailCar *getNext() const { return this->next; }
    virtual void setNext(RailCar *railCar)
    {
        this->next = railCar;
    }

    virtual ~RailCar() = default;
};

class PassengerCar : public RailCar
{
private:
    int capacity;

public:
    PassengerCar(const std::string &name, int capacity = DEFAULT_PASSENGERCAR_CAPACITY, RailCar *next = nullptr) : RailCar::RailCar(name, next)
    {
        this->capacity = capacity <= 0 ? DEFAULT_PASSENGERCAR_CAPACITY : capacity;
    }

    bool isProfitable() const override { return this->capacity > 40; }
    std::string toString() const override { return this->getName() + std::to_string(this->capacity); }

    RailCar *clone() const override
    {
        std::string name = this->getName();
        int capacity = this->capacity;

        return new PassengerCar{name, capacity};
    }
};

class RestaurantCar : public RailCar
{
private:
    int numberOfTables;

public:
    RestaurantCar(const std::string &name, int numberOfTables = DEFAULT_RESTAURANTCAR_NUMBER_OF_TABLES, RailCar *next = nullptr) : RailCar::RailCar(name, next)
    {
        this->numberOfTables = numberOfTables <= 0 ? DEFAULT_RESTAURANTCAR_NUMBER_OF_TABLES : numberOfTables;
    }

    bool isProfitable() const override { return this->numberOfTables >= 20; }
    std::string toString() const override { return this->getName() + std::to_string(this->numberOfTables); }

    RailCar *clone() const override
    {
        std::string name = this->getName();
        int numberOfTables = this->numberOfTables;

        return new RestaurantCar{name, numberOfTables};
    }
};

void destroyLocomotive(RailCar *current)
{
    if (current == nullptr)
    {
        return;
    }

    destroyLocomotive(current->getNext());
    delete current;
}

class Locomotive
{
private:
    RailCar *first;

public:
    Locomotive(RailCar *first = nullptr) : first{first} {}

    void attachRailCar(RailCar *railCar)
    {
        if (this->first == nullptr)
        {
            this->first = railCar;
            return;
        }

        RailCar *current = this->first;
        RailCar *previous = nullptr;
        while (current != nullptr && current->toString() < railCar->toString())
        {
            previous = current;
            current = current->getNext();
        }

        railCar->setNext(current);
        
        if (previous == nullptr) {
            this->first = railCar;
        } else {
            previous->setNext(railCar);
        }
    }
    RailCar *getFirstRailCar() const { return this->first; }

    void setFirstRailCar(RailCar *railCar)
    {
        if (this->first != nullptr)
        {
            delete this->first;
        }
        this->first = railCar;
    }

    ~Locomotive() {
        destroyLocomotive(this->first);
    }
};

void eliminateNonProfitableWagons(Locomotive &l)
{
    if (l.getFirstRailCar() == nullptr)
    {
        return;
    }

    RailCar *current = l.getFirstRailCar();
    RailCar *previous = nullptr;
    while (current != nullptr)
    {
        if (!current->isProfitable())
        {
            RailCar* toDelete = current;
            if (previous == nullptr)
            {
                // first railcar
                l.setFirstRailCar(current->getNext());
                current = l.getFirstRailCar();
            }
            else
            {
                // somewhere in between
                previous->setNext(current->getNext());
                current = current->getNext();
            }
            delete toDelete;
        } else {
            previous = current;
            current = current->getNext();
        }
    }
}

Locomotive reverseCopiesLocomotive(const Locomotive &l)
{
    std::vector<RailCar *> cars{};

    RailCar *current = l.getFirstRailCar();
    while (current != nullptr)
    {
        cars.push_back(current->clone());
        current = current->getNext();
    }

    Locomotive lReversed{};
    for (int i = cars.size() - 1; i >= 0; i--)
    {
        lReversed.attachRailCar(cars.at(i));
    }

    return lReversed;
}



int main()
{
    Locomotive l{};

    l.attachRailCar(new PassengerCar{"P1", 50});
    l.attachRailCar(new PassengerCar{"P2", 32});
    l.attachRailCar(new PassengerCar{"P3", 40});
    l.attachRailCar(new RestaurantCar{"R1", 25});
    l.attachRailCar(new RestaurantCar{"R2", 20});

    eliminateNonProfitableWagons(l);
    Locomotive l1 = reverseCopiesLocomotive(l);

    RailCar *currentL1 = l1.getFirstRailCar();
    while (currentL1 != nullptr)
    {
        std::cout << currentL1->toString() << "\n";
        currentL1 = currentL1->getNext();
    }
}