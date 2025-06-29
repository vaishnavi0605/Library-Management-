#ifndef USER_H
#define USER_H

#include <string>

namespace LibrarySystem {

class User {
protected:
    int id;
    std::string name;

public:
    User(int id, const std::string& name);
    virtual std::string getRole() const = 0;
    int getId() const;
    std::string getName() const;
};

} // namespace LibrarySystem

#endif
