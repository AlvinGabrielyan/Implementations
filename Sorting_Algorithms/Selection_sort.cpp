#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "Original array: ";
    printArray(arr);

    selectionSort(arr);
    
    cout << "Array after Selection Sort: ";
    printArray(arr);

    return 0;
}
