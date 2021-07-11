#include "person.hpp"

void addStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Student> student)
{
    database.push_back(student);
}

void addWorker(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Worker> worker)
{
    database.push_back(worker);
}

void fulfillDatabase(std::vector<std::shared_ptr<Person> >& database)
{
    if (!database.empty() && database[0] != nullptr)
        srand((unsigned int)time(NULL));

    //draw number of students (1-5) and workers (1-5)
    int studNum = rand() % 5 + 1;
    int workNum = rand() % 5 + 1;

    std::vector<std::string> firstNames = { "Jan", "Karol", "Marcin", "Jola", "Ela", "Ewa" };
    std::vector<std::string> lastNames = { "Kowalski", "Dygant", "Krawczyk", "Mroczek", "Cygan", "Kowal" };
    std::vector<std::string> addresses = { "ul.Cwiartki", "al.Gwiazd", "al.Jerozolimskie", "ul.Bursztynowa", "ul.Wolska", "ul.Woronicza" };
    std::vector<std::string> personalIds = { "49072852861", "78081951876", "83081899446", "72082968248", "04283145461",
        "95062887786", "95033072566", "95012578696", "97111622942", "98112038495" };
    std::vector<std::string> genders = { "M", "F" };
    std::vector<std::string> studentIds = { "111444", "987789", "222333", "777766", "333333", "111222" };
    std::vector<std::string> salary = { "1200$", "1000$", "2100$", "5000$" };

    ssize_t i = 0;
    while (i < studNum) {
        size_t idFirstName = rand() % 6;
        size_t idLastName = rand() % 6;
        size_t idAddress = rand() % 6;
        size_t idPersonalId = rand() % (10 - i);
        size_t idStudentId = rand() % (6 - i);
        size_t idGender{};
        (idFirstName < 3) ? idGender = 0 : idGender = 1;

        addStudent(database, std::make_shared<Student>(firstNames[idFirstName], lastNames[idLastName],
                                 addresses[idAddress], studentIds[idStudentId], personalIds[idPersonalId], genders[idGender]));
        //remove entries from vectors to avoid same pID or sID used several times
        personalIds.erase(personalIds.begin() + idPersonalId);
        studentIds.erase(studentIds.begin() + idStudentId);
        ++i;
    }

    ssize_t j = 0;
    while (j < workNum) {
        size_t idFirstName = rand() % 6;
        size_t idLastName = rand() % 6;
        size_t idAddress = rand() % 6;
        size_t idPersonalId = rand() % (10 - studNum - j);
        size_t idSalary = rand() % 4;
        size_t idGender{};
        (idFirstName < 3) ? idGender = 0 : idGender = 1;

        addWorker(database, std::make_shared<Worker>(firstNames[idFirstName], lastNames[idLastName],
                                addresses[idAddress], salary[idSalary], personalIds[idPersonalId], genders[idGender]));
        personalIds.erase(personalIds.begin() + idPersonalId);
        ++j;
    }
}

void removeStudent(std::vector<std::shared_ptr<Person> >& database, const std::shared_ptr<Person> student)
{
    for (auto it = database.begin(); it < database.end(); ++it) {
        if (*it == student) {
            database.erase(it);
            break;
        }
    }
}

void removeAllStudents(std::vector<std::shared_ptr<Person> >& database)
{
    auto it = database.begin();
    while (it < database.end()) {
        if (((*it)->getSalary()).empty()) {
            removeStudent(database, *it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Person> findByStudentId(std::vector<std::shared_ptr<Person> >& database, const std::string& studentId)
{
    for (auto& rec : database) {
        if (rec->getStudentId() == studentId) {
            return rec;
        }
    }
    throw std::out_of_range("studentID \"" + studentId + "\" has not been found");
}

void printDatabase(std::vector<std::shared_ptr<Person> >& database)
{
    for (auto& rec : database) {
        std::cout << *rec;
    }
}

std::shared_ptr<Person> findByLastName(std::vector<std::shared_ptr<Person> >& database, const std::string& str)
{
    for (auto& rec : database) {
        if (rec->getLastName() == str) {
            return rec;
        }
    }
    throw std::out_of_range("name \"" + str + "\" has not been found");
}

std::shared_ptr<Person> findByPersonalId(std::vector<std::shared_ptr<Person> >& database, const std::string& personalId)
{
    for (auto& rec : database) {
        if (rec->getPersonalId() == personalId) {
            return rec;
        }
    }
    throw std::out_of_range("personalID \"" + personalId + "\" has not been found");
}

struct lessPersonalId {
    inline bool operator()(const std::shared_ptr<Person> lhs, const std::shared_ptr<Person> rhs)
    {
        return (lhs->getPersonalId() < rhs->getPersonalId());
    }
};
void sortByPersonalID(std::vector<std::shared_ptr<Person> >& database)
{
    if (database.empty()) {
        std::cout << "Database is empty!\n";
    } else {
        std::sort(database.begin(), database.end(), lessPersonalId());
    }
}

struct lessLastName {
    inline bool operator()(const std::shared_ptr<Person> lhs, const std::shared_ptr<Person> rhs)
    {
        return (lhs->getLastName() < rhs->getLastName());
    }
};
void sortByLastName(std::vector<std::shared_ptr<Person> >& database)
{
    if (database.empty()) {
        std::cout << "Database is empty!\n";
    } else {
        std::sort(database.begin(), database.end(), lessLastName());
    }
}

struct lessSalary {
    inline bool operator()(const std::shared_ptr<Person> lhs, const std::shared_ptr<Person> rhs)
    {
        return (std::stoi(lhs->getSalary()) < std::stoi(rhs->getSalary()));
    }
};
void sortBySalary(std::vector<std::shared_ptr<Person> >& database)
{
    if (database.empty()) {
        std::cout << "Database is empty!\n";
    } else {
        std::sort(database.begin(), database.end(), lessSalary());
    }
}

void changeSalary(std::shared_ptr<Person>& person, std::string salary)
{
    try {
        person->setSalary(salary);

    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

ssize_t writeToFile(std::vector<std::shared_ptr<Person> >& database, const std::string fileName)
{
    std::ofstream fileWrite(fileName);

    if (fileWrite.fail()) {
        return -1;
    }

    for (const auto& rec : database) {
        fileWrite << *rec;
    }
    fileWrite.close();

    return 0;
}

ssize_t readFromFile(std::vector<std::shared_ptr<Person> >& databaseFile, const std::string fileName)
{
    std::ifstream fileRead(fileName);

    if (fileRead.fail()) {
        return -1;
    }

    std::string temp_all{};

    //read from file to temporary string var
    while (1) {
        std::string temp{};
        fileRead >> temp;
        if (fileRead.eof())
            break;
        temp_all += temp;
    }
    fileRead.close();

    std::vector<std::string> fields_stud = { "Name:", "Surname:", "Address:", "StudIden:", "Personal-ID:", "Gender:" };
    std::vector<std::string> fields_work = { "Name:", "Surname:", "Address:", "Earnings:", "Personal-ID:", "Gender:" };

    //count all records in the file
    size_t count_stud{};
    size_t count_work{};
    for (size_t i = 0; (i = temp_all.find((fields_stud[3]), i)) != std::string::npos; i++) {
        count_stud++;
    }

    for (size_t i = 0; (i = temp_all.find((fields_work[3]), i)) != std::string::npos; i++) {
        count_work++;
    }

    size_t i{};
    while (i < count_stud) {
        //parse the content of temporary string read from the file
        addStudent(databaseFile, std::make_shared<Student>(
                                     temp_all.substr(temp_all.find(fields_stud[0]) + fields_stud[0].size(),
                                         temp_all.find(fields_stud[1]) - temp_all.find(fields_stud[0]) - fields_stud[0].size()),
                                     temp_all.substr(temp_all.find(fields_stud[1]) + fields_stud[1].size(),
                                         temp_all.find(fields_stud[2]) - temp_all.find(fields_stud[1]) - fields_stud[1].size()),
                                     temp_all.substr(temp_all.find(fields_stud[2]) + fields_stud[2].size(),
                                         temp_all.find(fields_stud[3]) - temp_all.find(fields_stud[2]) - fields_stud[2].size()),
                                     temp_all.substr(temp_all.find(fields_stud[3]) + fields_stud[3].size(),
                                         temp_all.find(fields_stud[4]) - temp_all.find(fields_stud[3]) - fields_stud[3].size()),
                                     temp_all.substr(temp_all.find(fields_stud[4]) + fields_stud[4].size(),
                                         temp_all.find(fields_stud[5]) - temp_all.find(fields_stud[4]) - fields_stud[4].size()),
                                     temp_all.substr(temp_all.find(fields_stud[5]) + fields_stud[5].size(),
                                         temp_all.find(fields_stud[0], fields_stud[0].size()) - temp_all.find(fields_stud[5]) - fields_stud[5].size())));
        //erase read data
        temp_all.erase(temp_all.begin(), temp_all.begin() + (temp_all.find(fields_stud[5]) - temp_all.find(fields_stud[0]) + fields_stud[5].size() + 1));
        ++i;
    }

    while (i < (count_stud + count_work)) {
        //parse the content of temporary string read from the file
        addWorker(databaseFile, std::make_shared<Worker>(
                                    temp_all.substr(temp_all.find(fields_work[0]) + fields_work[0].size(),
                                        temp_all.find(fields_work[1]) - temp_all.find(fields_work[0]) - fields_work[0].size()),
                                    temp_all.substr(temp_all.find(fields_work[1]) + fields_work[1].size(),
                                        temp_all.find(fields_work[2]) - temp_all.find(fields_work[1]) - fields_work[1].size()),
                                    temp_all.substr(temp_all.find(fields_work[2]) + fields_work[2].size(),
                                        temp_all.find(fields_work[3]) - temp_all.find(fields_work[2]) - fields_work[2].size()),
                                    temp_all.substr(temp_all.find(fields_work[3]) + fields_work[3].size(),
                                        temp_all.find(fields_work[4]) - temp_all.find(fields_work[3]) - fields_work[3].size()),
                                    temp_all.substr(temp_all.find(fields_work[4]) + fields_work[4].size(),
                                        temp_all.find(fields_work[5]) - temp_all.find(fields_work[4]) - fields_work[4].size()),
                                    temp_all.substr(temp_all.find(fields_work[5]) + fields_work[5].size(),
                                        temp_all.find(fields_work[0], fields_work[0].size()) - temp_all.find(fields_work[5]) - fields_work[5].size())));
        //erase read data
        temp_all.erase(temp_all.begin(), temp_all.begin() + (temp_all.find(fields_work[5]) - temp_all.find(fields_work[0]) + fields_work[5].size() + 1));
        ++i;
    }

    return 0;
}

bool validatePersonalId(const std::string& personalId)
{
    if (personalId.size() < 11) {
        return false;
    }

    std::vector<size_t> numbers{};
    for (auto& el : personalId) {
        numbers.push_back(el - '0');
    }

    size_t i{};
    size_t sum{};
    for (auto& el : numbers) {
        switch (i) {
        case 0:
        case 4:
        case 8:
            sum += el;
            break;
        case 1:
        case 5:
        case 9:
            sum += el * 3;
            break;
        case 2:
        case 6:
            sum += el * 7;
            break;
        case 3:
        case 7:
            sum += el * 9;
            break;
        default:
            break;
        }
        ++i;
    }

    size_t checksum{}, mod{};
    mod = sum % 10;
    if (mod)
        checksum = 10 - mod;
    else
        checksum = 0;

    return (numbers[10] == checksum);
}

bool compareDatabases(std::vector<std::shared_ptr<Person> >& lhs, std::vector<std::shared_ptr<Person> >& rhs)
{
    size_t sizeLhs = lhs.size();
    if (sizeLhs != rhs.size()) {
        return false;
    }

    size_t i = 0;
    while (i < sizeLhs) {
        if (!(*(lhs[i]) == *(rhs[i]))) {
            return false;
        }
        ++i;
    }
    return true;
}
