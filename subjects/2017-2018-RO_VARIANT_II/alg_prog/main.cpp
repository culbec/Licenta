#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define DEFAULT_PARTICIPANT_NAME "Participant"
#define DEFAULT_PARTICIPANT_TOWN "Town"
#define DEFAULT_VOLUNTEER_YEARS 3
#define DEFAULT_EMPLOYEE_DEPARTMENT "IT"

class Participant
{
private:
    std::string name;
    std::string town;

public:
    Participant(const std::string &name = DEFAULT_PARTICIPANT_NAME, const std::string &town = DEFAULT_PARTICIPANT_TOWN)
    {
        this->name = name.empty() ? DEFAULT_PARTICIPANT_NAME : name;
        this->town = town.empty() ? DEFAULT_PARTICIPANT_TOWN : town;
    }

    virtual ~Participant() = default;

    virtual const std::string &getTown() const
    {
        return this->town;
    }

    virtual std::string toString() const
    {
        return this->name + this->town;
    }
};

class Volunteer : public Participant
{
private:
    int years;

public:
    Volunteer(int years = DEFAULT_VOLUNTEER_YEARS, const std::string &name = DEFAULT_PARTICIPANT_NAME, const std::string &town = DEFAULT_PARTICIPANT_TOWN) : Participant{name, town}
    {
        this->years = years <= 0 ? DEFAULT_VOLUNTEER_YEARS : years;
    }

    ~Volunteer() = default;

    std::string toString() const override
    {
        return "Volunteer " + std::to_string(years) + " years" + Participant::toString();
    }
};

class Employee : public Participant
{
private:
    std::string department;

public:
    Employee(const std::string &department = DEFAULT_EMPLOYEE_DEPARTMENT, const std::string &name = DEFAULT_PARTICIPANT_NAME, const std::string &town = DEFAULT_PARTICIPANT_TOWN) : Participant{name, town}
    {
        this->department = this->department.empty() ? DEFAULT_EMPLOYEE_DEPARTMENT : department;
    }

    ~Employee() = default;

    std::string toString() const override
    {
        return "Employee " + department + Participant::toString();
    }
};

class ONG
{
private:
    std::vector<Participant *> participants;

public:
    ONG(const std::vector<Participant *> participants = std::vector<Participant *>{}) : participants{participants} {}

    std::vector<Participant *> getAll(bool volunteer) const
    {
        std::vector<Participant *> result{};

        for (const auto &participant : this->participants)
        {
            if (volunteer)
            {
                if (dynamic_cast<const Volunteer *>(participant) != nullptr)
                {
                    result.push_back(participant);
                }
            }
            else
            {
                if (dynamic_cast<const Employee *>(participant) != nullptr)
                {
                    result.push_back(participant);
                }
            }
        }
        return result;
    }
};

void merge(std::vector<Participant *> &participants, size_t startLeft, size_t startRight, size_t endRight)
{
    size_t i = startLeft, j = startRight;
    std::vector<Participant *> temp{};

    while (i < startRight && j < endRight)
    {
        if (participants.at(i)->getTown() < participants.at(j)->getTown())
        {
            temp.push_back(participants.at(i++));
        }
        else
        {
            temp.push_back(participants.at(j++));
        }
    }

    for (size_t k = 0; k < endRight - startLeft; k++)
    {
        participants[startLeft + k] = temp[k];
    }
}

void mergeSort(std::vector<Participant *> &participants, size_t start, size_t end)
{
    if (start + 1 >= end)
    {
        return;
    }

    size_t midpoint = start + (end - start) / 2;
    mergeSort(participants, start, midpoint);
    mergeSort(participants, midpoint, end);
    merge(participants, start, midpoint, end);
}

std::vector<Participant *> volunteersSortedByTown(const ONG &ong)
{
    auto volunteers = ong.getAll(true);
    mergeSort(volunteers, 0, volunteers.size());
    return volunteers;
}

std::string townWithMaxEmployees(const ONG &ong)
{
    auto employees = ong.getAll(false);

    std::unordered_map<std::string, size_t> townNumEmployeesMapping{};
    std::string town = "";
    size_t maxEmployees = 0;

    for (const auto &employee : employees)
    {
        townNumEmployeesMapping[employee->getTown()]++;
        if (maxEmployees < townNumEmployeesMapping[employee->getTown()])
        {
            town = employee->getTown();
            maxEmployees = townNumEmployeesMapping[town];
        }
    }

    return town;
}

size_t numberOfEmployeesFromOng(const std::vector<ONG> &ongs)
{
    size_t numberOfEmployees = 0;

    for (const auto &ong : ongs)
    {
        numberOfEmployees += ong.getAll(false).size();
    }

    return numberOfEmployees;
}

int main()
{
    ONG ong1{std::vector<Participant *>{
        new Volunteer{10, "Marius", "Cluj-Napoca"},
        new Employee{"HR", "Mirela", "Brasov"}}};
    ONG ong2{std::vector<Participant *>{
        new Volunteer{4, "Mirel", "Zalau"},
        new Employee{"IT", "Vlad", "Iasi"}}};

    std::vector<ONG> ongs{ong1, ong2};

    auto volunteers = volunteersSortedByTown(ongs.at(1));
    std::cout << "===== VOLUNTEERS FROM ONG2 SORTED BY TOWN =====" << std::endl;
    for (auto *volunteer : volunteers)
    {
        std::cout << volunteer->toString() << std::endl;
    }
    std::cout << std::endl;

    for (const auto &ong : ongs)
    {
        auto tWME = townWithMaxEmployees(ong);

        std::cout << "Town with max employees from ONG: " << tWME << std::endl;
    }

    auto nOEFO = numberOfEmployeesFromOng(ongs);
    std::cout << "Number of employees from ONGs: " << nOEFO << std::endl;

    for (auto &ong : ongs)
    {
        auto volunteers = ong.getAll(true);
        auto employees = ong.getAll(false);

        for (auto *v : volunteers)
        {
            delete v;
        }

        for (auto *e : employees)
        {
            delete e;
        }
    }
}