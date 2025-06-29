#include <iostream>
#include <string>
#include "Library.h"

using namespace std;
using namespace LibrarySystem;

int main(int argc, char* argv[]) {
    // CGI Header for JSON
    cout << "Content-Type: application/json\n\n";

    if (argc < 3) {
        // Return error JSON if arguments are missing
        cout << "{ \"success\": false, \"error\": \"Missing parameters\" }";
        return 1;
    }

    int id = stoi(argv[1]);
    string role = argv[2];
    string name;

    Library lib;
    name = lib.authenticateUser(id, role);

    if (!name.empty()) {
        // ✅ Valid login
        cout << "{ \"success\": true, \"name\": \"" << name << "\", \"role\": \"" << role << "\" }";
    } else {
        // ❌ Invalid login
        cout << "{ \"success\": false, \"error\": \"Invalid ID or role\" }";
    }

    return 0;
}
