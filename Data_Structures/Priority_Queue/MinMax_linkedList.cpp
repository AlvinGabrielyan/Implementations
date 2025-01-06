#include <iostream>
#include <stdexcept>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class PriorityQueue {
    Node* head;
    bool isMinHeap;

public:
    PriorityQueue(bool minHeap = true) : head(nullptr), isMinHeap(minHeap) {}

    void enquque(int value) {
        Node* newNode = new Node(value);

        if (!head) {
            head = newNode;
            return;
        }

        if (isMinHeap) {
            if (value < head->data) {
                newNode->next = head;
                head = newNode;
                return;
            }
        } else {
            if (value > head->data) {//avelacnum enq skzbum, vor heto voroshenq priority-n
                newNode->next = head;
                head = newNode;
                return;
            }
        }

        // Aynqan enq ancnum tarreri vrayov, minchev gtnenq avelacvox tarri texy listum
        Node* current = head;
        while (current->next && 
              ((isMinHeap && current->next->data <= value) || 
               (!isMinHeap && current->next->data >= value))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    int dequeue() {
        if (!head) {
            throw runtime_error("Priority Queue is empty!");
        }

        Node* temp = head;
        int value = head->data;
        head = head->next;
        delete temp;
        return value;
    }

    int top() const {
        if (!head) {
            throw runtime_error("Priority Queue is empty!");
        }
        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void printQueue() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    PriorityQueue minPQ(true); 

    minPQ.enquque(20);
    minPQ.enquque(5);
    minPQ.enquque(15);
    minPQ.enquque(10);

    cout << "Min-Priority Queue (After Insertions): ";
    minPQ.printQueue();

    cout << "Top element: " << minPQ.top() << endl;

    cout << "Removing top element: " << minPQ.dequeue() << endl;

    cout << "Min-Priority Queue (After Extraction): ";
    minPQ.printQueue();

    PriorityQueue maxPQ(false); 

    maxPQ.enquque(20);
    maxPQ.enquque(5);
    maxPQ.enquque(15);
    maxPQ.enquque(10);

    cout << "\nMax-Priority Queue (After Insertions): ";
    maxPQ.printQueue();

    cout << "Top element: " << maxPQ.top() << endl;

    cout << "Removing top element: " << maxPQ.dequeue() << endl;

    cout << "Max-Priority Queue (After Extraction): ";
    maxPQ.printQueue();

    return 0;
}
