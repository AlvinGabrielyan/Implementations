#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    int data;
    bool color;
    Node* left;
    Node* right;

    Node(int val, bool col) : data(val), color(col), left(NULL), right(NULL) {}
};

int getHeight(Node* root) {
    if (root == NULL) return -1;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

bool isValidRBT(Node* node, int blackCount, int& pathBlackCount, bool& isValid) {
    if (node == NULL) {
        if (pathBlackCount == -1)
            pathBlackCount = blackCount;
        return blackCount == pathBlackCount;
    }

    if (node->color == true) {
        if ((node->left && node->left->color == true) ||
            (node->right && node->right->color == true)) {
            isValid = false;
            return false;
        }
    }

    if (node->color == false)
        blackCount++;

    bool leftValid = isValidRBT(node->left, blackCount, pathBlackCount, isValid);
    bool rightValid = isValidRBT(node->right, blackCount, pathBlackCount, isValid);

    return leftValid && rightValid;
}

bool validateRBT(Node* root) {
    if (root == NULL) return true;
    if (root->color != false) return false; 
    int pathBlackCount = -1;
    bool isValid = true;
    return isValidRBT(root, 0, pathBlackCount, isValid) && isValid;
}

Node* insert(Node* root, int key, bool color) {
    if (root == NULL) return new Node(key, color);
    if (key < root->data)
        root->left = insert(root->left, key, color);
    else
        root->right = insert(root->right, key, color);
    return root;
}

int main() {
    Node* root = NULL;
    int n;
    cout << "Enter number of nodes to insert: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int val;
        bool col;
        cout << "Enter value and color (0 = Black, 1 = Red): ";
        cin >> val >> col;
        if (root == NULL && col != 0) {
            cout << "Root must be black. Setting color to black.\n";
            col = 0;
        }
        root = insert(root, val, col);
    }

    cout << "\nTask 1: Height of the Red-Black Tree = " << getHeight(root) << endl;
    cout << "Task 2: Is Valid Red-Black Tree? " << (validateRBT(root) ? "Yes" : "No") << endl;

    return 0;
}
