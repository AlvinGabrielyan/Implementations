#include <iostream>
#include <cmath>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class PerfectBinaryTree {
private:
    TreeNode* root;
    int height;

    TreeNode* insertNode(TreeNode* node, int value, int currentLevel, int maxLevel) {
        if (!node) return new TreeNode(value);

        if (currentLevel < maxLevel) {
            if (!node->left) {
                node->left = insertNode(node->left, value, currentLevel + 1, maxLevel);
            } else if (!node->right) {
                node->right = insertNode(node->right, value, currentLevel + 1, maxLevel);
            } else {
                node->left = insertNode(node->left, value, currentLevel + 1, maxLevel);
            }
        }
        return node;
    }

    bool isPerfectBinaryTreeHelper(TreeNode* node, int depth, int expectedDepth) const {
        if (!node) return true;

        if (!node->left && !node->right) {
            return depth == expectedDepth;
        }

        if (!node->left || !node->right) {
            return false;
        }

        return isPerfectBinaryTreeHelper(node->left, depth + 1, expectedDepth) &&
               isPerfectBinaryTreeHelper(node->right, depth + 1, expectedDepth);
    }

    void printTreePreOrder(TreeNode* node) const {
        if (!node) return;
        cout << node->val << " ";
        printTreePreOrder(node->left);
        printTreePreOrder(node->right);
    }

    void clearTree(TreeNode* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    PerfectBinaryTree() : root(nullptr), height(0) {}

    void insert(int value) {
        int maxNodesAtLevel = pow(2, height + 1) - 1; 
        int currentNodes = countNodes(root);
        if (currentNodes == maxNodesAtLevel) {
            height++; 
        }
        root = insertNode(root, value, 0, height);
        cout << "Inserted value: " << value << endl;
    }

    bool searchHelper(TreeNode* node, int value) const {
        if (!node) return false;
        if (node->val == value) return true;
        return searchHelper(node->left, value) || searchHelper(node->right, value);
    }

    bool search(int value) const {
        return searchHelper(root, value);
    }

    bool isPerfectBinaryTree() const {
        int expectedDepth = height;
        if (isPerfectBinaryTreeHelper(root, 0, expectedDepth)) {
            cout << "The tree is a perfect binary tree.\n";
            return true;
        } else {
            cout << "The tree is not a perfect binary tree.\n";
            return false;
        }
    }

    void printTree() const {
        cout << "Tree (pre-order traversal): ";
        printTreePreOrder(root);
        cout << endl;
    }

    ~PerfectBinaryTree() {
        clearTree(root);
    }

private:
    int countNodes(TreeNode* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};

int main() {
    PerfectBinaryTree tree;
    int choice, value;

    cout << "Perfect Binary Tree Program\n";

    while (true) {
        cout << "\n1. Insert Element\n2. Search Element\n3. Print Tree\n4. Check if Perfect Binary Tree\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter a value to search: ";
            cin >> value;
            if (tree.search(value)) {
                cout << "Value " << value << " found in the tree.\n";
            } else {
                cout << "Value " << value << " not found in the tree.\n";
            }
            break;
        case 3:
            tree.printTree();
            break;
        case 4:
            tree.isPerfectBinaryTree();
            break;
        case 5:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}

