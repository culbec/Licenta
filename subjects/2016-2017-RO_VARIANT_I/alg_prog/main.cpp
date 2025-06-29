#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_PIZZA_DESCRIPTION "PizzaDescription"
#define DEFAULT_PIZZA_BASEPRICE 10
#define DEFAULT_PIZZA_WITH_INGREDIENTS_INGREDIENTS_PRICE 4

class Pizza
{
private:
    std::string description;
    int basePrice;

public:
    Pizza(const std::string &description = DEFAULT_PIZZA_DESCRIPTION, int basePrice = DEFAULT_PIZZA_BASEPRICE)
    {
        this->description = description.empty() ? DEFAULT_PIZZA_DESCRIPTION : description;
        this->basePrice = basePrice <= 0 ? DEFAULT_PIZZA_BASEPRICE : basePrice;
    }

    virtual ~Pizza() = default;

    virtual std::string getDescription() const { return this->description; }

    virtual int getPrice() const { return this->basePrice; }
};

class PizzaWithIngredients : public Pizza
{
private:
    int ingredientsPrice;

public:
    PizzaWithIngredients(int ingredientsPrice = DEFAULT_PIZZA_WITH_INGREDIENTS_INGREDIENTS_PRICE,
                         const std::string description = DEFAULT_PIZZA_DESCRIPTION,
                         int basePrice = DEFAULT_PIZZA_BASEPRICE) : Pizza{description, basePrice}
    {
        this->ingredientsPrice = ingredientsPrice <= 0 ? DEFAULT_PIZZA_WITH_INGREDIENTS_INGREDIENTS_PRICE : ingredientsPrice;
    }

    std::string getDescription() const override
    {
        return Pizza::getDescription() + "+ ingredients";
    }

    int getPrice() const override
    {
        return Pizza::getPrice() + this->ingredientsPrice;
    }
};

std::vector<Pizza *> mergePizzas(const std::vector<Pizza *> L1, const std::vector<Pizza *> L2)
{
    size_t startL1 = 0, startL2 = 0;

    std::vector<Pizza *> result{};
    result.reserve(L1.size() + L2.size());

    while (startL1 < L1.size() && startL2 < L2.size())
    {
        if (L1.at(startL1)->getPrice() > L2.at(startL2)->getPrice())
        {
            result.push_back(L1.at(startL1++));
        }
        else
        {
            result.push_back(L2.at(startL2++));
        }
    }

    while (startL1 < L1.size())
    {
        result.push_back(L1.at(startL1++));
    }

    while (startL2 < L2.size())
    {
        result.push_back(L2.at(startL2++));
    }

    return result;
}

void insertionSort(std::vector<Pizza *> &pizzas)
{
    for (size_t i = 1; i < pizzas.size(); i++)
    {
        int j = ((int)i) - 1;
        Pizza *elem = pizzas.at(i);

        while (j >= 0 && elem->getPrice() > pizzas.at(j)->getPrice())
        {
            pizzas[j + 1] = pizzas[j];
            j--;
        }

        pizzas[j + 1] = elem;
    }
}

void printPizzasAndTotalSum(const std::vector<Pizza *> &pizzas)
{
    std::cout << "===== PIZZAS AND THEIR TOTAL SUM =====" << std::endl;

    int totalSum = 0;
    for (const auto &p : pizzas)
    {
        std::cout << p->getDescription() << ' ' << p->getPrice() << std::endl;
        totalSum += p->getPrice();
    }
    std::cout << "Total sum: " << totalSum << std::endl;

    std::cout << std::endl;
}

int main()
{
    std::vector<Pizza *> p1{
        new Pizza{"Diavola", 20},
        new Pizza{"Quattro Stagionni", 15},
        new PizzaWithIngredients{14, "Salami", 5}};

    std::vector<Pizza *> p2{
        new Pizza{"Diavola", 20},
        new PizzaWithIngredients{20, "Quattro Stagionni", 15},
        new PizzaWithIngredients{14, "Salami", 5}};

    insertionSort(p1);
    insertionSort(p2);
    auto L = mergePizzas(p1, p2);

    printPizzasAndTotalSum(L);

    for (auto *p : L)
    {
        delete p;
    }

    return 0;
}