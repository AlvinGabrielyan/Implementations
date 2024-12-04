#include <iostream>
using namespace std;

struct Node {
    int key;
    string value;
    Node* next;
};

class HashMap {
private:
    static const int tableSize = 10; 
    Node* table[tableSize]; 

    int hashFunction(int key) const {
        return (key * 37) % tableSize;
    }

public:
    HashMap() {
        for (int i = 0; i < tableSize; ++i) {
            table[i] = nullptr;
        }
    }

    void insert(int key, const string& value) {
        int index = hashFunction(key);

        if (table[index] == nullptr) {
            table[index] = new Node();
            table[index]->key = key;
            table[index]->value = value;
            table[index]->next = nullptr;
            return;
        }

        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = table[index];
        table[index] = newNode;
    }

    bool search(int key, string& value) const {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false; 
    }

    void remove(int key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* previous = nullptr;

        while (current) {
            if (current->key == key) {
                if (previous) {
                    previous->next = current->next; 
                } else {
                    table[index] = current->next; 
                }
                delete current;
                cout << "Key " << key << " removed successfully.\n";
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Key " << key << " not found.\n";
    }

    void display() const {
        for (int i = 0; i < tableSize; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current) {
                cout << "{" << current->key << ": " << current->value.c_str() << "} ";
                current = current->next;
            }
            cout << endl;
        }
    }

    void addEntries() {
        int key;
        string value;
        char choice;
        do {
            cout << "Enter the key (integer): ";
            cin >> key;
            cout << "Enter the value (string): ";
            cin >> value;
            insert(key, value);
            cout << "Should we add a  pair? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }

    ~HashMap() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp; 
            }
        }
    }
};

int main() {
    HashMap map;
    int key;
    string value;
    char choice;

    cout << "Enter key-value pairs:\n";
    map.addEntries();

    do {
        cout << "\nChoose an operation:\n";
        cout << "1. Print HashMap\n";
        cout << "2. Search for a key\n";
        cout << "3. Remove a key\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "\nThe contents of the hash table:\n";
                map.display();
                break;
            case '2':
                cout << "Mutqagreq key search-i hamar: ";
                cin >> key;
                if (map.search(key, value)) {
                    cout << "For "<< key << "key is " << value <<" value"<<endl;
                } else {
                    cout << key << "key is not found.\n";
                }
                break;

            case '3':
                cout << "Enter a key for remove: ";
                cin >> key;
                map.remove(key);
                break;

            case '4':
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != '4');

    return 0;
}
