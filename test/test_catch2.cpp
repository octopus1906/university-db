#include "catch_amalgamated.hpp"

#include "../Person.hpp"
#include "../Student.hpp"
#include "../Worker.hpp"
#include "../utils.hpp"

SCENARIO("testing fulfillDatabase()", "[data]")
{
    GIVEN("provide database vector")
    {
        std::vector<std::shared_ptr<Person>> database{};
        WHEN("fulfill database")
        {
            fulfillDatabase(database);
            THEN("check if database is not empty")
            {
                REQUIRE_FALSE(database.empty());
            }
        }
    }
}

SCENARIO("verify if comparing works", "[compare]")
{
    std::vector<std::shared_ptr<Person>> testDatabase{};
    std::vector<std::shared_ptr<Person>> testDatabaseRef{};

    auto workHalina = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studJola = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarol = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");
    auto workHalinaRef = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studJolaRef = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarolRef = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");

    GIVEN("add people to database")
    {
        addStudent(testDatabase, studJola);
        addStudent(testDatabase, studKarol);
        addWorker(testDatabase, workHalina);
        testDatabaseRef.push_back(studJolaRef);
        testDatabaseRef.push_back(studKarolRef);
        testDatabaseRef.push_back(workHalinaRef);

        WHEN("compareDatabases() validation")
        {
            THEN("check if compareDatabases() works")
            {
                REQUIRE(compareDatabases(testDatabase, testDatabaseRef) == (*testDatabase[0] == *testDatabaseRef[0]
                                                                               && *testDatabase[1] == *testDatabaseRef[1]
                                                                               && *testDatabase[2] == *testDatabaseRef[2]));
            }
        }
    }
}

SCENARIO("verify if file handling works", "[file]")
{
    std::vector<std::shared_ptr<Person>> testDatabase{};
    std::vector<std::shared_ptr<Person>> testDatabaseRef{};

    auto workHalina = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studJola = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "49072852861", "F");
    auto studKarol = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");

    GIVEN("add people to database")
    {
        addStudent(testDatabase, studJola);
        addStudent(testDatabase, studKarol);
        addWorker(testDatabase, workHalina);

        WHEN("execute write and read functions")
        {
            writeToFile(testDatabase, "testBase.txt");
            readFromFile(testDatabaseRef, "testBase.txt");

            THEN("check if databases are equal after file operation")
            {
                REQUIRE(compareDatabases(testDatabase, testDatabaseRef));
            }
        }
    }
}

SCENARIO("verify searching functions", "[search]")
{
    std::vector<std::shared_ptr<Person>> testDatabaseRef{};

    auto studMarcinRef = std::make_shared<Student>("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto workZygmuntRef = std::make_shared<Worker>("Zygmunt", "Kasinski", "ul.Okopowa", "1600$", "59062887786", "M");

    GIVEN("add people to database")
    {
        testDatabaseRef.push_back(studMarcinRef);
        testDatabaseRef.push_back(workZygmuntRef);

        WHEN("findByPersonalId() validation")
        {
            THEN("check if person found by id is fine")
            {
                REQUIRE(findByPersonalId(testDatabaseRef, "83081899446") == testDatabaseRef[0]);
            }
        }

        WHEN("findByLastName() validation")
        {
            THEN("check if person found by lastName is fine")
            {
                REQUIRE(findByLastName(testDatabaseRef, "Kasinski") == testDatabaseRef[1]);
            }
        }

        WHEN("findByStudentId() validation")
        {
            THEN("check if student found by id is fine")
            {
                REQUIRE(findByStudentId(testDatabaseRef, "222333") == testDatabaseRef[0]);
            }
        }
    }
}

SCENARIO("verify sorting functions", "[sort]")
{
    std::vector<std::shared_ptr<Person>> testDatabase{};

    auto studJola = std::make_shared<Student>("Jola", "Cygan", "ul.Bursztynowa", "987789", "83081899446", "F");
    auto studEla = std::make_shared<Student>("Ela", "Kowal", "al.Gwiazd", "111444", "04283145461", "F");

    auto workHalina = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto workZbigniew = std::make_shared<Worker>("Zbigniew", "Poleski", "ul.Podlaska", "2300$", "49072852861", "M");

    GIVEN("add people to database")
    {
        testDatabase.push_back(studJola);
        testDatabase.push_back(studEla);
        testDatabase.push_back(workHalina);
        testDatabase.push_back(workZbigniew);

        WHEN("sortByPersonalID() validation")
        {
            sortByPersonalID(testDatabase);

            THEN("check if order is correct after sortByPersonalID()")
            {
                REQUIRE(testDatabase[0] == studEla);
                REQUIRE(testDatabase[1] == workZbigniew);
                REQUIRE(testDatabase[2] == workHalina);
                REQUIRE(testDatabase[3] == studJola);
            }
        }

        WHEN("sortByLastName() validation")
        {
            sortByLastName(testDatabase);

            THEN("check if order is correct after sortByLastName()")
            {
                REQUIRE(testDatabase[0] == studJola);
                REQUIRE(testDatabase[1] == studEla);
                REQUIRE(testDatabase[2] == workZbigniew);
                REQUIRE(testDatabase[3] == workHalina);
            }
        }

        WHEN("sortBySalary() validation")
        {
            removeAllStudents(testDatabase);
            sortBySalary(testDatabase);

            THEN("check if order is correct after sortBySalary()")
            {
                REQUIRE(testDatabase[0] == workHalina);
                REQUIRE(testDatabase[1] == workZbigniew);
            }
        }
    }
}

SCENARIO("verify various database utils", "[utils]")
{
    std::vector<std::shared_ptr<Person>> testDatabase{};
    std::vector<std::shared_ptr<Person>> testDatabaseRef{};

    auto studMarcin = std::make_shared<Student>("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto workZygmunt = std::make_shared<Worker>("Zygmunt", "Kasinski", "ul.Okopowa", "1600$", "59062887786", "M");
    auto workHalina = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studKarol = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");

    auto studMarcinRef = std::make_shared<Student>("Marcin", "Mroczek", "ul.Woronicza", "222333", "83081899446", "M");
    auto workZygmuntRef = std::make_shared<Worker>("Zygmunt", "Kasinski", "ul.Okopowa", "1600$", "59062887786", "M");
    auto workHalinaRef = std::make_shared<Worker>("Halina", "Rodowicz", "ul.Lubelska", "1200$", "52010278456", "F");
    auto studKarolRef = std::make_shared<Student>("Karol", "Krawczyk", "ul.Wolska", "333333", "78081951876", "M");

    GIVEN("provide database vector")
    {
        addStudent(testDatabase, studMarcin);
        addWorker(testDatabase, workZygmunt);
        testDatabaseRef.push_back(studMarcinRef);
        testDatabaseRef.push_back(workZygmuntRef);

        WHEN("add student and worker")
        {
            addStudent(testDatabase, studKarol);
            addWorker(testDatabase, workHalina);
            testDatabaseRef.push_back(studKarolRef);
            testDatabaseRef.push_back(workHalinaRef);

            THEN("check if database is extended")
            {
                REQUIRE(compareDatabases(testDatabase, testDatabaseRef));
            }
        }

        WHEN("remove student")
        {
            removeStudent(testDatabase, studMarcin);
            testDatabaseRef.erase((testDatabaseRef.begin()));

            THEN("check if student is removed")
            {
                REQUIRE(compareDatabases(testDatabase, testDatabaseRef));
            }
        }

        WHEN("change salary")
        {
            std::shared_ptr<Person> ptrSucc = findByPersonalId(testDatabase, "59062887786");
            changeSalary(ptrSucc, "1500$");
            testDatabaseRef[1]->setSalary("1500$");

            THEN("check if salary is changed")
            {
                REQUIRE(compareDatabases(testDatabase, testDatabaseRef));
            }
        }
    }
}

SCENARIO("verify personal id validation", "[pIdValid]")
{
    GIVEN("define personal ids")
    {
        std::string correctId = "95062887786";
        std::string wrongId = "95062887787";

        WHEN("validatePersonalId() validation")
        {
            THEN("check if validatePersonalId() works")
            {
                REQUIRE(validatePersonalId(correctId));
                REQUIRE_FALSE(validatePersonalId(wrongId));
            }
        }
    }
}
