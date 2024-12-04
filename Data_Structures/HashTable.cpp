#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int key;
    string value;
    Node* next;
    Node(int k, const string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> table; 
    int capacity;   
    int size;            
    int hashFunction(int key) const {
        return key % capacity;
    }

public:
  HashTable(int capacity);
  ~HashTable();
  void insert(int key, const string& value);
  string search(int key) const;
  void remove(int key);
  void print() const;
  int getSize() const;
  bool isEmpty() const;
};

HashTable::HashTable(int capacity) : capacity(capacity), size(0) {
    table.resize(capacity, nullptr); 
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void HashTable::insert(int key, const string& value) {
    int index = hashFunction(key);
    Node* newNode = new Node(key, value);
    Node* current = table[index];

    if (current == nullptr) {
        table[index] = newNode;
    } else {
             while (current != nullptr) 
      {
        if (current->key == key) {
          current->value = value;
          delete newNode;
          return;
        }
        if (current->next == nullptr) break;

        current = current->next;
            }
         current->next = newNode;
    }
    ++size;  
}
string HashTable::search(int key) const {
    int index = hashFunction(key);
    Node* current = table[index];

     while (current != nullptr) {
        if (current->key == key) {
            return current->value; 
    }
        current = current->next;
    }
    return "The key you are looking for:";
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    Node* current = table[index];
    Node* prev = nullptr;

     while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;    
            }
            delete current;
            --size;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Key not found" << endl;
}

void HashTable::print() const {
    for (int i = 0; i < capacity; ++i) {
        cout << "Bucket " << i << ": ";
        Node* current = table[i];
        while (current != nullptr) {
            cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        cout << endl;
    }
}

int HashTable::getSize() const {
    return size;
}

bool HashTable::isEmpty() const {
    return size == 0;
}

int main() {
    HashTable ht(7);
    ht.insert(1, "Apple");
    ht.insert(2, "Banana");
    ht.insert(3, "Cherry");
    ht.insert(8, "Watermelon");
  ht.insert(15, "Bluberry"); 
    cout << "The contents of the hash table :" << endl;
    ht.print();

    cout << "Search key 3: " << ht.search(3) << endl;
    cout << "Search 10: " << ht.search(10) << endl;

    cout << "Remove key 3..." << endl;
    ht.remove(3);
    ht.print();

    return 0;
}
