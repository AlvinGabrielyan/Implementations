//hashset  #include <iostream>
#include <list>
#include <vector>
using namespace std;

class HashSet {
private:
    static const int hashSize = 16; 
    vector<list<int>> table; 

    int hashFunction(int key) {
        return key % hashSize; 
    }

public:
    HashSet() {
        table.resize(hashSize); 
  }

    void insert(int key) {
        int index = hashFunction(key);
              for (int element : table[index]) {
            if (element == key) {
                return; 
            }
        }
              table[index].push_back(key);
    }

    bool contains(int key) {
        int index = hashFunction(key);
        for (int element : table[index]) {
            if (element == key) {
                return true;
            }
        }
        return false; 
    }

    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    void display() {
        for (int i = 0; i < hashSize; i++) {
            cout << "Bucket " << i << ": ";
            for (int element : table[i]) {
                cout << element << " -> ";
            }
            cout << "nullptr" << endl;
        }
    }
};

int main() {
    HashSet hashSet;
    hashSet.insert(10);
    hashSet.insert(20);
    hashSet.insert(15);
    hashSet.insert(25);
    hashSet.insert(30);
    hashSet.insert(26);
    hashSet.insert(27);
    hashSet.insert(25);
    hashSet.insert(46);
    hashSet.insert(37);
    hashSet.insert(74);
    hashSet.insert(64);
    hashSet.insert(46);
    hashSet.insert(25);
    hashSet.insert(25);
    hashSet.insert(25);
    hashSet.insert(25);
    
    cout << "Current HashSet:" << endl;
    hashSet.display();

    cout << "Contains 15: " << (hashSet.contains(15) ? "Yes" : "No") << endl;
    cout << "Contains 30: " << (hashSet.contains(30) ? "Yes" : "No") << endl;

    hashSet.remove(15);
    cout << "After removing 15:" << endl;
    hashSet.display();

    return 0;
}
