#pragma once

#include <vector>
#include <string>
#include <stdexcept> 
#include <algorithm>
#include <iostream>
#include <fstream>

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
    {}
    ~Student(){}

    std::string getFirstName(void) const {return firstName_;}
    std::string getLastName(void) const {return lastName_;}
    std::string getAddress(void) const {return address_;}
    std::string getStudentId(void) const {return studentId_;}
    std::string getPersonalId(void) const {return personalId_;}
    std::string getGender(void) const {return gender_;}

    bool operator==(const Student& stud1) const {
        return ( 
                firstName_ == stud1.firstName_
                 && lastName_ == stud1.lastName_
                 && address_ == stud1.address_
                 && studentId_ == stud1.studentId_
                 && personalId_ == stud1.personalId_
                 && gender_ == stud1.gender_
        );
    }

    bool operator!=(const Student& stud1) const {
        return ( 
                firstName_ != stud1.firstName_
                 || lastName_ != stud1.lastName_
                 || address_ != stud1.address_
                 || studentId_ != stud1.studentId_
                 || personalId_ != stud1.personalId_
                 || gender_ != stud1.gender_
        );
    }
};

void addStudent(std::vector<Student>& database, const Student& student);
void removeStudent(std::vector<Student>& database, const Student& student);
void printRecord(Student& student);
void printDatabase(std::vector<Student>& database);
Student& findByLastName(std::vector<Student>& database, const std::string& str);
Student& findByPersonalId(std::vector<Student>& database, const std::string& personalId);
Student& findByStudentId(std::vector<Student>& database, const std::string& studentId);
void sortByPersonalID(std::vector<Student>& database);
void sortByLastName(std::vector<Student>& database);

ssize_t writeToFile(std::vector<Student>& database, const std::string fileName);
ssize_t readFromFile(std::vector<Student>& databaseFile, const std::string fileName);

bool validatePersonalId(const std::string& personalId);
bool testFunction(void);
