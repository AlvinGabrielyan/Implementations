#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> results; 
    
    void traverse(TreeNode* currentNode) {
        if (currentNode == NULL) return;

        if (currentNode->left != NULL) {
            traverse(currentNode->left);
        }
        if (currentNode->right != NULL) {
            traverse(currentNode->right);
        }
        results.push_back(currentNode->val); 
    }

    vector<int> postorderTraversal(TreeNode* root) {
        traverse(root);
        return results;
    }
};

void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
  
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);


    Solution sol;
    vector<int> result = sol.postorderTraversal(root);

    cout << "Postorder Traversal: ";
    printVector(result);

    return 0;
}
