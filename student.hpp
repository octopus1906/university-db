#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Student {
    std::string firstName_;
    std::string lastName_;
    std::string address_;
    std::string studentId_;
    std::string personalId_;
    std::string gender_;

public:
    Student(std::string firstName, std::string lastName, std::string address, std::string studentId, std::string personalId, std::string gender)
        : firstName_(firstName)
        , lastName_(lastName)
        , address_(address)
        , studentId_(studentId)
        , personalId_(personalId)
        , gender_(gender)
    {
    }
    ~Student() {}

    std::string getFirstName(void) const { return firstName_; }
    std::string getLastName(void) const { return lastName_; }
    std::string getAddress(void) const { return address_; }
    std::string getStudentId(void) const { return studentId_; }
    std::string getPersonalId(void) const { return personalId_; }
    std::string getGender(void) const { return gender_; }

    bool operator==(const Student& rhs) const
    {
        return (
            firstName_ == rhs.firstName_
            && lastName_ == rhs.lastName_
            && address_ == rhs.address_
            && studentId_ == rhs.studentId_
            && personalId_ == rhs.personalId_
            && gender_ == rhs.gender_);
    }
};

void addStudent(std::vector<Student>& database, const Student& student);
void removeStudent(std::vector<Student>& database, const Student& student);
void printDatabase(std::vector<Student>& database);
Student& findByLastName(std::vector<Student>& database, const std::string& str);
Student& findByPersonalId(std::vector<Student>& database, const std::string& personalId);
Student& findByStudentId(std::vector<Student>& database, const std::string& studentId);
void sortByPersonalID(std::vector<Student>& database);
void sortByLastName(std::vector<Student>& database);

std::ostream& operator<<(std::ostream& os, const Student& student);
ssize_t writeToFile(std::vector<Student>& database, const std::string fileName);
ssize_t readFromFile(std::vector<Student>& databaseFile, const std::string fileName);

bool validatePersonalId(const std::string& personalId);
bool testFunction(void);
