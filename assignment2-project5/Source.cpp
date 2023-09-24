#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {

#ifdef PRE_RELEASE
    std::cout << "Running pre-release version." << std::endl;
#else
    std::cout << "Running standard version." << std::endl;
#endif
    std::vector<STUDENT_DATA> students;
    std::ifstream file("StudentData.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open the StudentData.txt file." << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        STUDENT_DATA student;

        size_t lastSpace = line.find_last_of(" \t"); // Search for the last space or tab
        if (lastSpace != std::string::npos) {
            student.firstName = line.substr(lastSpace + 1);
            student.lastName = line.substr(0, lastSpace);
        }
        else {
            // No space found, use the whole line as the last name
            student.lastName = line;
        }

        students.push_back(student);
    }

    // Printing the students for verification
    for (const auto& student : students) {
        std::cout << student.firstName << " " << student.lastName << std::endl;
    }
    return 1;
}
