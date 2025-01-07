#include <iostream>
using namespace std;

// Strategy interface
class SortStrategy {
public:
    virtual void sort() const = 0;
};

// Concrete Strategy 1: BubbleSort
class BubbleSort : public SortStrategy {
public:
    void sort() const override {
        cout << "Sorting using Bubble Sort" << endl;
    }
};

// Concrete Strategy 2: QuickSort
class QuickSort : public SortStrategy {
public:
    void sort() const override {
        cout << "Sorting using Quick Sort" << endl;
    }
};

class Context {
private:
    SortStrategy* strategy;  

public:
      void setStrategy(SortStrategy* newStrategy) {
        strategy = newStrategy;
    }

       void executeStrategy() const {
        strategy->sort();
    }
};

int main() {
    Context context;
    
    BubbleSort bubbleSort;
    QuickSort quickSort;
    
    context.setStrategy(&bubbleSort);
    context.executeStrategy();
    
    context.setStrategy(&quickSort);
    context.executeStrategy();

    return 0;
}
