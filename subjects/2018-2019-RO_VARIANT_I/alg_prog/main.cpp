#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define DEFAULT_CLIENT_NAME "CLI"
#define DEFAULT_CLIENT_INCOME 10.0

class Dwelling
{
private:
    std::string type;
    double price;
    bool profitable;

public:
    Dwelling(const std::string &type, double price, bool profitable) : type{type}, price{price}, profitable{profitable} {}

    bool isProfitable() const { return this->profitable; }

    double getPrice() const { return this->price; }
};

class Client
{
private:
    std::string name;
    double income;

public:
    Client(const std::string &name = DEFAULT_CLIENT_NAME, double income = DEFAULT_CLIENT_INCOME)
    {
        this->name = name.size() < 3 ? DEFAULT_CLIENT_NAME : name;
        this->income = income < 0.0 ? DEFAULT_CLIENT_INCOME : income;
    }

    virtual double totalIncome() const { return this->income; }

    virtual std::string toString() const { return this->name + std::to_string(this->totalIncome()); }

    virtual bool isInterested(const Dwelling &d) const = 0;

    virtual const std::string &getName() const { return this->name; }

    virtual ~Client() = default;
};

class Company : public Client
{
private:
    double moneyFromInvestments;

public:
    Company(double moneyFromInvestments, const std::string &name = DEFAULT_CLIENT_NAME, double income = DEFAULT_CLIENT_INCOME) : Client::Client(name, income), moneyFromInvestments{moneyFromInvestments} {}

    double totalIncome() const override
    {
        return Client::totalIncome() + this->moneyFromInvestments;
    }

    bool isInterested(const Dwelling &d) const override
    {
        return d.getPrice() / 12.0 < this->totalIncome() && d.isProfitable();
    }
};

class Person : public Client
{
public:
    Person(const std::string &name = DEFAULT_CLIENT_NAME, double income = DEFAULT_CLIENT_INCOME) : Client::Client(name, income) {}

    bool isInterested(const Dwelling &d) const override
    {
        return d.getPrice() / 360.0 < this->totalIncome() / 2.0;
    }
};

typedef bool (*compareClients)(Client *c1, Client *c2);

void merge(std::vector<Client *> &clients, size_t startLeft, size_t startRight, size_t endRight, compareClients relation)
{
    size_t i = startLeft, j = startRight;
    std::vector<Client *> temp;

    while (i < startRight && j < endRight)
    {
        if (relation(clients.at(i), clients.at(j)))
        {
            temp.push_back(clients.at(i));
            i++;
        }
        else
        {
            temp.push_back(clients.at(j));
            j++;
        }
    }

    while (i < startRight)
    {
        temp.push_back(clients.at(i++));
    }

    while (j < endRight)
    {
        temp.push_back(clients.at(j++));
    }

    for (size_t k = 0; k < temp.size(); k++)
    {
        clients[startLeft + k] = temp[k];
    }
}

void mergeSortHelper(std::vector<Client *> &clients, size_t start, size_t end, compareClients relation)
{
    if (start + 1 >= end)
    {
        return;
    }

    size_t midpoint = start + (end - start) / 2;
    mergeSortHelper(clients, start, midpoint, relation);
    mergeSortHelper(clients, midpoint, end, relation);

    merge(clients, start, midpoint, end, relation);
}

void mergeSort(std::vector<Client *> &clients, compareClients relation)
{
    mergeSortHelper(clients, 0, clients.size(), relation);
}

std::vector<Client *> interestedClients(const std::unordered_map<std::string, Client *> &clients, const Dwelling &d)
{
    std::vector<Client *> result;

    for (auto iter = clients.begin(); iter != clients.end(); iter++)
    {
        if (iter->second->isInterested(d))
        {
            result.push_back(iter->second);
        }
    }

    mergeSort(result, [](Client *c1, Client *c2)
              { return c1->getName() < c2->getName(); });
    return result;
}

int main()
{
    std::unordered_map<std::string, Client *> clients{};

    Client *company1 = new Company{300.0, "TwoStart", 800000.0};
    Client *company2 = new Company{10000.0, "Fort", 400000.0};
    Client *person1 = new Person("Ana", 1000000.0);
    Client *person2 = new Person("Mihai", 50000000.0);

    clients[company1->getName()] = company1;
    clients[company2->getName()] = company2;
    clients[person1->getName()] = person1;
    clients[person2->getName()] = person2;

    Dwelling d1{"apartament", 150000.0, false};
    Dwelling d2{"casa", 500000.0, true};

    std::cout << "===== INTERESTED CLIENTS IN DWELLING: 'apartament' =====\n";
    for (const auto &c : interestedClients(clients, d1))
    {
        std::cout << c->toString() << "\n";
    }

    std::cout << "\n===== INTERESTED CLIENTS IN DWELLING: 'casa' =====\n";
    for (const auto &c : interestedClients(clients, d2))
    {
        std::cout << c->toString() << "\n";
    }

    delete company1;
    delete company2;
    delete person1;
    delete person2;

    return 0;
}