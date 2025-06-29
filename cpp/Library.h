#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <map>
#include <string>
#include "Book.h"
#include "Student.h"
using namespace std;
#include "Faculty.h"
#include "User.h"
namespace LibrarySystem {
    struct IssuedBookInfo {
        std::string title;
        std::string issuedAt;
        std::string dueDate;
        };
class Library {
private:
    std::vector<Book> books;
    // std::vector<Student> students;
    std::map<int, Student> students;
    
    std::map<int, std::vector<IssuedBookInfo>> issuedBooks;

    std::map<int, Faculty> faculty;

public:
    Library();

    void addBook(const std::string& title, const std::string& author);
    void registerStudent(int id, const std::string& name);
    bool issueBook(int studentId, const std::string& title);
    bool returnBook(int studentId, const std::string& title);
    void registerFaculty(int id, const std::string& name);
    // bool authenticateUser(int id, const std::string& role, std::string& nameOut);
    string authenticateUser(int id, const std::string& role);

    bool deleteBook(const std::string& title);
    bool saveBooksToFile(const std::string& filename) const;
    bool loadBooksFromFile(const std::string& filename);
    bool loadIssuedBooksFromFile(const std::string& filename);
    bool saveIssuedBooksToFile(const std::string& filename) const;

    bool hasBookIssued(int studentId, const std::string& title) const;
    bool bookExists(const std::string& title) const;
    void addIssuedBook(int studentId, const IssuedBookInfo& info);
    bool appendBookToFile(const std::string& filename, const Book& b);
    const std::vector<Book>& getBooks() const;
    vector<Student> getStudents() const;
};

} // namespace LibrarySystem

#endif


