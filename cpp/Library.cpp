#include "Library.h"
#include <algorithm>
#include <fstream>
#include <map>

using namespace LibrarySystem;

Library::Library() {

    registerStudent(1, "Alice");
    registerFaculty(1001, "Prof. John");


    addBook("C++ Primer", "Lippman");
    addBook("Clean Code", "Robert C. Martin");
}

void Library::addBook(const std::string& title, const std::string& author) {
    books.emplace_back(title, author);
}

void Library::registerStudent(int id, const std::string& name) {
    students.emplace(id, Student(id, name));

}

bool Library::issueBook(int studentId, const std::string& title) {
    if (students.find(studentId) == students.end()) {
        return false; // ❌ student not registered
    }
    // ✅ Check if book exists
    bool bookExists = false;
    for (const Book& book : books) {
        if (book.getTitle() == title) {
            bookExists = true;
            break;
        }
    }

    if (!bookExists) return false;

    // ✅ Check if already issued to this student
    const auto& issuedList = issuedBooks[studentId];
    for (const auto& info : issuedList) {
        if (info.title == title) {
            return false; // already issued
        }
    }


    // ✅ Issue the book
    issuedBooks[studentId].push_back({ title, "2023-10-01", "2023-10-15" }); // Example dates
    return true;
}


bool Library::returnBook(int studentId, const std::string& title) {
    if (students.find(studentId) == students.end()) {
    return false; // Not registered
}

    auto it = issuedBooks.find(studentId);
    if (it == issuedBooks.end()) {
        return false; // No books issued to this student
    }

    auto& books = it->second;
    for (auto bookIt = books.begin(); bookIt != books.end(); ++bookIt) {
        if (bookIt->title == title) {
            books.erase(bookIt); // remove the book
            return true;
        }
    }

    return false; // Book not found for this student
}


const std::vector<Book>& Library::getBooks() const {
    return books;
}

std::vector<Student> Library::getStudents() const {
    std::vector<Student> list;
    for (const auto& pair : students) {
        list.push_back(pair.second);
    }
    return list;
}


void Library::registerFaculty(int id, const std::string& name) {
    faculty.emplace(id, Faculty(id, name));

}

std::string Library::authenticateUser(int id, const std::string& role) {
    if (role == "student") {
        std::map<int, Student>::const_iterator sit = students.find(id);
        if (sit != students.end()) {
            return sit->second.getName();
        }

    } else if (role == "faculty") {
        std::map<int, Faculty>::const_iterator fit = faculty.find(id);
        if (fit != faculty.end()) {
            return fit->second.getName();
        }
    }
    return ""; // authentication failed
}

 


bool Library::deleteBook(const std::string& title) {
    auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b) {
        return b.getTitle() == title;
    });

    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

bool Library::saveBooksToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;

    for (const auto& b : books) {
        out << b.getTitle() << "," << b.getAuthor() << "\n";
    }

    return true;
}

bool Library::loadBooksFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    books.clear();
    std::string line;

    while (getline(in, line)) {
        size_t comma = line.find(',');
        if (comma != std::string::npos) {
            std::string title = line.substr(0, comma);
            std::string author = line.substr(comma + 1);
            books.emplace_back(title, author);
        }
    }

    return true;
}

#include <fstream>

bool Library::loadIssuedBooksFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    issuedBooks.clear();
    std::string line;

    while (getline(in, line)) {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);
        size_t third = line.find(',', second + 1);

        if (first != std::string::npos && second != std::string::npos && third != std::string::npos) {
            int id = std::stoi(line.substr(0, first));
            std::string title = line.substr(first + 1, second - first - 1);
            std::string issuedAt = line.substr(second + 1, third - second - 1);
            std::string dueDate = line.substr(third + 1);

            issuedBooks[id].push_back({ title, issuedAt, dueDate });
        }
    }

    return true;
}


bool Library::saveIssuedBooksToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;

    for (const auto& pair : issuedBooks) {
        for (const auto& info : pair.second) {
            out << pair.first << "," << info.title << "," << info.issuedAt << "," << info.dueDate << "\n";
        }
    }

    return true;
}

bool Library::hasBookIssued(int studentId, const std::string& title) const {
    auto it = issuedBooks.find(studentId);
    if (it == issuedBooks.end()) return false;

    // ✅ Manual loop with title comparison
    for (const auto& info : it->second) {
        if (info.title == title) {
            return true;
        }
    }

    return false;
}



bool Library::bookExists(const std::string& title) const {
    for (const auto& b : books) {
        if (b.getTitle() == title) return true;
    }
    return false;
}

void Library::addIssuedBook(int studentId, const IssuedBookInfo& info) {
    issuedBooks[studentId].push_back(info);
}

bool Library::appendBookToFile(const std::string& filename, const Book& b) {
    std::ofstream out(filename, std::ios::app); // open in append mode
    if (!out) return false;
    out << b.getTitle() << "," << b.getAuthor() << "\n";
    return true;
}

