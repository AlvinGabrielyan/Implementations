#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class MaxHeap {
    int* arr;
    int maxSize;
    int heapSize;

public:
    MaxHeap(int maxSize);
    int parent(int i) { return (i - 1) / 2; }
    int lChild(int i) { return (2 * i + 1); }
    int rChild(int i) { return (2 * i + 2); }
    int getMax() { return arr[0]; }
    int curSize() { return heapSize; }
    int removeMax();
    void MaxHeapify(int);
    void increaseKey(int i, int newVal);
    void deleteKey(int i);
    void insertKey(int x);
    void printHeap(); 
};

MaxHeap::MaxHeap(int totSize) {
    heapSize = 0;
    maxSize = totSize;
    arr = new int[totSize];
}

void MaxHeap::insertKey(int x) {
    if (heapSize == maxSize) {
        cout << " Could not insertKey\n";
        return;
    }

    heapSize++;
    int i = heapSize - 1;
    arr[i] = x;

    while (i != 0 && arr[parent(i)] < arr[i]) {
        swap(arr[i], arr[parent(i)]);
        i = parent(i);
    }
}

void MaxHeap::increaseKey(int i, int newVal) {
    arr[i] = newVal;
    while (i != 0 && arr[parent(i)] < arr[i]) {
        swap(arr[i], arr[parent(i)]);
        i = parent(i);
    }
}

int MaxHeap::removeMax() {
    if (heapSize <= 0)
        return INT_MIN;
    if (heapSize == 1) {
        heapSize--;
        return arr[0];
    }
    int root = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    MaxHeapify(0);

    return root;
}

void MaxHeap::deleteKey(int i) {
    increaseKey(i, INT_MAX);
    removeMax();
}

void MaxHeap::MaxHeapify(int i) {
    int l = lChild(i);
    int r = rChild(i);
    int largest = i;
    if (l < heapSize && arr[l] > arr[i])
        largest = l;
    if (r < heapSize && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        MaxHeapify(largest);
    }
}


void MaxHeap::printHeap() {
    cout << "Heap elements by levels:\n";
    int levelEnd = 1; 
    int count = 0;   
    for (int i = 0; i < heapSize; i++) {
        cout << arr[i] << " ";
        count++;
        if (count == levelEnd) {
            cout << "\n";
            levelEnd *= 2; 
            count = 0;
        }
    }
    cout << endl;
}



int main() {
    MaxHeap h(15);
    cout << "Entered 6 keys: " << endl;
    h.insertKey(4);
    h.insertKey(10);
    h.insertKey(12);
    h.insertKey(14);
    h.insertKey(7);
    h.insertKey(8);

    h.printHeap();

    h.deleteKey(3);
    cout << "Heap after deleting key at index 3:" << endl;
    h.printHeap();

    h.insertKey(25);
    h.insertKey(6);
    cout << "Heap after inserting 25 and 6:" << endl;
    h.printHeap();

    return 0;
}
