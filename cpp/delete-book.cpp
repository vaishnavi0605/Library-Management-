#include <iostream>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: delete-book <title>\n";
        return 1;
    }

    string title = argv[1];

    Library lib;
    lib.loadBooksFromFile("books.txt");

    if (lib.deleteBook(title)) {
        lib.saveBooksToFile("books.txt");
        cout << "Book deleted: " << title << "\n";
    } else {
        cout << "Book not found.\n";
    }

    return 0;
}
