#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct item {
  int value;
  int priority;
};

class PriorityQueue {
private:
  vector<item> pq;
public:
  void enqueue(int value, int priority) {
    item newItem = { value,priority };        
    pq.push_back(newItem);
  }


  int peek() {
    sort(pq.begin(), pq.end(), [](const item& a, const item& b)
      {
        if (a.priority == b.priority) {
          return a.value > b.value;
        }
        return a.priority > b.priority;
      });

    return pq.front().value;                  
  }
  
  void dequeue() {
    sort(pq.begin(), pq.end(), [](const item& a, const item& b) {
      if (a.priority == b.priority) {
        return a.value > b.value;
      }
      return a.priority > b.priority;
      });

    if (!pq.empty()) {
      pq.erase(pq.begin());
    }
  }
};

int main() {
  PriorityQueue pq;
  pq.enqueue(10, 2);
  pq.enqueue(14, 4);
  pq.enqueue(16, 4);
  pq.enqueue(12, 3);

  cout << "Top element: " << pq.peek() << endl;
  
  pq.dequeue();
  cout << "Top element: " << pq.peek() << endl;



}
