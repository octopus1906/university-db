#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

class Person {
protected:
    std::string firstName_;
    std::string lastName_;
    std::string address_;
    std::string personalId_;
    std::string gender_;

public:
    Person(std::string firstName, std::string lastName, std::string address,
        std::string personalId, std::string gender)
        : firstName_(firstName)
        , lastName_(lastName)
        , address_(address)
        , personalId_(personalId)
        , gender_(gender)
    {
    }
    virtual ~Person() {}

    std::string getFirstName() const { return firstName_; }
    std::string getLastName() const { return lastName_; }
    std::string getAddress() const { return address_; }
    std::string getPersonalId() const { return personalId_; }
    std::string getGender() const { return gender_; }

    virtual std::ostream& doPrint(std::ostream& os) const = 0;
    virtual std::string getStudentId() const = 0;
    virtual std::string getSalary() const = 0;
    virtual void setSalary(std::string salary) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Person& person)
    {
        return person.doPrint(os);
    }

    bool operator==(const Person& rhs) const
    {
        return (
            this->getFirstName() == rhs.getFirstName()
            && this->getLastName() == rhs.getLastName()
            && this->getAddress() == rhs.getAddress()
            && this->getPersonalId() == rhs.getPersonalId()
            && this->getGender() == rhs.getGender()
            && this->getSalary() == rhs.getSalary()
            && this->getStudentId() == rhs.getStudentId());
    }
};

class Student : public Person {
private:
    std::string studentId_;

public:
    Student(std::string firstName, std::string lastName, std::string address, std::string studentId, std::string personalId, std::string gender)
        : Person(firstName, lastName, address, personalId, gender)
        , studentId_(studentId)
    {
    }
    ~Student() override {}

    std::string getStudentId() const override { return studentId_; }
    std::string getSalary() const { return std::string(); }
    void setSalary(std::string salary) override
    {
        std::cout << salary << " wasted! "
                  << this->getFirstName() << " cannot earn money!\n";
    };

    std::ostream& doPrint(std::ostream& os) const override
    {
        os << "Name: " << this->getFirstName() << "\n";
        os << "Surname: " << this->getLastName() << "\n";
        os << "Address: " << this->getAddress() << "\n";
        os << "StudIden: " << this->getStudentId() << "\n";
        os << "Personal-ID: " << this->getPersonalId() << "\n";
        os << "Gender: " << this->getGender() << "\n";
        os << "\n";
        return os;
    }
};

class Worker : public Person {
private:
    std::string salary_;

public:
    Worker(std::string firstName, std::string lastName, std::string address, std::string salary, std::string personalId, std::string gender)
        : Person(firstName, lastName, address, personalId, gender)
        , salary_(salary)
    {
    }
    ~Worker() override {}

    std::string getStudentId() const override { return std::string(); }
    std::string getSalary() const override { return salary_; }
    void setSalary(std::string salary) override { salary_ = salary; }

    std::ostream& doPrint(std::ostream& os) const override
    {
        os << "Name: " << this->getFirstName() << "\n";
        os << "Surname: " << this->getLastName() << "\n";
        os << "Address: " << this->getAddress() << "\n";
        os << "Earnings: " << this->getSalary() << "\n";
        os << "Personal-ID: " << this->getPersonalId() << "\n";
        os << "Gender: " << this->getGender() << "\n";
        os << "\n";
        return os;
    }
};

void addStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Student> student);
void addWorker(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Worker> worker);
void removeStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Person> student);
void removeAllStudents(std::vector<std::shared_ptr<Person> >& database);
void printDatabase(std::vector<std::shared_ptr<Person> >& database);

std::shared_ptr<Person> findByLastName(std::vector<std::shared_ptr<Person> >& database, const std::string& str);
std::shared_ptr<Person> findByPersonalId(std::vector<std::shared_ptr<Person> >& database, const std::string& personalId);
std::shared_ptr<Person> findByStudentId(std::vector<std::shared_ptr<Person> >& database, const std::string& studentId);

void sortByPersonalID(std::vector<std::shared_ptr<Person> >& database);
void sortByLastName(std::vector<std::shared_ptr<Person> >& database);
void sortBySalary(std::vector<std::shared_ptr<Person> >& database);

void changeSalary(std::shared_ptr<Person>& person, std::string salary);
ssize_t writeToFile(std::vector<std::shared_ptr<Person> >& database, const std::string fileName);
ssize_t readFromFile(std::vector<std::shared_ptr<Person> >& databaseFile, const std::string fileName);
bool validatePersonalId(const std::string& personalId);
bool testFunction(void);

void fulfillDatabase(std::vector<std::shared_ptr<Person> >& database);
bool compareDatabases(std::vector<std::shared_ptr<Person> >& lhs, std::vector<std::shared_ptr<Person> >& rhs);
