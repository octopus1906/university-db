#pragma once

#include "Person.hpp"

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
