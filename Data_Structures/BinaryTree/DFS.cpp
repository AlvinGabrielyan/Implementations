/*Temporary queue-i mej put enq root-y, stugum enq, ete children chuni, iran uxarkum enq result queue-i mej,
ete uni left child, leftin put enq anum temp-i mej, parent-in result.*/

#include <iostream>
#include <deque>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

vector<int> dfs_using_queues(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    deque<Node*> temp_queue;
    temp_queue.push_back(root);
    
    while (!temp_queue.empty()) {
        Node* current = temp_queue.back();
        temp_queue.pop_back(); 
        result.push_back(current->value);
        
        if (current->right) {
            temp_queue.push_back(current->right);
        }
        if (current->left) {
            temp_queue.push_back(current->left);
        }
    }
    
    return result;
}

Node* create_sample_tree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    return root;
}

void delete_tree(Node* root) {
    if (root) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

int main() {
    Node* tree = create_sample_tree();
    vector<int> result = dfs_using_queues(tree);
    
    cout << "DFS Traversal: ";
    for (int value : result) {
        cout << value << " ";
    }
    cout << endl;
    
    delete_tree(tree);
    return 0;
}
