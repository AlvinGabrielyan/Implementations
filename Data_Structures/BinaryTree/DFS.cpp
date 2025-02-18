#include <iostream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

vector<int> dfs_two_queues(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    deque<Node*> temp_queue;   
    queue<int> result_queue;  
    
    temp_queue.push_front(root);
    
    while (!temp_queue.empty()) {
        Node* current = temp_queue.front();
        temp_queue.pop_front();
        
        result_queue.push(current->value);

        if (current->right) {
            temp_queue.push_front(current->right);
        }
        if (current->left) {
            temp_queue.push_front(current->left);
        }
    }
    
    while (!result_queue.empty()) {
        result.push_back(result_queue.front());
        result_queue.pop();
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
    vector<int> result = dfs_two_queues(tree);
    
    cout << "DFS Traversal: ";
    for (int value : result) {
        cout << value << " ";
    }
    cout << endl;
    
    delete_tree(tree);
    return 0;
}
