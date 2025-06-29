#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

namespace LibrarySystem {

class Student : public User {
public:
    Student(int id, const std::string& name);
    std::string getRole() const override;
};

}

#endif
