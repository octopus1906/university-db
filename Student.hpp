#pragma once

#include "Person.hpp"

class Student : public Person {
private:
    std::string studentId_;

test

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
