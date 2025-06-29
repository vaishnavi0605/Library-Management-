#include <iostream>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: add-book <title> <author>\n";
        return 1;
    }

    std::string title = argv[1];
    std::string author = argv[2];

    Library lib;
    lib.loadBooksFromFile("books.txt");  // optional, for in-memory state

    Book b(title, author);
    lib.addBook(title, author);          // optional, in-memory addition
    lib.appendBookToFile("books.txt", b);  // ✅ append only

    cout << "Book added successfully: " << title << " by " << author << "\n";
    return 0;
}
