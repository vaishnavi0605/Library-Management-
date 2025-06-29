#include <iostream>
#include <string>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;

int main(int argc, char* argv[]) {
    Library lib;
    lib.loadBooksFromFile("books.txt");
    if (argc < 2) {
        cout << "Missing book title\n";
        return 1;
    }

    string query = argv[1];

    const auto& books = lib.getBooks();
    bool found = false;

    for (const auto& book : books) {
        if (book.getTitle().find(query) != string::npos) {
            cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No books found matching \"" << query << "\"\n";
    }

    return 0;
}
