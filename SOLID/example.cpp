#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Representation Layer- data pahelu u artacelu hamar
class BookRepresentation {
public:
    static void displayBooks(const vector<string>& books) {
        if (books.empty()) {
            cout << "No books available." << endl;
        } else {
            cout << "Books in the library (Formatted View):" << endl;
            for (size_t i = 0; i < books.size(); ++i) {
                cout << i + 1 << ". " << books[i] << endl;
            }
        }
    }
};

// Service Layer- himnakan funkcionaln a apahovum
class LibraryService {
private:
    vector<string> books; 

public:
 
    void addBook(const string& title) {
        if (find(books.begin(), books.end(), title) != books.end()) {
            cout << "Error: \" << title << "\" already exists!" << endl;
        } else {
            books.push_back(title);
            cout << "Book \"" << title << "\" added successfully!" << endl;
        }
    }

    vector<string> getBooks() const {
        return books;
    }
};

// Control Layer-data a stanum
class LibraryController {
private:
    LibraryService service;

public:
    LibraryController(LibraryService serviceInstance) : service(serviceInstance) {}

    void run() {
        int choice;
        do {
            cout << "\nLibrary Management System" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. List Books" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cin.ignore(); 
                    cout << "Enter book title: ";
                    string title;
                    getline(cin, title);
                    service.addBook(title);
                    break;
                }
                case 2: {
                    vector<string> books = service.getBooks();
                    BookRepresentation::displayBooks(books);
                    break;
                }
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 0);
    }
};

int main() {
 
    LibraryService service;
    LibraryController controller(service);
    controller.run();

    return 0;
}
