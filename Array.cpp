#include <iostream>
using namespace std;

class MyArray {
private:
    int* arr;      
    int capacity;   
    int currentSize; 

public:
     MyArray(int size) {
        capacity = size;
        arr = new int[capacity];
        currentSize = 0; 
    }
    ~MyArray() {
        delete[] arr;
    }

    void insert(int value) {
        if (currentSize == capacity) {
            cout << "Array is full." << endl;
            return;
        }
        arr[currentSize] = value;
        currentSize++;
    }

    void insertAt(int index, int value) {
        if (currentSize == capacity) {
            cout << "Array is full." << endl;
            return;
        }
        if (index < 0 || index > currentSize) {
            cout << "Invalid index!" << endl;
            return;
        }

		for (int i = currentSize; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        currentSize++;
    }
	
	void removeAt(int index) {
        if (index < 0 || index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        for (int i = index; i < currentSize - 1; i++) {
            arr[i] = arr[i + 1];
        }
        currentSize--; 
    }

	int get(int index) const {
        if (index < 0 || index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return -1; 
        }
        return arr[index];
    }
   void update(int index, int value) {
        if (index < 0 || index >= currentSize) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        arr[index] = value;
    }
   void display() const {
        if (currentSize == 0) {
            cout << "Array is empty!" << endl;
            return;
        }
        cout << "Array elements: ";
        for (int i = 0; i < currentSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int size() const {
        return currentSize;
    }

    int getCapacity() const {
        return capacity;
    }
};

int main() {
    MyArray myArr(6);

    myArr.insert(10);
    myArr.insert(20);
    myArr.insert(30);
    myArr.display(); 

    myArr.insertAt(1, 15); 
    myArr.display(); 

    myArr.insertAt(0, 5); 
    myArr.display();

    myArr.removeAt(2); 
    myArr.display(); 

    return 0;
}
