#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class DegenerateBinaryTree {
private:
    TreeNode* root;

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (node->val == value) {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            TreeNode* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }

        if (node->left) node->left = deleteNode(node->left, value);
        if (node->right) node->right = deleteNode(node->right, value);

        return node;
    }

    bool searchNode(TreeNode* node, int value) const {
        if (!node) return false;
        if (node->val == value) return true;
        return searchNode(node->left, value) || searchNode(node->right, value);
    }

    void clearTree(TreeNode* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    void printTree(TreeNode* node) const {
        if (!node) return;
        cout << node->val << " ";
        printTree(node->left);
        printTree(node->right);
    }

    bool isDegenerateHelper(TreeNode* node) const {
        if (!node) return true;
        if (node->left && node->right) return false;
        return isDegenerateHelper(node->left) && isDegenerateHelper(node->right);
    }

public:
    DegenerateBinaryTree() : root(nullptr) {}

    void insert(int value, const string& direction) {
        TreeNode* newNode = new TreeNode(value);

        if (!root) {
            root = newNode;
            cout << "Inserted root node with value: " << value << endl;
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (direction == "left") {
                if (!current->left) {
                    current->left = newNode;
                    cout << "Inserted " << value << " as left child of " << current->val << endl;
                    break;
                } else {
                    current = current->left;
                }
            } else if (direction == "right") {
                if (!current->right) {
                    current->right = newNode;
                    cout << "Inserted " << value << " as right child of " << current->val << endl;
                    break;
                } else {
                    current = current->right;
                }
            } else {
                cout << "Invalid direction! Use 'left' or 'right'." << endl;
                delete newNode;
                return;
            }
        }
    }

    void deleteValue(int value) {
        if (!search(value)) {
            cout << "Value " << value << " not found in the tree.\n";
            return;
        }
        root = deleteNode(root, value);
        cout << "Value " << value << " deleted successfully.\n";
    }

    bool search(int value) const {
        return searchNode(root, value);
    }

    void printTree() const {
        cout << "Tree (pre-order traversal): ";
        printTree(root);
        cout << endl;
    }

    bool isDegenerate() const {
        if (isDegenerateHelper(root)) {
            cout << "The tree is degenerate.\n";
            return true;
        } else {
            cout << "The tree is not degenerate.\n";
            return false;
        }
    }

    ~DegenerateBinaryTree() {
        clearTree(root);
    }
};

int main() {
    DegenerateBinaryTree tree;
    int choice, value;
    string direction;

    cout << "Degenerate Binary Tree Program\n";

    while (true) {
        cout << "\n1. Insert Element\n2. Search Element\n3. Delete Element\n4. Print Tree\n5. Check if Degenerate\n6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a value to insert: ";
            cin >> value;
            cout << "Enter direction (left or right): ";
            cin >> direction;
            tree.insert(value, direction);
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
            tree.isDegenerate();
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

