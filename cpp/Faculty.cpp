#include "Faculty.h"

namespace LibrarySystem {

Faculty::Faculty(int id, const std::string& name) : User(id, name) {}

std::string Faculty::getRole() const {
    return "faculty";
}

}
