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

class CompleteBinaryTree {
private:
    vector<TreeNode*> nodes; 

    void swapNodes(TreeNode* a, TreeNode* b) {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }

public:
    CompleteBinaryTree() {}

    void insert(int value, const string& direction) {
        TreeNode* newNode = new TreeNode(value);
        nodes.push_back(newNode);

        int index = nodes.size() - 1;
        if (index == 0) return; 

        int parentIndex = (index - 1) / 2;
        if (direction == "left" && nodes[parentIndex]->left == nullptr) {
            nodes[parentIndex]->left = newNode; 
        } else if (direction == "right" && nodes[parentIndex]->right == nullptr) {
            nodes[parentIndex]->right = newNode; 
        } else {
            cout << "Cannot insert " << value << " to the " << direction << "." << endl;
            nodes.pop_back();
        }
    }

    bool search(int value) const {
        for (const auto& node : nodes) {
            if (node->val == value) {
                return true;
            }
        }
        return false;
    }

    bool deleteValue(int value) {
        int indexToDelete = -1;

        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i]->val == value) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete == -1) {
            cout << "Value " << value << " not found in the tree.\n";
            return false; 
        }

        TreeNode* lastNode = nodes.back();
        swapNodes(nodes[indexToDelete], lastNode);

        int parentIndex = (nodes.size() - 2) / 2;
        if (nodes.size() % 2 == 1) {
            nodes[parentIndex]->right = nullptr;
        } else {
            nodes[parentIndex]->left = nullptr;
        }

        delete lastNode;
        nodes.pop_back();
        
        return true;
    }

    bool isComplete() const {
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i]->right && !nodes[i]->left) {
                return false;
            }

            if ((2 * i + 1 < nodes.size() && !nodes[i]->left) || 
                (2 * i + 2 < nodes.size() && !nodes[i]->right)) {
                return false;
            }
        }
        return true;
    }

    void printLevelOrder() const {
        for (const auto& node : nodes) {
            cout << node->val << " ";
        }
        cout << endl;
    }

    ~CompleteBinaryTree() {
        for (auto node : nodes) {
            delete node;
        }
    }
};

int main() {
    CompleteBinaryTree tree;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Element\n";
        cout << "2. Delete Element\n";
        cout << "3. Search Element\n";
        cout << "4. Check Completeness\n";
        cout << "5. Print Level-Order Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                string direction;
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Enter direction (left/right): ";
                cin >> direction;
                tree.insert(value, direction);
                break;
            }
            case 2: {
                int value;
                cout << "Enter value to delete: ";
                cin >> value;
                if (tree.deleteValue(value)) {
                    cout << "Value " << value << " deleted successfully.\n";
                }
                break;
            }
            case 3: {
                int value;
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(value)) {
                    cout << "Value " << value << " found in the tree.\n";
                } else {
                    cout << "Value " << value << " not found in the tree.\n";
                }
                break;
            }
            case 4:
                if (tree.isComplete()) {
                    cout << "The tree is a complete binary tree.\n";
                } else {
                    cout << "The tree is NOT a complete binary tree.\n";
                }
                break;
            case 5:
                cout << "Level-order traversal of the tree: ";
                tree.printLevelOrder();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

