#include <iostream>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <string>

using namespace std;

template <typename K, typename V>
class ConcurrentHashMap {
private:
    unordered_map<K, V> map;
    mutable shared_mutex mutex;

public:

    void insert(const K& key, const V& value) {
        unique_lock<shared_mutex> lock(mutex);
        map[key] = value;
    }

    bool get(const K& key, V& value) const {
        shared_lock<shared_mutex> lock(mutex);
        auto it = map.find(key);
        if (it != map.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    bool erase(const K& key) {
        unique_lock<shared_mutex> lock(mutex);
        return map.erase(key) > 0;
    }

    bool contains(const K& key) const {
        shared_lock<shared_mutex> lock(mutex);
        return map.find(key) != map.end();
    }

    void print() const {
        shared_lock<shared_mutex> lock(mutex);
        for (const auto& pair : map) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
};

int main() {
    ConcurrentHashMap<int, string> cmap;
    int choice;
    
    while (true) {
        cout << "\nMenu:\n"
             << "1. Insert key-value pair\n"
             << "2. Get value by key\n"
             << "3. Erase key-value pair\n"
             << "4. Check if key exists\n"
             << "5. Print all key-value pairs\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            break;
        }

        int key;
        string value;
        switch (choice) {
            case 1: 
                cout << "Enter key (integer): ";
                cin >> key;
                cout << "Enter value (string): ";
                cin >> value;
                cmap.insert(key, value);
                cout << "Inserted successfully!\n";
                break;

            case 2: 
                cout << "Enter key to retrieve: ";
                cin >> key;
                if (cmap.get(key, value)) {
                    cout << "Value: " << value << endl;
                } else {
                    cout << "Key not found.\n";
                }
                break;

            case 3: 
                cout << "Enter key to erase: ";
                cin >> key;
                if (cmap.erase(key)) {
                    cout << "Key erased successfully.\n";
                } else {
                    cout << "Key not found.\n";
                }
                break;

            case 4: 
                cout << "Enter key to check: ";
                cin >> key;
                if (cmap.contains(key)) {
                    cout << "Key exists.\n";
                } else {
                    cout << "Key does not exist.\n";
                }
                break;

            case 5: 
                cmap.print();
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
