#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#define DEFAULT_VEHICLE_BASEPRICE 100
#define DEFAULT_CAR_MODEL "Ferrari"
#define DEFAULT_AUTOMATICCAR_ADDITIONALPRICE 200
#define DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE "FrontBack"

class Vehicle
{
private:
    int basePrice;

public:
    Vehicle(int basePrice = DEFAULT_VEHICLE_BASEPRICE)
    {
        this->basePrice = basePrice < 0 ? DEFAULT_VEHICLE_BASEPRICE : basePrice;
    }

    virtual std::string description() const = 0;

    virtual int getPrice() const { return this->basePrice; }

    virtual ~Vehicle() = default;
};

class Car : public Vehicle
{
private:
    std::string model;

public:
    Car(const std::string &model = DEFAULT_CAR_MODEL, int basePrice = DEFAULT_VEHICLE_BASEPRICE) : Vehicle{basePrice}
    {
        this->model = model.empty() ? DEFAULT_CAR_MODEL : model;
    }

    virtual std::string description() const override { return this->model; }

    virtual ~Car() = default;
};

class AutomaticCar : public Car
{
private:
    int additionalPrice;

public:
    AutomaticCar(int additionalPrice = DEFAULT_AUTOMATICCAR_ADDITIONALPRICE, const std::string &model = DEFAULT_CAR_MODEL, int basePrice = DEFAULT_VEHICLE_BASEPRICE) : Car{model, basePrice}
    {
        this->additionalPrice = additionalPrice < 0 ? DEFAULT_AUTOMATICCAR_ADDITIONALPRICE : additionalPrice;
    }

    int getPrice() const override
    {
        return Car::getPrice() + this->additionalPrice;
    }

    std::string description() const override
    {
        return "Automatic car " + Car::description();
    }
};

class CarWithParkingSensor : public Car
{
private:
    std::string sensorType;

public:
    CarWithParkingSensor(const std::string &sensorType = DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE, const std::string &model = DEFAULT_CAR_MODEL, int basePrice = DEFAULT_VEHICLE_BASEPRICE) : Car{model, basePrice}
    {
        this->sensorType = sensorType.empty() ? DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE : sensorType;
    }

    int getPrice() const override
    {
        return Car::getPrice() + 2500;
    }

    std::string description() const override
    {
        return "Car with parking sensor " + sensorType + " " + Car::description();
    }
};

std::vector<std::pair<std::string, size_t>> modelWithNumberOfCars(const std::vector<Vehicle *> &vehicles)
{
    std::vector<std::pair<std::string, size_t>> result{};

    for (const auto &vehicle : vehicles)
    {
        // ALTERNATIVE with STRINGSTREAM DELIMITER SPLIT
        // std::stringstream ss(vehicle->description());
        // std::vector<std::string> tokens;
        // std::string token;
        // while (getline(ss, token, ' '))
        // {
        //     tokens.push_back(token);
        // }

        // std::string model = vehicle->description();
        // if (!tokens.empty())
        // {
        //     model = tokens.back();
        // }
        const Car *car = dynamic_cast<const Car *>(vehicle);
        if (!car)
        {
            // not a vehicle with model
            continue;
        }
        auto model = car->Car::description();

        auto iter = std::find_if(result.begin(), result.end(), [&model](const std::pair<std::string, size_t> &pair)
                                 { return pair.first == model; });

        if (iter != result.end())
        {
            iter->second += 1;
        }
        else
        {
            result.push_back(std::make_pair(model, 1));
        }
    }

    return result;
}

void sortVehicles(std::vector<Vehicle *> &vehicles)
{
    size_t n = vehicles.size();

    for (size_t i = 0; i < n; i++)
    {
        if (vehicles.at(i)->getPrice() < 1000 || vehicles.at(i)->getPrice() > 4000)
        {
            Vehicle *toMove = vehicles.at(i);
            for (size_t j = i; j < vehicles.size() - 1; j++)
            {
                vehicles[j] = vehicles[j + 1];
            }

            vehicles[vehicles.size() - 1] = toMove;
            n--;
            i--;
        }
    }
}

void printDescriptions(const std::vector<Vehicle *> &vehicles)
{
    for (const auto &v : vehicles)
    {
        std::cout << v->description() << ':' << v->getPrice() << "\n";
    }
}

int main()
{
    std::vector<Vehicle *> vehicles{
        new Car{"Audi", 100},
        new AutomaticCar{5000, "Audi", 15000},
        new Car{"Toyota", 10000},
        new AutomaticCar{10000, "Mercedes", 80000},
        new CarWithParkingSensor{"Front", "Opel", 5000}};

    auto pairs = modelWithNumberOfCars(vehicles);
    for (const auto &pair : pairs)
    {
        std::cout << pair.first << ":" << pair.second << "\n";
    }

    sortVehicles(vehicles);
    printDescriptions(vehicles);

    for (auto *v : vehicles)
    {
        delete v;
    }

    return 0;
}