#pragma once

#include <iostream>

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
