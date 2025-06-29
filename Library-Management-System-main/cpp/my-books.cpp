#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: my-books <studentId>\n";
        return 1;
    }

    int studentId = stoi(argv[1]);
    ifstream in("issued.txt");
    if (!in) {
        cout << "No issued books found.\n";
        return 0;
    }

    string line;
    bool found = false;

    cout << "Books issued to you:\n";

    while (getline(in, line)) {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);
        size_t third = line.find(',', second + 1);

        if (first != string::npos && second != string::npos && third != string::npos) {
            int id = stoi(line.substr(0, first));
            string title = line.substr(first + 1, second - first - 1);
            string issuedAt = line.substr(second + 1, third - second - 1);
            string dueDate = line.substr(third + 1);

            if (id == studentId) {
                cout << "- " << title << " (Issued: " << issuedAt << ", Due: " << dueDate << ")\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No books issued.\n";
    }

    return 0;
}
