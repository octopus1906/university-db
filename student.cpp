#include "student.hpp"

void addStudent(std::vector<Student>& database, const Student& student)
{
    database.push_back(student);
}

void removeStudent(std::vector<Student>& database, const Student& student)
{
    for (auto it = database.begin(); it < database.end(); ++it) {
        if (*it == student) {
            database.erase(it);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Student& student)
{
    os << "Name: " << student.getFirstName() << "\n";
    os << "Surname: " << student.getLastName() << "\n";
    os << "Address: " << student.getAddress() << "\n";
    os << "Student ID:: " << student.getStudentId() << "\n";
    os << "Personal ID: " << student.getPersonalId() << "\n";
    os << "Gender: " << student.getGender() << "\n";
    os << "\n";
    return os;
}

void printDatabase(std::vector<Student>& database)
{
    for (auto& rec : database) {
        std::cout << rec;
    }
}

Student& findByLastName(std::vector<Student>& database, const std::string& str)
{
    for (auto& rec : database) {
        if (rec.getLastName() == str) {
            return rec;
        }
    }
    throw std::out_of_range("name \"" + str + "\" has not been found");
}

Student& findByPersonalId(std::vector<Student>& database, const std::string& personalId)
{
    for (auto& rec : database) {
        if (rec.getPersonalId() == personalId) {
            return rec;
        }
    }
    throw std::out_of_range("personalID \"" + personalId + "\" has not been found");
}

Student& findByStudentId(std::vector<Student>& database, const std::string& studentId)
{
    for (auto& rec : database) {
        if (rec.getStudentId() == studentId) {
            return rec;
        }
    }
    throw std::out_of_range("studentID \"" + studentId + "\" has not been found");
}

struct lessPersonalId {
    inline bool operator()(const Student& stud1, const Student& stud2)
    {
        return (stud1.getPersonalId() < stud2.getPersonalId());
    }
};
void sortByPersonalID(std::vector<Student>& database)
{
    if (database.empty()) {
        std::cout << "Database is empty!\n";
    } else {
        std::sort(database.begin(), database.end(), lessPersonalId());
    }
}

struct lessLastName {
    inline bool operator()(const Student& stud1, const Student& stud2)
    {
        return (stud1.getLastName() < stud2.getLastName());
    }
};
void sortByLastName(std::vector<Student>& database)
{
    if (database.empty()) {
        std::cout << "Database is empty!\n";
    } else {
        std::sort(database.begin(), database.end(), lessLastName());
    }
}

ssize_t writeToFile(std::vector<Student>& database, const std::string fileName)
{
    std::ofstream fileWrite(fileName);

    if (fileWrite.fail()) {
        return -1;
    }

    for (const auto& el : database) {
        fileWrite << "Name: " << el.getFirstName() << " "
                  << "Surname: " << el.getLastName() << " "
                  << "Address: " << el.getAddress() << " "
                  << "Student-ID: " << el.getStudentId() << " "
                  << "Personal-ID: " << el.getPersonalId() << " "
                  << "Gender: " << el.getGender() << "\n";
    }
    fileWrite.close();

    return 0;
}

ssize_t readFromFile(std::vector<Student>& databaseFile, const std::string fileName)
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

    std::vector<std::string> fields = { "Name:", "Surname:", "Address:", "Student-ID:", "Personal-ID:", "Gender:" };

    //count all records in the file
    size_t count{};
    for (size_t i = 0; (i = temp_all.find((fields[0]), i)) != std::string::npos; i++) {
        count++;
    }

    size_t i{};
    while (i < count) {
        //parse the content of temporary string read from the file
        addStudent(databaseFile, Student(
                                     temp_all.substr(temp_all.find(fields[0]) + fields[0].size(), temp_all.find(fields[1]) - temp_all.find(fields[0]) - fields[0].size()), temp_all.substr(temp_all.find(fields[1]) + fields[1].size(), temp_all.find(fields[2]) - temp_all.find(fields[1]) - fields[1].size()), temp_all.substr(temp_all.find(fields[2]) + fields[2].size(), temp_all.find(fields[3]) - temp_all.find(fields[2]) - fields[2].size()), temp_all.substr(temp_all.find(fields[3]) + fields[3].size(), temp_all.find(fields[4]) - temp_all.find(fields[3]) - fields[3].size()), temp_all.substr(temp_all.find(fields[4]) + fields[4].size(), temp_all.find(fields[5]) - temp_all.find(fields[4]) - fields[4].size()), temp_all.substr(temp_all.find(fields[5]) + fields[5].size(), temp_all.find(fields[0], fields[0].size()) - temp_all.find(fields[5]) - fields[5].size())));
        //erase read data
        temp_all.erase(temp_all.begin(), temp_all.begin() + (temp_all.find(fields[5]) - temp_all.find(fields[0]) + fields[5].size() + 1));
        ++i;
    }
    return 0;
}

bool validatePersonalId(const std::string& personalId)
{
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

    if (numbers[10] == checksum)
        return true;
    else
        return false;
}
