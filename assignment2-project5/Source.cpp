#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

int main() {
    
    std::vector<STUDENT_DATA> students; // Ensure this is at the top of main.

#ifdef PRE_RELEASE
    std::cout << "Running pre-release version." << std::endl;
    std::ifstream file("StudentData_Emails.txt");
#else
    std::cout << "Running standard version." << std::endl;
    std::ifstream file("StudentData.txt");
#endif

    if (!file.is_open()) {
#ifdef PRE_RELEASE
        std::cerr << "Failed to open the StudentData_Emails.txt file." << std::endl;
#else
        std::cerr << "Failed to open the StudentData.txt file." << std::endl;
#endif
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        STUDENT_DATA student;
        std::stringstream ss(line);
        std::string token;

#ifdef PRE_RELEASE
        std::getline(ss, token, ',');
        student.lastName = token;

        std::getline(ss, token, ',');
        student.firstName = token;

        std::getline(ss, token, ',');
        student.email = token;
#else
        size_t lastSpace = line.find_last_of(" \t");
        if (lastSpace != std::string::npos) {
            student.firstName = line.substr(lastSpace + 1);
            student.lastName = line.substr(0, lastSpace);
        }
        else {
            student.lastName = line;
        }
#endif

        students.push_back(student);
    }


    // Printing the students for verification
    for (const auto& student : students) {
        std::cout << student.firstName << " " << student.lastName;
#ifdef PRE_RELEASE
        std::cout << " " << student.email;
#endif
        std::cout << std::endl;
    }
    return 1;
}
