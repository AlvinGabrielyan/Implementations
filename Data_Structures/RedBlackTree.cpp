#include <iostream>
#include <algorithm>
#include <memory>
#include <climits>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

enum Color {
    RED, BLACK
};

class Node {
public:
    int value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) : value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    Node* searchHelper(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }
        if (value < node->value) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }

    void fixInsert(Node* node) {
        Node* parent = nullptr;
        Node* grandParent = nullptr;

        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandParent = parent->parent;

            if (parent == grandParent->left) {
                Node* uncle = grandParent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandParent;
                } else {
                    if (node == parent->right) {
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotate(grandParent);
                    swapColors(parent, grandParent);
                    node = parent;
                }
            } 
            
            else {
                Node* uncle = grandParent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandParent;
                } else {
                    if (node == parent->left) {
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    leftRotate(grandParent);
                    swapColors(parent, grandParent);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    void swapColors(Node* x, Node* y) {
        Color temp = x->color;
        x->color = y->color;
        y->color = temp;
    }

    void inorderHelper(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        inorderHelper(node->left);
        cout << node->value << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderHelper(node->right);
    }

    int calculateHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

    void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void printTreeHelper(Node* root, string prefix, bool isLeft, vector<string>& result) {
        if (root == nullptr) {
            return;
        }

        string nodeStr = to_string(root->value) + (root->color == RED ? "(R)" : "(B)");
        printTreeHelper(root->right, prefix + (isLeft ? "│   " : "    "), false, result);
        result.push_back(prefix + (isLeft ? "└── " : "┌── ") + nodeStr);
        printTreeHelper(root->left, prefix + (isLeft ? "    " : "│   "), true, result);
    }

    void printLevelOrderHelper(Node* root, vector<string>& result) {
        if (root == nullptr) {
            result.push_back("Empty tree");
            return;
        }

        int height = calculateHeight(root);
        int width = (1 << height) * 6 - 2; 

        vector<vector<string>> levels(height);
        queue<pair<Node*, pair<int, int>>> q; 
        q.push({root, {0, width / 2}});

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            Node* node = current.first;
            int level = current.second.first;
            int pos = current.second.second;
            
            while (levels.size() <= level) {
                levels.push_back({});
            }
            
            string nodeStr = to_string(node->value) + (node->color == RED ? "R" : "B");
            
            while (levels[level].size() <= pos + nodeStr.length()) {
                levels[level].push_back(" ");
            }
            
            for (size_t i = 0; i < nodeStr.length(); i++) {
                levels[level][pos + i] = nodeStr[i];
            }
            
            if (node->left) {
                q.push({node->left, {level + 1, pos - (1 << (height - level - 2))}});
            }
            if (node->right) {
                q.push({node->right, {level + 1, pos + (1 << (height - level - 2))}});
            }
        }
        for (const auto& level : levels) {
            string levelStr;
            for (const auto& c : level) {
                levelStr += c;
            }
            result.push_back(levelStr);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        destroyTree(root);
    }

    Node* search(int value) {
        return searchHelper(root, value);
    }

    void insert(int value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                delete newNode;
                return;
            }
        }

        newNode->parent = parent;

        if (value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsert(newNode);
    }

    void inorderTraversal() {
        inorderHelper(root);
        cout << endl;
    }

    bool contains(int value) {
        return search(value) != nullptr;
    }

    int getHeight() {
        return calculateHeight(root);
    }

    int size() {
        return countNodes(root);
    }

    int findMin() {
        if (root == nullptr) {
            return INT_MIN;
        }

        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }

        return current->value;
    }

    int findMax() {
        if (root == nullptr) {
            return INT_MAX;
        }

        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }

        return current->value;
    }

    bool isEmpty() {
        return root == nullptr;
    }

    vector<string> printTree() {
        vector<string> result;
        printTreeHelper(root, "", false, result);
        reverse(result.begin(), result.end());
        return result;
    }

    vector<string> printLevelOrder() {
        vector<string> result;
        printLevelOrderHelper(root, result);
        return result;
    }

    void displayTree() {
        if (root == nullptr) {
            cout << "Empty tree" << endl;
            return;
        }

        vector<string> treeLines = printTree();
        for (const auto& line : treeLines) {
            cout << line << endl;
        }
    }
};

void displayMenu() {
    cout << "\n===== Red-Black Tree Visualization =====\n";
    cout << "1. Insert a value\n";
    cout << "2. Display tree\n";
    cout << "3. Search for a value\n";
    cout << "4. Get tree statistics\n";
    cout << "5. Inorder traversal\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    RedBlackTree tree;
    int choice, value;
    
    cout << "Welcome to the Red-Black Tree Visualizer!" << endl;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << "Value " << value << " inserted!" << endl;
                tree.displayTree();
                break;
                
            case 2:
                cout << "\n--- Tree Visualization ---\n";
                tree.displayTree();
                break;
                
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.contains(value)) {
                    cout << "Value " << value << " exists in the tree." << endl;
                } else {
                    cout << "Value " << value << " does not exist in the tree." << endl;
                }
                break;
                
            case 4:
                cout << "\n--- Tree Statistics ---\n";
                cout << "Height: " << tree.getHeight() << endl;
                cout << "Number of nodes: " << tree.size() << endl;
                if (!tree.isEmpty()) {
                    cout << "Minimum value: " << tree.findMin() << endl;
                    cout << "Maximum value: " << tree.findMax() << endl;
                }
                break;
                
            case 5:
                cout << "Inorder traversal: ";
                tree.inorderTraversal();
                break;
                
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}
