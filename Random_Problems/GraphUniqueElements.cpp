#include <iostream>
#include<set>
#include <vector>

using namespace std;

struct Node {
  int val;
  vector<Node*> neighbors;
  Node(int x) : val(x){}

};
void dfs(Node* node, set<int>& visited, vector<int>& result) {
    if(!node || visited.count(node->val)) return;
    
    visited.insert(node->val);
    result.push_back(node->val);
    
    for(Node* neighbor : node->neighbors)
    {
        dfs(neighbor,visited, result);
    }
}

vector<int> getAllElements(Node* start) {
    set<int> visited; 
    vector<int> result;
    dfs(start, visited, result);
    return result;
}



int main()
{
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->neighbors = {node2, node3};
    node2->neighbors = {node1, node4};  
    node3->neighbors = {node1};
    node4->neighbors = {node2};

    vector<int> elements = getAllElements(node1);
    
    for (int val : elements) {
        cout << val << " ";
    }

    return 0;

}
