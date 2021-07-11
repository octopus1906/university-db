#include "person.hpp"

int main()
{
    std::vector<std::shared_ptr<Person> > database{};

    while (1) {
        std::cout << "\n*** Students database ***" << std::endl;
        std::cout << "What'd you like to do?" << std::endl;
        std::cout << "1. Initialize a student list\n"
                  << "2. Add new student to the list\n"
                  << "3. Add new worker to the list\n"
                  << "4. Show current list\n"
                  << "5. Remove student from the list\n"
                  << "6. Find person by surname\n"
                  << "7. Find person by personal id\n"
                  << "8. Modify salary by personal id\n"
                  << "9. Sort list of people by personal id\n"
                  << "10. Sort list of people by surname\n"
                  << "11. Sort list of people by salary (students will be deleted!)\n"
                  << "12. Save data to the file\n"
                  << "13. Read data from the file\n"
                  << "14. Run test function\n"

                  << "Press any other button to exit\n";
        try {
            size_t option{};
            std::cout << "Choose one option: ";
            std::cin >> option;

            switch (option) {
            case 1: {
                std::cout << "New people have been added, "
                          << "all values are hardcoded, you have nothing to do here!\n";
                fulfillDatabase(database);
                break;
            }
            case 2: {
                std::cout << "Provide first name of the student that you want to add: \n";
                std::string firstName{};
                std::cin >> firstName;
                std::cout << "Provide last name of the student that you want to add: \n";
                std::string lastName{};
                std::cin >> lastName;
                std::cout << "Provide address of the student that you want to add: \n";
                std::string address{};
                std::cin >> address;
                std::cout << "Provide studentID of the student that you want to add: \n";
                std::string studentId{};
                std::cin >> studentId;
                std::cout << "Provide personalId of the student that you want to add: \n";
                std::string personalId{};
                std::cin >> personalId;
                if (!validatePersonalId(personalId)) {
                    std::cerr << "Wrong personal ID! Student not added!\n";
                    break;
                }
                std::cout << "Provide gender of the student that you want to add (F/M): \n";
                std::string gender{};
                std::cin >> gender;
                if (gender != "M" && gender != "F") {
                    std::cerr << "There are only two genders - M or F! Student not added!\n";
                    break;
                }
                addStudent(database, std::make_shared<Student>(firstName, lastName, address, studentId, personalId, gender));
                break;
            }
            case 3: {
                std::cout << "Provide first name of the worker that you want to add: \n";
                std::string firstName{};
                std::cin >> firstName;
                std::cout << "Provide last name of the worker that you want to add: \n";
                std::string lastName{};
                std::cin >> lastName;
                std::cout << "Provide address of the worker that you want to add: \n";
                std::string address{};
                std::cin >> address;
                std::cout << "Provide salary of the worker that you want to add: \n";
                std::string salary{};
                std::cin >> salary;
                std::cout << "Provide personalId of the worker that you want to add: \n";
                std::string personalId{};
                std::cin >> personalId;
                if (!validatePersonalId(personalId)) {
                    std::cerr << "Wrong personal ID! Worker not added!\n";
                    break;
                }
                std::cout << "Provide gender of the worker that you want to add (F/M): \n";
                std::string gender{};
                std::cin >> gender;
                if (gender != "M" && gender != "F") {
                    std::cerr << "There are only two genders - M or F! Worker not added!\n";
                    break;
                }
                addWorker(database, std::make_shared<Worker>(firstName, lastName, address, salary, personalId, gender));
                break;
            }
            case 4: {
                std::cout << "Here you can find full list of the students:\n";
                printDatabase(database);
                break;
            }
            case 5: {
                std::cout << "Provide studentID of the student that you want to remove: \n";
                std::string studentId{};
                std::cin >> studentId;
                try {
                    removeStudent(database, findByStudentId(database, studentId));
                    std::cout << "Student with ID: "
                              << studentId
                              << " has been deleted from the list!\n";
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                break;
            }
            case 6: {
                std::cout << "Provide surname of the person that you want to display: \n";
                std::string surname{};
                std::cin >> surname;
                try {
                    std::cout << *(findByLastName(database, surname));
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "Provide personal ID of the person that you want to display: \n";
                std::string personalId{};
                std::cin >> personalId;
                if (validatePersonalId(personalId)) {
                    try {
                        std::cout << *(findByPersonalId(database, personalId));
                    } catch (const std::out_of_range& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "STOP! You have provided incorrect personal ID number!\n";
                }
                break;
            }
            case 8: {
                std::cout << "Provide personal ID of the person that's salary you want to modify: \n";
                std::string personalId{};
                std::cin >> personalId;

                std::cout << "Provide a new salary value: \n";
                std::string salary{};
                std::cin >> salary;
                if (validatePersonalId(personalId)) {
                    std::shared_ptr<Person> ptr = findByPersonalId(database, personalId);
                    changeSalary(ptr, salary);

                } else {
                    std::cout << "STOP! You have provided incorrect personal ID number!\n";
                }
                break;
            }
            case 9: {
                std::cout << "Sorted list by personal ID looks as follows: \n";
                sortByPersonalID(database);
                printDatabase(database);
                break;
            }
            case 10: {
                std::cout << "Sorted list by surname looks as follows: \n";
                sortByLastName(database);
                printDatabase(database);
                break;
            }
            case 11: {
                removeAllStudents(database);
                std::cout << "Sorted list by salary looks as follows: \n";
                sortBySalary(database);
                printDatabase(database);
                break;
            }
            case 12: {
                std::cout << "Provide a file name: \n";
                std::string fileName{};
                std::cin >> fileName;
                if (-1 == writeToFile(database, fileName)) {
                    std::cerr << "Error: writing operation failed!" << std::endl;
                }
                break;
            }
            case 13: {
                std::cout << "Provide a file name: \n";
                std::string fileName{};
                std::cin >> fileName;
                database.clear();
                if (-1 == readFromFile(database, fileName)) {
                    std::cerr << "Error: reading operation failed!" << std::endl;
                }
                break;
            }
            case 14: {
                std::cout << "Test result: " << (testFunction() ? "OK\n" : "FAIL\n");
                break;
            }
            default: {
                return 0;
            }
            }
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}