#include <iostream>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: return <studentId> <title>\n";
        return 1;
    }

    int studentId = std::stoi(argv[1]);
    std::string title = argv[2];

    Library lib;
    lib.loadBooksFromFile("books.txt");
    lib.loadIssuedBooksFromFile("issued.txt");

    if (lib.returnBook(studentId, title)) {
    lib.saveIssuedBooksToFile("issued.txt");
    cout << "Book returned successfully.\n";
    } else {
        cout << "Book not found in issued list.\n";
    }

    return 0;
}
