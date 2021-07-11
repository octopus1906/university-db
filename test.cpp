#include "person.hpp"

bool testFunction(void)
{
    std::vector<std::shared_ptr<Person> > testDatabase{};
    std::vector<std::shared_ptr<Person> > testDatabaseRef{};

    //entries for 1st dababase
    auto studMarcin = std::make_shared<Student>("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto workZygmunt = std::make_shared<Worker>("Zygmunt", "Kasinski", "ul.Okopowa", "1600$", "59062887786", "M");
    auto workHalina = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studJola = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarol = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");
    auto studEla = std::make_shared<Student>("Ela", "Kowal", "al.Gwiazd", "111444", "04283145461", "F");

    //entries for 2nd database
    auto studMarcinRef = std::make_shared<Student>("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto workZygmuntRef = std::make_shared<Worker>("Zygmunt", "Kasinski", "ul.Okopowa", "1600$", "59062887786", "M");
    auto workHalinaRef = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studJolaRef = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarolRef = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");
    auto studElaRef = std::make_shared<Student>("Ela", "Kowal", "al.Gwiazd", "111444", "04283145461", "F");

    /////////////////////////////////////
    //test adding new people
    /////////////////////////////////////
    addStudent(testDatabase, studMarcin);
    addStudent(testDatabase, studJola);
    addStudent(testDatabase, studKarol);
    addStudent(testDatabase, studEla);
    addWorker(testDatabase, workZygmunt);
    addWorker(testDatabase, workHalina);

    testDatabaseRef.push_back(studMarcinRef);
    testDatabaseRef.push_back(studJolaRef);
    testDatabaseRef.push_back(studKarolRef);
    testDatabaseRef.push_back(studElaRef);
    testDatabaseRef.push_back(workZygmuntRef);
    testDatabaseRef.push_back(workHalinaRef);

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: add person failed\n";
        return false;
    }

    /////////////////////////////////////
    //test deleting students
    /////////////////////////////////////
    removeStudent(testDatabase, studKarol);

    testDatabaseRef.erase((testDatabaseRef.begin() + 2));

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: remove student failed\n";
        return false;
    }

    /////////////////////////////////////
    //test changing salary
    /////////////////////////////////////
    std::shared_ptr<Person> ptrFail = findByPersonalId(testDatabase, "83081899446");
    changeSalary(ptrFail, "1500$");
    std::shared_ptr<Person> ptrSucc = findByPersonalId(testDatabase, "59062887786");
    changeSalary(ptrSucc, "1500$");

    testDatabaseRef[3]->setSalary("1500$");

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: change salary failed\n";
        return false;
    }

    /////////////////////////////////////
    //test searching by surname
    /////////////////////////////////////
    try {
        if (!(findByLastName(testDatabase, "Cygan") == studJola)) {
            std::cout << "Test: search by last name failed\n";
            return false;
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test searching by personal ID
    /////////////////////////////////////
    try {
        if (!(findByPersonalId(testDatabase, "83081899446") == studMarcin)) {
            std::cout << "Test: search by personal ID failed\n";
            return false;
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test searching by student ID
    /////////////////////////////////////
    try {
        if (!(findByStudentId(testDatabase, "111444") == studEla)) {
            std::cout << "Test: search by student ID failed\n";
            return false;
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    /////////////////////////////////////
    //test sorting by personal ID
    /////////////////////////////////////
    sortByPersonalID(testDatabase);
    std::reverse(testDatabaseRef.begin(), testDatabaseRef.end());
    std::iter_swap(testDatabaseRef.begin(), testDatabaseRef.begin() + 2);
    std::iter_swap(testDatabaseRef.begin() + 1, testDatabaseRef.begin() + 3);

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: sort by personal ID failed\n";
        return false;
    }

    /////////////////////////////////////
    //test sorting by surname
    /////////////////////////////////////
    sortByLastName(testDatabase);
    std::iter_swap(testDatabaseRef.begin(), testDatabaseRef.begin() + 1);
    std::iter_swap(testDatabaseRef.begin() + 1, testDatabaseRef.begin() + 3);
    std::iter_swap(testDatabaseRef.begin() + 2, testDatabaseRef.begin() + 4);
    std::iter_swap(testDatabaseRef.begin() + 2, testDatabaseRef.begin() + 3);

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: sort by surname failed\n";
        return false;
    }

    /////////////////////////////////////
    //test removing by student ID
    /////////////////////////////////////
    try {
        removeStudent(testDatabase, findByStudentId(testDatabase, "987789"));
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    testDatabaseRef.erase(testDatabaseRef.begin());

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: removing by student ID failed\n";
        return false;
    }

    /////////////////////////////////////
    //test sorting by salary
    /////////////////////////////////////
    removeAllStudents(testDatabase);
    sortBySalary(testDatabase);

    auto it = testDatabaseRef.begin();
    while (it < testDatabaseRef.end()) {
        if (((*it)->getSalary()).empty()) {
            testDatabaseRef.erase(it);
        } else {
            ++it;
        }
    }
    std::reverse(testDatabaseRef.begin(), testDatabaseRef.end());

    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: sort by salary failed\n";
        return false;
    }

    /////////////////////////////////////
    //test file handling
    /////////////////////////////////////
    if (-1 == writeToFile(testDatabase, "testBase.txt")) {
        std::cerr << "Error: writing operation failed!" << std::endl;
        return false;
    }
    testDatabaseRef.clear();
    if (-1 == readFromFile(testDatabaseRef, "testBase.txt")) {
        std::cerr << "Error: reading operation failed!" << std::endl;
        return false;
    }
    if (!(compareDatabases(testDatabase, testDatabaseRef))) {
        std::cout << "Test: file handling failed\n";
        return false;
    }

    /////////////////////////////////////
    //test personal id validation
    /////////////////////////////////////
    if (0 == validatePersonalId("95062887786")
        || 1 == validatePersonalId("95062887787")) {
        std::cout << "Test: personal id validation failed\n";
        return false;
    }

    return true;
}
