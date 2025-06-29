#ifndef BOOK_H
#define BOOK_H

#include <string>

namespace LibrarySystem {

class Book {
private:
    std::string title;
    std::string author;

public:
    Book(const std::string& title, const std::string& author);
    std::string getTitle() const;
    std::string getAuthor() const;
};

} // namespace LibrarySystem

#endif
