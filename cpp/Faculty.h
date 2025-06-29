#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

namespace LibrarySystem {

class Faculty : public User {
public:
    Faculty(int id, const std::string& name);
    std::string getRole() const override;
};

}

#endif
