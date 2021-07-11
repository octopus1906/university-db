#pragma once

#include "Person.hpp"
#include "Student.hpp"
#include "Worker.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

void addStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Student> student);
void addWorker(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Worker> worker);
void removeStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Person> student);
void removeAllStudents(std::vector<std::shared_ptr<Person> >& database);
void printDatabase(std::vector<std::shared_ptr<Person> >& database);

std::shared_ptr<Person> findByStudentId(std::vector<std::shared_ptr<Person> >& database, const std::string& studentId);
std::shared_ptr<Person> findByLastName(std::vector<std::shared_ptr<Person> >& database, const std::string& str);
std::shared_ptr<Person> findByPersonalId(std::vector<std::shared_ptr<Person> >& database, const std::string& personalId);

void sortByPersonalID(std::vector<std::shared_ptr<Person> >& database);
void sortByLastName(std::vector<std::shared_ptr<Person> >& database);
void sortBySalary(std::vector<std::shared_ptr<Person> >& database);

void changeSalary(std::shared_ptr<Person>& person, std::string salary);
ssize_t writeToFile(std::vector<std::shared_ptr<Person> >& database, const std::string fileName);
ssize_t readFromFile(std::vector<std::shared_ptr<Person> >& databaseFile, const std::string fileName);
bool validatePersonalId(const std::string& personalId);
void fulfillDatabase(std::vector<std::shared_ptr<Person> >& database);
bool compareDatabases(std::vector<std::shared_ptr<Person> >& lhs, std::vector<std::shared_ptr<Person> >& rhs);

bool testFunction(void);
