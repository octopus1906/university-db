#include "student.hpp"

int main()
{
    std::vector<Student> database{};

    while (1) {
        std::cout << "\n*** Students database ***" << std::endl;
        std::cout << "What'd you like to do?" << std::endl;
        std::cout << "1. Initialize a student list\n"
                  << "2. Show current student list\n"
                  << "3. Remove student from the list\n"
                  << "4. Find student by surname\n"
                  << "5. Find student by personal id\n"
                  << "6. Sort student list by personal id\n"
                  << "7. Sort student list by surname\n"
                  << "8. Save data to the file\n"
                  << "9. Read data from the file\n"
                  << "10. Run test function\n"
                  << "Press any other button to exit\n";
        try {
            size_t option{};
            std::cout << "Choose one option: ";
            std::cin >> option;

            switch (option) {
            case 1: {
                std::cout << "Some new students have been added, "
                          << "all values are hardcoded, you have nothing to do here!\n";
                addStudent(database, Student("Jan", "Kowalski", "ul.Cwiartki", "111222", "95062887786", "M"));
                addStudent(database, Student("Ewa", "Dygant", "al.Jerozolimskie", "777766", "04283145461", "F"));
                addStudent(database, Student("Karol", "Krawczyk", "ul.Wolska", "333333", "72082968248", "M"));
                addStudent(database, Student("Marcin", "Mroczek", "ul.Woronicza", "222333", "49072852861", "M"));
                addStudent(database, Student("Jola", "Cygan", "ul.Bursztynowa", "987789", "78081951876", "F"));
                addStudent(database, Student("Ela", "Kowal", "al.Gwiazd", "111444", "83081899446", "F"));
                break;
            }
            case 2: {
                std::cout << "Here you can find full list of the students:\n";
                printDatabase(database);
                break;
            }
            case 3: {
                std::cout << "Provide studentID of the student that you want to remove: \n";
                std::string studentId{};
                std::cin >> studentId;
                try {
                    removeStudent(database, findByStudentId(database, studentId));
                    std::cout << "Student with ID: "
                              << "studentId"
                              << " has been deleted from the list!\n";
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Provide surname of the student that you want to display: \n";
                std::string surname{};
                std::cin >> surname;
                try {
                    std::cout << findByLastName(database, surname);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Provide personal ID of the student that you want to display: \n";
                std::string personalId{};
                std::cin >> personalId;
                if (validatePersonalId(personalId)) {
                    try {
                        std::cout << findByPersonalId(database, personalId);
                    } catch (const std::out_of_range& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "STOP! You have provided incorrect personal ID number!\n";
                }
                break;
            }
            case 6: {
                std::cout << "Sorted list by personal ID looks as follows: \n";
                sortByPersonalID(database);
                printDatabase(database);
                break;
            }
            case 7: {
                std::cout << "Sorted list by surname looks as follows: \n";
                sortByLastName(database);
                printDatabase(database);
                break;
            }
            case 8: {
                std::cout << "Provide a file name: \n";
                std::string fileName{};
                std::cin >> fileName;
                if (-1 == writeToFile(database, fileName)) {
                    std::cerr << "Error: writing operation failed!" << std::endl;
                }
                break;
            }
            case 9: {
                std::cout << "Provide a file name: \n";
                std::string fileName{};
                std::cin >> fileName;
                database.clear();
                if (-1 == readFromFile(database, fileName)) {
                    std::cerr << "Error: reading operation failed!" << std::endl;
                }
                break;
            }
            case 10: {
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