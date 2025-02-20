/*(LRU)-ն  քեշի փոխարինման քաղաքականություն է, որն ապահովում է, որ քեշը պահպանի վերջին օգտագործված տվյալները, 
իսկ ամենաքիչ օգտագործվածները ջնջվեն, երբ այն հասնի իր ծավալին:*/

#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    
    void _remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void _add(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    ~LRUCache() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            _remove(node);
            _add(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            _remove(cache[key]);
            delete cache[key];
        }
        
        Node* node = new Node(key, value);
        cache[key] = node;
        _add(node);
        
        if (cache.size() > capacity) {
            Node* lru = tail->prev;
            _remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }
};

int main() {
    LRUCache cache(2);
    
    cache.put(1, 1);
    cout << "Put (1,1)" << endl;
    
    cache.put(2, 2);
    cout << "Put (2,2)" << endl;
    
    cout << "Get 1: " << cache.get(1) << endl;    
    
    cache.put(3, 3);    
    cout << "Put (3,3)" << endl;
    
    cout << "Get 2: " << cache.get(2) << endl;    
    
    cache.put(4, 4);    
    cout << "Put (4,4)" << endl;
    
    cout << "Get 1: " << cache.get(1) << endl;    
    cout << "Get 3: " << cache.get(3) << endl;    
    cout << "Get 4: " << cache.get(4) << endl;    
    
    return 0;
}
