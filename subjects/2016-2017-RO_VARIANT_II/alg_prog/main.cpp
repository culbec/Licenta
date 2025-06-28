#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_MELON_LIKE_KG 6.5

class Fruit
{
private:
    bool withSeeds;

public:
    Fruit(bool withSeeds = true) : withSeeds{withSeeds} {}

    virtual ~Fruit() = default;

    virtual std::string getDescription() const = 0;

    bool isWithSeeds() const { return this->withSeeds; }
};

class MelonLike : public Fruit
{
private:
    double kg;

public:
    MelonLike(double kg = DEFAULT_MELON_LIKE_KG, bool withSeeds = false) : Fruit{withSeeds}
    {
        this->kg = kg <= 0.0 ? DEFAULT_MELON_LIKE_KG : kg;
    }

    virtual std::string getDescription() const override
    {
        return std::to_string(this->kg) + " melon like " + (this->isWithSeeds() ? "with seeds" : "without seeds");
    }

    virtual ~MelonLike() = default;
};

class Melon : public MelonLike
{
public:
    Melon(double kg = DEFAULT_MELON_LIKE_KG, bool withSeeds = false) : MelonLike{kg, withSeeds} {}

    std::string getDescription() const override
    {
        return MelonLike::getDescription() + " melon ";
    }
};

class WaterMelon : public MelonLike
{
public:
    WaterMelon(double kg = DEFAULT_MELON_LIKE_KG, bool withSeeds = false) : MelonLike{kg, withSeeds} {}

    std::string getDescription() const override
    {
        return MelonLike::getDescription() + " watermelon";
    }
};

size_t binarySearch(const std::vector<Fruit *> &fruits, Fruit *fruit)
{
    size_t start = 0, end = fruits.size();

    while (start + 1 < end)
    {
        size_t midpoint = start + (end - start) / 2;

        if (fruit->getDescription() == fruits.at(midpoint)->getDescription())
        {
            return midpoint + 1;
        }

        if (fruit->getDescription() < fruits.at(midpoint)->getDescription())
        {
            end = midpoint;
        }
        else
        {
            start = midpoint;
        }
    }

    return start + 1;
}

void insertFruit(std::vector<Fruit *> &fruits, Fruit *fruit)
{
    size_t pos = binarySearch(fruits, fruit);
    fruits.insert(fruits.begin() + pos, fruit);
}

void printFruitsWithOrWithoutSeeds(const std::vector<Fruit *> &fruits, bool withSeeds)
{
    std::cout << "===== FRUITS WITH SEEDS: " << withSeeds << " =====" << std::endl;
    for (const auto &fruit : fruits)
    {
        if (fruit->isWithSeeds() == withSeeds)
        {
            std::cout << fruit->getDescription() << std::endl;
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<Fruit *> fruits{
        new WaterMelon(6, false),
        new Melon(10, true),
        new MelonLike(11, false),
        new WaterMelon(13, true)};
    Fruit *watermelon = new WaterMelon(12, false);

    std::sort(fruits.begin(), fruits.end(), [](Fruit *f1, Fruit *f2)
              { return f1->getDescription() < f2->getDescription(); });
    insertFruit(fruits, watermelon);
    for (const auto &fruit : fruits)
    {
        std::cout << fruit->getDescription() << std::endl;
    }
    printFruitsWithOrWithoutSeeds(fruits, true);
    printFruitsWithOrWithoutSeeds(fruits, false);

    return 0;
}