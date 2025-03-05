#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "Original array: ";
    printArray(arr);

    quickSort(arr, 0, arr.size() - 1);
    
    cout << "Array after Quick Sort: ";
    printArray(arr);

    return 0;
}
