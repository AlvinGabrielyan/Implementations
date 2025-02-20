#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class ThreadSafeStack {

private:
    stack<T> data;
    mutable mutex mtx; 

public:
    ThreadSafeStack() = default;

    void push(T value) {
        lock_guard<mutex> lock(mtx);
        data.push(move(value));
    }

    bool pop(T& value) {
        lock_guard<mutex> lock(mtx);
        if (data.empty()) {
            return false;
        }
        
        value = move(data.top());
        data.pop();
        return true;
    }

    bool empty() const {
        lock_guard<mutex> lock(mtx);
        return data.empty();
    }

    size_t size() const {
        lock_guard<mutex> lock(mtx);
        return data.size();
    }
};

void producer(ThreadSafeStack<int>& stack, int start, int count) {
    for (int i = 0; i < count; ++i) {
        stack.push(start + i);
        this_thread::sleep_for(chrono::milliseconds(100)); 
        cout << "Thread " << this_thread::get_id() << " pushed: " << start + i << endl;
    }
}

void consumer(ThreadSafeStack<int>& stack, int count) {
    int value;
    int popped = 0;
    
    while (popped < count) {
        if (stack.pop(value)) {
            cout << "Thread " << this_thread::get_id() << " popped: " << value << endl;
            popped++;
            this_thread::sleep_for(chrono::milliseconds(150));  
        }
    }
}

int main() {
    ThreadSafeStack<int> stack;
    
    thread producer1(producer, ref(stack), 100, 5);
    thread producer2(producer, ref(stack), 200, 5);
    
    thread consumer1(consumer, ref(stack), 5);
    thread consumer2(consumer, ref(stack), 5);
    
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    
    cout << "Final stack size: " << stack.size() << endl;
    
    return 0;
}
