#include <iostream>
using namespace std;

class Queue {
private:
    int front, rear, size;
    int* queue;
public:
    Queue(int s) {
        front = rear = -1;
        size = s;
        queue = new int[size];
    }

     void enqueue(int value) {
        if (rear == size - 1) {
            cout << "Queue is full\n";
        }
    else 
    {
            if (front == -1) front = 0; 
            rear++;
            queue[rear] = value;
            cout << value << " enqueued into the queue\n";
        }
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty\n";
        }
    else {
            cout << queue[front] << " dequeued from the queue\n";
            front++;
            if (front > rear) front = rear = -1; 
        }
    }
    void display() {
        if (front == -1) {
            cout << "Queue is empty\n";
        } else {
            cout << "Queue elements: ";
            for (int i = front; i <= rear; i++) {
                cout << queue[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Queue q(5); 

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display(); 

    q.dequeue(); 
    q.display();

    q.enqueue(50);
    q.display();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue(); 

    return 0;
}
