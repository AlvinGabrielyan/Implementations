#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PriorityQueue {
    vector<int> data;
    bool isMinHeap;  

public:
    PriorityQueue(bool minHeap = true) : isMinHeap(minHeap) {}

    void enquque(int value) {
        data.push_back(value); 
        if (isMinHeap) {
            sort(data.begin(), data.end()); //skzbic a sksvum sorting-y, minheapi hamar
        } else {
            sort(data.rbegin(), data.rend()); //cucichy verjic a sksvum, 
        }
    }

    int dequeue() {
        if (data.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        
        int topElement = data.front(); 
        data.erase(data.begin());    
        return topElement;
    }

    int top() const {
        if (data.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        return data.front(); 
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    void printQueue() const {
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
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
