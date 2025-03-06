#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void insertTreeNode(TreeNode*& root, int value) {
    if (!root) root = new TreeNode(value);
    else if (value < root->value) insertTreeNode(root->left, value);
    else insertTreeNode(root->right, value);
}

void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->value);
    inorderTraversal(root->right, result);
}

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

void treeSort(vector<int>& arr) {
    TreeNode* root = nullptr;
    for (int val : arr) insertTreeNode(root, val);
    arr.clear();
    inorderTraversal(root, arr);
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    cout << "Original array: ";
    printArray(arr);

    treeSort(arr);
    cout << "Array after Tree Sort: ";
    printArray(arr);

    return 0;
}
