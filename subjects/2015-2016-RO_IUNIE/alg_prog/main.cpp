#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Student
{
private:
    std::string nume;
    std::string oras;

public:
    Student(const std::string &nume, const std::string &oras)
    {
        this->nume = nume.empty() ? "Student" : nume;
        this->oras = oras.empty() ? "Cluj-Napoca" : oras;
    }

    virtual const std::string &getNume() const { return this->nume; }
    virtual const std::string &getOras() const { return this->oras; }

    virtual std::string toString() const
    {
        return this->nume + this->oras;
    }

    virtual ~Student() = default;
};

class StudentBursier : public Student
{
private:
    int bursa;

public:
    StudentBursier(const std::string &nume, const std::string &oras, int bursa) : Student{nume, oras}
    {
        this->bursa = bursa <= 0 ? 500 : bursa;
    }

    std::string toString() const override
    {
        return Student::toString() + std::to_string(this->bursa);
    }
};

void insertStudent(std::vector<Student *> &students, Student *student)
{
    size_t pos = 0;
    for (pos; pos < students.size(); pos++)
    {
        if (student->getNume() < students.at(pos)->getNume())
        {
            break;
        }
    }

    students.insert(students.begin() + pos, student);
}

void printStudents(const std::vector<Student *> &students)
{
    std::cout << "===== STUDENTS ====" << std::endl;

    for (const auto &student : students)
    {
        std::cout << student->toString() << std::endl;
    }

    std::cout << std::endl;
}

void printOrasStudentiBursieri(const std::vector<Student *> &students)
{
    std::unordered_map<std::string, std::vector<Student *>> cityStudentMapping;

    for (const auto &student : students)
    {
        const StudentBursier *studentBursier = dynamic_cast<const StudentBursier *>(student);
        if (!studentBursier)
        {
            continue;
        }

        cityStudentMapping[studentBursier->getOras()].push_back(student);
    }

    // sorting students
    for (auto &[city, studentList] : cityStudentMapping)
    {
        // selection sort
        for (size_t i = 0; i < studentList.size() - 1; i++)
        {
            size_t minIndex = i;
            for (size_t j = i + 1; j < studentList.size(); j++)
            {
                if (studentList[j]->getNume() < studentList[minIndex]->getNume())
                {
                    minIndex = j;
                }
            }
            std::swap(studentList[i], studentList[minIndex]);
        }
    }

    // printing students
    std::cout << "===== ORAS STUDENTI BURSIERI ====" << std::endl;
    for (const auto &[city, studentList] : cityStudentMapping)
    {
        std::cout << "Oras: " << city << std::endl;
        for (const auto &student : studentList)
        {
            std::cout << student->toString() << std::endl;
        }
    }
}

int main()
{
    std::vector<Student *> studenti;
    insertStudent(studenti, new Student{"Marius", "Arad"});
    insertStudent(studenti, new StudentBursier{"Mirabela", "Oradea", -1});
    insertStudent(studenti, new StudentBursier{"Alin", "Arad", 1000});
    insertStudent(studenti, new StudentBursier{"Alina", "Oradea", 2000});

    printStudents(studenti);
    printOrasStudentiBursieri(studenti);

    for (auto *student : studenti)
    {
        delete student;
    }

    return 0;
}