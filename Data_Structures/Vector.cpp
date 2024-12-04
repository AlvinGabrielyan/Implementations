#include <iostream>
using namespace std;

class MyVector {
private:
    int* arr;
    int capacity;
    int currentSize;

    void resize() {
        int* temp = new int[capacity * 2]; 
        for (int i = 0; i < currentSize; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        capacity *= 2;
    }

public:
    MyVector(int initialCapacity = 2) {
        capacity = initialCapacity;
        arr = new int[capacity];
        currentSize = 0;
    }

    ~MyVector() {
        delete[] arr;
    }

    int size() const {
        return currentSize;
    }

    int getCapacity() const {
        return capacity;
    }

    void pushBack(int value) {
        if (currentSize == capacity) {
            resize();  
        }
        arr[currentSize] = value;
        currentSize++;
    }

    void popBack() {
        if (currentSize > 0) {
            currentSize--;  
        } else {
            cout << "Vector is empty!" << endl;
        }
    }

    int get(int index) const {
        if (index < 0  index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return -1;
        }
        return arr[index];
    }

    void update(int index, int value) {
        if (index < 0  index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        arr[index] = value;
    }

    void display() const {
        cout << "Vector elements: ";
        for (int i = 0; i < currentSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

  void insertAt(int index, int value) {
        if (index < 0  index > currentSize) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        if (currentSize == capacity) {
            resize();  
    }
        
    for (int i = currentSize; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        currentSize++;
    }

    void removeAt(int index) {
        if (index < 0  index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return;
        }
  
    for (int i = index; i < currentSize - 1; i++) {
            arr[i] = arr[i + 1];
        }
        currentSize--; 
    }
};

int main() {
    MyVector vec;

    vec.pushBack(10);
    vec.pushBack(20);
    vec.pushBack(30);
    vec.display(); 
    vec.insertAt(1, 15); 
    vec.display(); 
    vec.removeAt(2); 
    vec.display(); 

    return 0;
}

 c
