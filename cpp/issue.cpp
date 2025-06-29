#include <iostream>
#include <ctime>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;
using LibrarySystem::IssuedBookInfo;

std::string getCurrentDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return buf;
}

std::string getDueDate() {
    time_t t = time(nullptr) + 14 * 24 * 60 * 60; // 14 days
    tm* due = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", due);
    return buf;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: issue <studentId> <title>\n";
        return 1;
    }

    int studentId = stoi(argv[1]);
    std::string title = argv[2];

    Library lib;
    lib.loadBooksFromFile("books.txt");
    lib.loadIssuedBooksFromFile("issued.txt");

    if (lib.hasBookIssued(studentId, title)) {
        cout << "Book already issued to student " << studentId << "\n";
        return 0;
    }

    if (!lib.bookExists(title)) {
        cout << "Book not found in inventory.\n";
        return 0;
    }

    IssuedBookInfo info = { title, getCurrentDate(), getDueDate() };

    lib.addIssuedBook(studentId, info);
    lib.saveIssuedBooksToFile("issued.txt");

    cout << "Book issued successfully. Due: " << info.dueDate << "\n";
    return 0;
}
