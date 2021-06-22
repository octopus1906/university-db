#include "student.hpp"

bool testFunction(void)
{
    std::vector<Student> testDatabase{};
    std::vector<Student> testDatabaseRef{};

    auto studMarcin = Student("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto studJola = Student("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarol = Student("Karol", "Krawczyk", "ul.Wolska", "333333", "04283145461", "M");
    auto studEla = Student("Ela", "Kowal", "al.Gwiazd", "111444", "78081951876", "F");

    /////////////////////////////////////
    //test adding new students
    /////////////////////////////////////
    addStudent(testDatabase, studMarcin);
    addStudent(testDatabase, studJola);
    addStudent(testDatabase, studKarol);
    addStudent(testDatabase, studEla);

    testDatabaseRef.push_back(studMarcin);
    testDatabaseRef.push_back(studJola);
    testDatabaseRef.push_back(studKarol);
    testDatabaseRef.push_back(studEla);

    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: add student failed\n";
        return false;
    }

    /////////////////////////////////////
    //test deleting students
    /////////////////////////////////////
    removeStudent(testDatabase, studEla);

    testDatabaseRef.pop_back();

    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: remove student failed\n";
        return false;
    }

    /////////////////////////////////////
    //test searching by surname
    /////////////////////////////////////
    try {
        if (findByLastName(testDatabase, "Cygan") != studJola)
        {
            std::cout << "Test: search by last name failed\n";
            return false;
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test searching by personal ID
    /////////////////////////////////////
    try {
        if (findByPersonalId(testDatabase, "83081899446") != studMarcin)
        {
            std::cout << "Test: search by personal ID failed\n";
            return false;
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test searching by student ID
    /////////////////////////////////////
    try {
        if (findByStudentId(testDatabase, "333333") != studKarol)
        {
            std::cout << "Test: search by student ID failed\n";
            return false;
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test sorting by personal ID
    /////////////////////////////////////
    sortByPersonalID(testDatabase);
    std::reverse(testDatabaseRef.begin(), testDatabaseRef.end());
    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: sort by personal ID failed\n";
        return false;
    }

    /////////////////////////////////////
    //test sorting by surname
    /////////////////////////////////////
    sortByLastName(testDatabase);
    std::iter_swap(testDatabaseRef.begin(), testDatabaseRef.begin()+1);
    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: sort by surname failed\n";
        return false;
    }

    /////////////////////////////////////
    //test removing by student ID
    /////////////////////////////////////
    try {
        removeStudent(testDatabase, findByStudentId(testDatabase, "333333"));
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    testDatabaseRef.erase(testDatabaseRef.begin()+1);
    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: removing by student ID failed\n";
        return false;
    }

    /////////////////////////////////////
    //test file handling
    /////////////////////////////////////
    if (-1 == writeToFile(testDatabase, "testBase.txt"))
    {
        std::cerr << "Error: writing operation failed!" << std::endl;
        return false;
    }
    testDatabaseRef.clear();
    if (-1 == readFromFile(testDatabaseRef, "testBase.txt"))
    {
        std::cerr << "Error: reading operation failed!" << std::endl;
        return false;
    }
    if (testDatabase != testDatabaseRef)
    {
        std::cout << "Test: file handling failed\n";
        return false;
    }

    /////////////////////////////////////
    //test personal id validation
    /////////////////////////////////////
    if (0 == validatePersonalId("95062887786")
        || 1 == validatePersonalId("95062887787"))
    {
        std::cout << "Test: personal id validation failed\n";
        return false;
    }

    return true;
}
