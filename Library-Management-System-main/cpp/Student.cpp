#include "Student.h"

namespace LibrarySystem {

Student::Student(int id, const std::string& name) : User(id, name) {}

std::string Student::getRole() const {
    return "student";
}

}
