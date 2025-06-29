#include "Book.h"
#include "Library.h"

using namespace LibrarySystem;

int main() {
    Library lib;

    lib.registerStudent(1, "Alice");

    lib.addBook("C++ Programming", "Bjarne Stroustrup");

    return 0;
}
