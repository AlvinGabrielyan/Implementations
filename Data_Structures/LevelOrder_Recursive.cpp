#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void printLevel(Node* root, int level) {
    if (root == nullptr) {
        return;  }
    
    if (level == 1) {
        cout << root->data << " ";
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}



int treeHeight(Node* root) {
    if (root == nullptr) {
        return 0;  
    }
    
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    
    return max(leftHeight, rightHeight) + 1;
}

void levelOrderTraversal(Node* root) {
    int height = treeHeight(root);
    
    for (int i = 1; i <= height; i++) {
        printLevel(root, i); 
        cout << endl;  
    }
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Level Order Traversal (Recursive):" << endl;
    levelOrderTraversal(root);  
    return 0;
}
