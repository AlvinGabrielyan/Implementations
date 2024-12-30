#include <iostream>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class FullBinaryTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);

        if (!node->left) {
            node->left = new TreeNode(value);
        } else if (!node->right) {
            node->right = new TreeNode(value);
        } else {
            node->left = insertNode(node->left, value);
        }

        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (node->val == value) {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }

                if (!node->left || !node->right) {
                TreeNode* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }
        }

        node->left = deleteNode(node->left, value);
        node->right = deleteNode(node->right, value);

        return node;
    }

    bool isFullBinaryTreeHelper(TreeNode* node) const {
        if (!node) return true;

        if ((node->left && !node->right) || (!node->left && node->right)) {
            return false;
        }

        return isFullBinaryTreeHelper(node->left) && isFullBinaryTreeHelper(node->right);
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
    FullBinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
        cout << "Inserted value: " << value << endl;
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
        cout << "Deleted value: " << value << endl;
    }

    bool searchHelper(TreeNode* node, int value) const {
        if (!node) return false;
        if (node->val == value) return true;
        return searchHelper(node->left, value) || searchHelper(node->right, value);
    }
    
    bool search(int value) const {
        return searchHelper(root, value);
    }
 
    bool isFullBinaryTree() const {
        if (isFullBinaryTreeHelper(root)) {
            cout << "The tree is a full binary tree.\n";
            return true;
        } else {
            cout << "The tree is not a full binary tree.\n";
            return false;
        }
    }

    void printTree() const {
        cout << "Tree (pre-order traversal): ";
        printTreePreOrder(root);
        cout << endl;
    }

    ~FullBinaryTree() {
        clearTree(root);
    }
};

int main() {
    FullBinaryTree tree;
    int choice, value;

    cout << "Full Binary Tree Program\n";

    while (true) {
        cout << "\n1. Insert Element\n2. Search Element\n3. Delete Element\n4. Print Tree\n5. Check if Full Binary Tree\n6. Exit\nEnter your choice: ";
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
            cout << "Enter a value to delete: ";
            cin >> value;
            tree.deleteValue(value);
            break;
        case 4:
            tree.printTree();
            break;
        case 5:
            tree.isFullBinaryTree();
            break;
        case 6:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
