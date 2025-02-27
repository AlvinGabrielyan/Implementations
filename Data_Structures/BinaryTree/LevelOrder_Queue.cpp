#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value): data(value),
    left(nullptr), right(nullptr){}
};

void levelOrderTraversal(Node* root)
{
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {

    
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }
}

int main()
{
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(7);
    root->right->right = new Node(6);

    cout << "Level Order Traversal of Binary Tree: ";
    levelOrderTraversal(root);
    return 0;
}
