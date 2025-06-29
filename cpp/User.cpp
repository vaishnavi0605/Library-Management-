#include "User.h"

namespace LibrarySystem {

User::User(int id, const std::string& name) : id(id), name(name) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }

}
